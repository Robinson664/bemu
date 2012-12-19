using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using BBLinq.Types;

using Bloomberglp.Blpapi;

namespace BBLinq
{
    public static class BBMktDataType
    {
        /// <summary>
        /// Subscribe to real-time market data.
        /// </summary>
        /// <param name="bbKeys">Bloomberg Yellow Key identifiers for securities</param>
        /// <param name="fields">Real-time data fields</param>
        /// <param name="callback">A function that will be called when market data is received.  Use the function's list of FieldTimeType objects.  Different keys can have different callbacks.</param>
        public static void BBMktData(this IEnumerable<string> bbKeys, IEnumerable<string> fields, Action<IEnumerable<FieldTimeType>> callback = null)
        {
            BBMktDataHelpers.Subscribe(bbKeys, fields, null, callback);
        }

        /// <summary>
        /// Subscribe to real-time market data.
        /// </summary>
        /// <param name="bbKeys">Bloomberg Yellow Key identifiers for securities</param>
        /// <param name="fields">Real-time data fields</param>
        /// <param name="conflationInterval">Sets a defined period in seconds for which updates will be received for the subscription. In range [0.1 seconds, 24 hours]</param>
        /// <param name="callback">A function that will be called when market data is received.  Use the function's list of FieldTimeType objects.  Different keys can have different callbacks.</param>
        public static void BBMktData(this IEnumerable<string> bbKeys, IEnumerable<string> fields, TimeSpan? conflationInterval = null, Action<IEnumerable<FieldTimeType>> callback = null)
        {
            if (conflationInterval.HasValue)
            {
                if (conflationInterval.Value.TotalSeconds < 0.1 || conflationInterval.Value.TotalSeconds > 86400)
                    throw new ArgumentOutOfRangeException("conflationInterval must be >= 0.1 seconds and <= 86400 seconds (24 hours).  Your conflationInterval is " + conflationInterval.Value.TotalSeconds.ToString());
            }

            BBMktDataHelpers.Subscribe(bbKeys, fields, conflationInterval, callback);
        }

        /// <summary>
        /// Unsubscribe from market data for the given securities.
        /// </summary>
        /// <param name="bbKeys"></param>
        public static void BBMktData(this IEnumerable<string> bbKeys)
        {
            BBMktDataHelpers.Unsubscribe(bbKeys);
        }

        /// <summary>
        /// Use this to stop the subscription service.  You can restart it in the same way that you started it originally.
        /// </summary>
        public static void Dispose()
        {
            BBMktDataHelpers.Dispose();
        }

        private static class BBMktDataHelpers
        {
            private readonly static object _syncroot = new object();
            private static bool _isServiceOpened = false; //use this to make sure that the service is opened before subscribing to market data

            private static Session _session;

            //each security can have its own separate callback.  this dictionary maps securities to their callbacks.
            private static Dictionary<string, Action<IEnumerable<FieldTimeType>>> _key2Callback = new Dictionary<string, Action<IEnumerable<FieldTimeType>>>();

            //a list of a subscriptions using my BBSubscriptionType that extends Subscription with a BBKey field to make it easier to unsubscribe.
            private static List<BBSubscriptionType> _subscriptions = new List<BBSubscriptionType>();

            static BBMktDataHelpers()
            {
                BBMktDataHelpers.CreateAndStartSession();
            }

            private static void CreateAndStartSession()
            {
                SessionOptions options = new SessionOptions();
                options.ServerHost = "127.0.0.1";
                options.ServerPort = 8194;

                BBMktDataHelpers._session = new Session(options, BBMktDataHelpers.ProcessSubscriptionEvent);
                BBMktDataHelpers._session.StartAsync();
            }

            /// <summary>
            /// Creates a new session, waits for the session to open (on another thread), and then subscribes to securities that were previously subscribed to.
            /// </summary>
            private static void ReCreateAndReStartSession()
            {
                BBMktDataHelpers.CreateAndStartSession();
                BBMktDataHelpers.WaitForServiceToOpen();

                //resubscribe to the market data
                BBMktDataHelpers._session.Subscribe(BBMktDataHelpers._subscriptions.Cast<Subscription>().ToList());
            }

            public static void Dispose()
            {
                BBMktDataHelpers._session.Stop();
                BBMktDataHelpers._session.Dispose();
                BBMktDataHelpers._isServiceOpened = false;
            }

            public static void Unsubscribe(IEnumerable<string> bbkeys)
            {
                var bbSubsToRemove = BBMktDataHelpers._subscriptions.Where(w => bbkeys.Contains(w.BBKey)).ToList();

                //BBMktDataHelpers._session.Unsubscribe(subsToRemove); //unsubscribe from Bloomberg
                foreach (var item in bbSubsToRemove)
                {
                    BBMktDataHelpers._session.Cancel(item.CorrelationID);
                }

                var toRemove = BBMktDataHelpers._subscriptions.Where(w => bbkeys.Contains(w.BBKey)).ToList();
                foreach (var item in toRemove)
                {
                    BBMktDataHelpers._subscriptions.Remove(item);
                }
            }

