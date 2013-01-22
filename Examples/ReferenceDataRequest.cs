using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using BEmu; //un-comment this line to use the Bloomberg API Emulator
//using Bloomberglp.Blpapi; //un-comment this line to use the actual Bloomberg API

namespace Examples
{
    public static class ReferenceDataRequest
    {
        /// <summary>
        /// This example Bloomberg request starts a session meant for Reference Requests and requests a few fields for several securities.
        /// I pulled this example code almost line-for-line from section C.1 of the Bloomberg API Developer's Guide
        /// </summary>
        public static void RunExample()
        {
            SessionOptions sessionOptions = new SessionOptions();
            sessionOptions.ServerHost = "localhost";
            sessionOptions.ServerPort = 8194;

            Session session = new Session(sessionOptions);
            if (!session.Start())
            {
                System.Console.WriteLine("Could not start session.");
                System.Environment.Exit(1);
            }
            if (!session.OpenService("//blp/refdata"))
            {
                System.Console.WriteLine("Could not open service //blp/refdata");
                System.Environment.Exit(1);
            }
            CorrelationID requestID = new CorrelationID(1);
            Service refDataSvc = session.GetService("//blp/refdata");
            Request request = refDataSvc.CreateRequest("ReferenceDataRequest");

            //request information for the following securities
            request.Append("securities", "IBM US EQUITY");
            request.Append("securities", "SPY US EQUITY");
            request.Append("securities", "MSFT US EQUITY");
            request.Append("securities", "AAPL 150117C00600000 EQUITY"); //this is a stock option: TICKER yyMMdd[C/P]\d{8} EQUITY

            //include the following simple fields in the result
            request.Append("fields", "PX_LAST");
            request.Append("fields", "BID");
            request.Append("fields", "ASK");
            request.Append("fields", "OPT_EXPIRE_DT");

            //request a field that can be overriden and returns bulk data
            request.Append("fields", "CHAIN_TICKERS");
            Element overrides = request["overrides"];

            //request only puts
            Element ovrdPutCall = overrides.AppendElement();
            ovrdPutCall.SetElement("fieldId", "CHAIN_PUT_CALL_TYPE_OVRD");
            ovrdPutCall.SetElement("value", "P"); //accepts either "C" for calls or "P" for puts

            //request 5 options in the result
            Element ovrdNumStrikes = overrides.AppendElement();
            ovrdNumStrikes.SetElement("fieldId", "CHAIN_POINTS_OVRD");
            ovrdNumStrikes.SetElement("value", 5); //accepts a positive integer

            //request options that expire on Dec. 20, 2014
            Element ovrdDtExps = overrides.AppendElement();
            ovrdDtExps.SetElement("fieldId", "CHAIN_EXP_DT_OVRD");
            ovrdDtExps.SetElement("value", "20141220"); //accepts dates in the format yyyyMMdd

            session.SendRequest(request, requestID);

            bool continueToLoop = true;
            while (continueToLoop)
            {
                Event eventObj = session.NextEvent();
                switch (eventObj.Type)
                {
                    case Event.EventType.RESPONSE: // final event
                        continueToLoop = false;
                        handleResponseEvent(eventObj);
                        break;
                    case Event.EventType.PARTIAL_RESPONSE:
                        handleResponseEvent(eventObj);
                        break;
                    default:
                        handleOtherEvent(eventObj);
                        break;
                }
            }

        }

        private static void handleResponseEvent(Event eventObj)
        {
            System.Console.WriteLine("EventType =" + eventObj.Type);
            foreach (Message message in eventObj.GetMessages())
            {
                System.Console.WriteLine("correlationID=" + message.CorrelationID);
                System.Console.WriteLine("messageType =" + message.MessageType);
                Console.WriteLine(message.ToString());
            }
        }

        private static void handleOtherEvent(Event eventObj)
        {
            System.Console.WriteLine("EventType=" + eventObj.Type);
            foreach (Message message in eventObj.GetMessages())
            {
                System.Console.WriteLine("correlationID=" + message.CorrelationID);
                System.Console.WriteLine("messageType=" + message.MessageType);
                Console.WriteLine(message.ToString());
                if (Event.EventType.SESSION_STATUS == eventObj.Type && message.MessageType.Equals("SessionTerminated"))
                {
                    System.Console.WriteLine("Terminating: " + message.MessageType);
                }
            }
        }
    }
}
