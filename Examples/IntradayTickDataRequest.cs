using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using BEmu; //un-comment this line to use the Bloomberg API Emulator
//using Bloomberglp.Blpapi; //un-comment this line to use the actual Bloomberg API

namespace Examples
{
    public static class IntradayTickDataRequest
    {
        /// <summary>
        /// This example Bloomberg request starts a session meant for Reference Requests and requests a few fields for several securities.
        /// I pulled this example code almost line-for-line from section C.1 of the Bloomberg API Developer's Guide
        /// </summary>
        public static void RunExample()
        {
            SessionOptions sessionOptions = new SessionOptions();
            sessionOptions.ServerHost = "127.0.0.1";
            sessionOptions.ServerPort = 8194;

            Session session = new Session(sessionOptions);
            session.Start();
            session.OpenService("//blp/refdata");

            Service refDataService = session.GetService("//blp/refdata");
            Request request = refDataService.CreateRequest("IntradayTickRequest");
            request.Set("security", "CMG US Equity");
            request.Append("eventTypes", "TRADE"); //in TRADE (default), BID, ASK, BID_BEST, ASK_BEST, MID_PRICE, AT_TRADE, BEST_BID, BEST_ASK
            request.Set("startDateTime", new Datetime(DateTime.Today.AddHours(9.5)));
            request.Set("endDateTime", new Datetime(DateTime.Today.AddHours(10).AddMinutes(1))); //goes back at most 140 days (documentation section 7.2.3)
            request.Set("includeConditionCodes", true); //true or false (default)
            request.Set("includeNonPlottableEvents", false); //true or false (default)
            request.Set("includeExchangeCodes", false); //true or false (default)
            request.Set("returnEids", false); //true or false (false)
            request.Set("includeBrokerCodes", false); //true or false (default)
            request.Set("includeRpsCodes", false); //true or false (default)
            request.Set("includeBicMicCodes", false); //true or false (default)

            CorrelationID corr = new CorrelationID(17);

            session.SendRequest(request, corr);
            
            bool continueToLoop = true;
            while (continueToLoop)
            {
                Event evt = session.NextEvent();

                switch (evt.Type)
                {
                    case Event.EventType.RESPONSE:
                        foreach (var msg in evt.GetMessages())
                        {
                            Console.WriteLine(msg);
                        }
                        continueToLoop = false;
                        break;
                    case Event.EventType.PARTIAL_RESPONSE:
                        foreach (var msg in evt.GetMessages())
                        {
                            Console.WriteLine(msg);
                        }
                        break;
                }
            }
        }
    }
}