            public static void Subscribe(IEnumerable<string> bbKeys, IEnumerable<string> fields, TimeSpan? tsConflationInterval, Action<IEnumerable<FieldTimeType>> callback)
            {
                bool needToWaitForService = false;
                lock (BBMktDataHelpers._syncroot)
                {
                    if (!BBMktDataHelpers._isServiceOpened)
                    {
                        BBMktDataHelpers.CreateAndStartSession();
                        needToWaitForService = true;
                    }
                }

                if (needToWaitForService)
                    BBMktDataHelpers.WaitForServiceToOpen();

                if (callback != null)
                {
                    foreach (var item in bbKeys)
                    {
                        BBMktDataHelpers._key2Callback.Remove(item);
                    }
                    foreach (var item in bbKeys)
                    {
                        BBMktDataHelpers._key2Callback.Add(item, callback);
                    }
                }

                List<string> listFields = fields.ToList(), listSubOptions = new List<string>();

                if (tsConflationInterval.HasValue)
                    listSubOptions.Add("interval=" + tsConflationInterval.Value.TotalSeconds.ToString());

                var subs = new List<BBSubscriptionType>();
                foreach (var key in bbKeys)
                {
                    CorrelationID id = new CorrelationID(NextCorrelationId.Get());
                    BBSubscriptionType sub = new BBSubscriptionType(key, listFields, listSubOptions, id);
                    subs.Add(sub);
                }

                BBMktDataHelpers.WaitForServiceToOpen();
                BBMktDataHelpers._session.Subscribe(subs.Cast<Subscription>().ToList()); //must ensure that the session is opened before subscribing to anything
                BBMktDataHelpers._subscriptions.AddRange(subs); //save the subscriptions so that I can (un)subscribe later if I need to
            }

            private static void WaitForServiceToOpen()
            {
                bool continueLoop = true;
                while (continueLoop) //keep checking if the session has been opened
                {
                    lock (BBMktDataHelpers._syncroot)
                    {
                        if (BBMktDataHelpers._isServiceOpened)
                            continueLoop = false;
                    }

                    if (continueLoop) //wait a little bit before checking again
                        System.Threading.Thread.Sleep(TimeSpan.FromMilliseconds(100));
                }
            }

            private static void ProcessSubscriptionEvent(Event eventObj, Session session)
            {
                switch (eventObj.Type)
                {
                    case Event.EventType.SESSION_STATUS:
                        foreach (var message in eventObj.GetMessages())
                        {
                            if (message.MessageType.Equals("SessionStarted"))
                            {
                                try
                                {
                                    lock (BBMktDataHelpers._syncroot)
                                    {
                                        //this must happen before subscribing to any data
                                        session.OpenServiceAsync("//blp/mktdata", new CorrelationID(NextCorrelationId.Get()));
                                        BBMktDataHelpers._isServiceOpened = true;
                                    }
                                }
                                catch (Exception)
                                {
                                    Console.Error.WriteLine("Could not open //blp/mktdata for async");
                                }
                            }
                        }
                        break;

                    case Event.EventType.SUBSCRIPTION_DATA:
                        DateTime dtNow = DateTime.Now;
                        foreach (var message in eventObj.GetMessages())
                        {
                            List<FieldTimeType> fields = new List<FieldTimeType>(message.NumElements);
                            string bbKey = message.TopicName;
                            foreach (var item in message.Elements)
                            {
                                if (!item.IsNull)
                                {
                                    object value = BBTypeConverter.GetValue(item);
                                    FieldTimeType fType = new FieldTimeType(bbKey, item.Name.ToString(), value, dtNow);
                                    fields.Add(fType);
                                }
                            }

                            Action<IEnumerable<FieldTimeType>> callback;
                            if (BBMktDataHelpers._key2Callback.TryGetValue(bbKey, out callback))
                                callback(fields);
                        }
                        break;

                    default:
                        break;
                }
            }

            /// <summary>
            /// Simply adds a public BBKey to the Subscription type.
            ///   I need this for unsubscribing by BBKey (as opposed to unsubscribing by correlationId)
            /// </summary>
            private class BBSubscriptionType : Subscription
            {
                private readonly string _bbKey;
                public string BBKey { get { return this._bbKey; } }

                public BBSubscriptionType(string key, List<string> listFields, List<string> listSubOptions, CorrelationID id) : base(key, listFields, listSubOptions, id)
                {
                    this._bbKey = key;
                }
            }
        }
    }
}
