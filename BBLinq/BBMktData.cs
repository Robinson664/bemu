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
        /// <param name="callback">A function that will be called when market data is received.  Use the function's list of FieldDateType objects.</param>
        public static void BBMktData(this IEnumerable<string> bbKeys, IEnumerable<string> fields, Action<IEnumerable<FieldDateType>> callback)
        {
            BBMktDataHelpers.Subscribe(bbKeys, fields, null, callback);
        }

        private static class BBMktDataHelpers
        {
            static BBMktDataHelpers()
            {
                SessionOptions options = new SessionOptions();
                options.ServerHost = "127.0.0.1";
                options.ServerPort = 8194;

                BBMktDataHelpers._session = new Session(options, BBMktDataHelpers.ProcessSubscriptionEvent);
                BBMktDataHelpers._session.StartAsync();
            }

            private readonly static object _syncroot = new object();
            private static bool _isServiceOpened = false;

            private static Session _session;
            private static Action<IEnumerable<FieldDateType>> _callback;
            public static void Subscribe(IEnumerable<string> bbKeys, IEnumerable<string> fields, IEnumerable<string> subOptions, Action<IEnumerable<FieldDateType>> callback)
            {
                BBMktDataHelpers._callback = callback;
                List<string> listFields = fields.ToList(), listSubOptions = null;

                var subs = new List<Subscription>();
                foreach (var key in bbKeys)
                {
                    Subscription sub = new Subscription(key, listFields, listSubOptions, new CorrelationID(NextCorrelationId.Get()));
                    subs.Add(sub);
                }

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
                BBMktDataHelpers._session.Subscribe(subs); //must ensure that the session is opened before subscribing to anything
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
                            List<FieldDateType> fields = new List<FieldDateType>(message.NumElements);
                            string bbKey = message.TopicName;
                            foreach (var item in message.Elements)
                            {
                                if (!item.IsNull)
                                {
                                    FieldDateType fType = new FieldDateType(bbKey, item.Name.ToString(), item.GetValue(), dtNow);
                                    fields.Add(fType);
                                }
                            }
                            BBMktDataHelpers._callback(fields);
                        }
                        break;
                }
            }
        }
    }
}
