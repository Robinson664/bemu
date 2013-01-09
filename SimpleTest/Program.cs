using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using BBLinq;
using System.Threading;
using System.Threading.Tasks;

using BEmu;
//using Bloomberglp.Blpapi;

namespace SimpleTest
{
    class Program
    {
        static void Main(string[] args)
        {
            Program.DoHist();

            Console.ReadLine();
            //BBMktDataType.Dispose();
        }

        #region BBLINQ
        private static void DoLinq()
        {
            string[] keys = { "AAPL US 01/19/13 C500 EQUITY", "AAPL US EQUITY", "C H3 COMDTY" };
            string[] fields = { "LAST_TRADE", "PX_LAST" };

            foreach (var field in keys.BBRefData(fields))
            {
                Console.WriteLine(field.ToString());
            }

            //keys.BBMktData(fields, (items) =>
            //    {
            //        foreach (var item in items)
            //        {
            //            if (fields.Contains(item.FieldName))
            //                Console.WriteLine(item.ToString());
            //        }
            //    });
        }
        #endregion

        #region static
        private static void DoRef()
        {
            string bbkey1 = "AAPL US EQUITY";
            string bbkey2 = "IBM US EQUITY";
            string bbkey3 = "SPY US EQUITY";

            SessionOptions sessionOptions = new SessionOptions();
            sessionOptions.ServerHost = "127.0.0.1";
            sessionOptions.ServerPort = 8194;

            Session session = new Session(sessionOptions);
            session.Start();
            session.OpenService("//blp/refdata");

            Service service = session.GetService("//blp/refdata");

            Request request = service.CreateRequest("ReferenceDataRequest");

            Name nameSecurities = new Name("securities");
            Name nameFields = new Name("fields");
            request.Append(nameSecurities, bbkey1);
            request.Append(nameSecurities, bbkey2);
            request.Append(nameSecurities, bbkey3);
            request.Append(nameFields, "Bid");
            request.Append(nameFields, "Ask");
            request.Append(nameFields, "CHAIN_TICKERS");

            Element elmOverrides = request["overrides"];

            Element elm1 = elmOverrides.AppendElement();
            elm1.SetElement("fieldId", "CHAIN_PUT_CALL_TYPE_OVRD");
            elm1.SetElement("value", "P");

            Element elm2 = elmOverrides.AppendElement();
            elm2.SetElement("fieldId", "CHAIN_POINTS_OVRD");
            elm2.SetElement("value", 5);

            CorrelationID corr = new CorrelationID(4);

            session.SendRequest(request, corr);

            bool continueToLoop = true;
            while (continueToLoop)
            {
                Event eventObj = session.NextEvent();

                switch (eventObj.Type)
                {
                    case Event.EventType.RESPONSE: // final event
                        continueToLoop = false;
                        Program.ProcessResponseRef(eventObj, corr);
                        break;
                    case Event.EventType.PARTIAL_RESPONSE:
                        Program.ProcessResponseRef(eventObj, corr);
                        break;
                }
            }
        }

        private static void ProcessResponseRef(Event eventObj, CorrelationID corr)
        {
            Name nameSecurityData = new Name("securityData");
            Name nameSecurity = new Name("security");
            Name nameFieldData = new Name("fieldData");

            foreach (var message in eventObj.GetMessages()) //loop through each message
            {
                if (message.CorrelationID.Value == corr.Value)
                {
                    Element elmSecDataArr = message.GetElement(nameSecurityData);
                    for (int i = 0; i < elmSecDataArr.NumValues; i++) //loop through each security
                    {
                        Element elmSecData = elmSecDataArr.GetValueAsElement(i);

                        string bbkey = elmSecData.GetElementAsString(nameSecurity);
                        Element elmFieldData = elmSecData.GetElement(nameFieldData);

                        for (int j = 0; j < elmFieldData.NumElements; j++)
                        {
                            Element elmSingleField = elmFieldData.GetElement(j);
                            string strName = elmSingleField.Name.ToString();
                            object value = elmSingleField.GetValue();

                            Console.WriteLine(string.Format("{0}: {1} = {2}", bbkey, strName, value));
                        }

                    }
                }
            }
        }
        #endregion

        #region hist
        private static void DoHist()
        {
            string bbkey1 = "AAPL US EQUITY";
            string bbkey2 = "IBM US EQUITY";
            DateTime dtStart = new DateTime(2012, 8, 28);

            SessionOptions sessionOptions = new SessionOptions();
            sessionOptions.ServerHost = "127.0.0.1";
            sessionOptions.ServerPort = 8194;

            Session session = new Session(sessionOptions);
            session.Start();
            session.OpenService("//blp/refdata");

            Service service = session.GetService("//blp/refdata");

            Request request = service.CreateRequest("HistoricalDataRequest");

            Name nameSecurities = new Name("securities");
            Name nameFields = new Name("fields");
            Name nameDtStart = new Name("startDate");
            Name namePeriodicityAdjustment = new Name("periodicityAdjustment");
            Name namePeriodicitySelection = new Name("periodicitySelection");
            Name namePricingOption = new Name("pricingOption");
            Name nameOverrideOption = new Name("overrideOption");
            Name nameAdjustmentNormal = new Name("adjustmentNormal");
            Name nameAdjustmentAbnormal = new Name("adjustmentAbnormal");
            Name nameAdjustmentSplit = new Name("adjustmentSplit");
            Name nameMaxDataPoints = new Name("maxDataPoints");

            request.Append(nameSecurities, bbkey1);
            request.Append(nameSecurities, bbkey2);
            request.Append(nameFields, "Bid");
            request.Append(nameFields, "Ask");

            request.Set(nameDtStart, dtStart.ToString("yyyyMMdd"));
            request.Set(namePeriodicityAdjustment, "CALENDAR");
            request.Set(namePeriodicitySelection, "WEEKLY");
            request.Set(namePricingOption, "PRICING_OPTION_YIELD");
            request.Set(nameOverrideOption, "OVERRIDE_OPTION_GPA");
            request.Set(nameAdjustmentNormal, false);
            request.Set(nameAdjustmentAbnormal, false);
            request.Set(nameAdjustmentSplit, false);
            request.Set(nameMaxDataPoints, 5);

            CorrelationID corr = new CorrelationID(4);

            session.SendRequest(request, corr);

            bool continueToLoop = true;
            while (continueToLoop)
            {
                Event eventObj = session.NextEvent();

                switch (eventObj.Type)
                {
                    case Event.EventType.RESPONSE: // final event
                        continueToLoop = false;
                        Program.ProcessResponseHist(eventObj, corr);
                        break;
                    case Event.EventType.PARTIAL_RESPONSE:
                        Program.ProcessResponseHist(eventObj, corr);
                        break;
                }
            }
        }

        private static void ProcessResponseHist(Event eventObj, CorrelationID corr)
        {
            Name nameSecurityData = new Name("securityData");
            Name nameSecurity = new Name("security");
            Name nameFieldData = new Name("fieldData");

            foreach (var message in eventObj.GetMessages()) //loop through each message
            {
                if (message.CorrelationID.Value == corr.Value)
                {
                    Element elmSecData = message.GetElement(nameSecurityData);
                    string bbkey = elmSecData.GetElementAsString(nameSecurity);
                    Element elmFieldData = elmSecData.GetElement(nameFieldData);

                    for (int i = 0; i < elmSecData.NumValues; i++) //loop through each security
                    {
                        for (int j = 0; j < elmFieldData.NumValues; j++)
                        {
                            Element elmData = elmFieldData.GetValueAsElement(j);
                            foreach (var elm in elmData.Elements)
                            {
                                string fieldName = elm.Name.ToString();
                                object fieldValue = elm.GetValue();
                                Console.WriteLine(string.Format("{2}: {0} = {1}", fieldName, fieldValue, bbkey));

                                string str = message.AsElement.ToString();
                            }
                            Console.WriteLine();
                        }
                    }

                }
            }
        }
        #endregion
                
        #region mkt
        private static int _correlation = 0;
        private static void DoMkt()
        {
            SessionOptions options = new SessionOptions();
            options.ServerHost = "127.0.0.1";
            options.ServerPort = 8194;

            Session session = new Session(options, Program.ProcessSubscriptionEvent);
            session.StartAsync();

            Task.Factory.StartNew(() =>
                {
                    Thread.Sleep(TimeSpan.FromSeconds(5));

                    session.Cancel(_corr);
                    Console.WriteLine("unsub");
                });
        }

        private static CorrelationID _corr;
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
                                //this must happen before subscribing to any data
                                CorrelationID corr = new CorrelationID(Program._correlation++);
                                session.OpenServiceAsync("//blp/mktdata", corr);

                                List<string> fields = new string[] { "bid", "ask" }.ToList();
                                List<Subscription> subs = new List<Subscription>();
                                subs.Add(new Subscription("AAPL US EQUITY", fields));
                                subs.Add(new Subscription("IBM US EQUITY", fields));
                                subs.Add(new Subscription("SPY US EQUITY", fields));
                                _corr = subs[1].CorrelationID;

                                session.Subscribe(subs);
                            }
                            catch (Exception)
                            {
                                Console.Error.WriteLine("Could not open //blp/mktdata for async");
                            }
                        }
                    }
                    break;

                case Event.EventType.SERVICE_STATUS:
                    break;

                case Event.EventType.SUBSCRIPTION_STATUS:
                    foreach (var msg in eventObj.GetMessages())
                    {
                        //var elm1 = msg.AsElement;
                        foreach (var elm in msg.Elements)
                        {
                            
                        }
                    }
                    break;

                case Event.EventType.SUBSCRIPTION_DATA:
                    DateTime dtNow = DateTime.Now;
                    foreach (var message in eventObj.GetMessages()) //MarketDataEvents
                    {
                        string bbKey = message.TopicName;
                        foreach (var item in message.Elements)
                        {
                            if (!item.IsNull)
                            {
                                string field = item.Name.ToString().ToUpper();
                                object value = item.GetValue();

                                if (field == "BID" || field == "ASK" || field == "DATE")
                                {
                                    Console.WriteLine(string.Format("{0}: {1} = {2}", bbKey, field, value));
                                }
                            }
                        }
                    }
                    break;

                default:
                    break;
            }
        }

        #endregion

    }
}
