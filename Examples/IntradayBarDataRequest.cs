//------------------------------------------------------------------------------
// <copyright project="Examples" file="IntradayBarDataRequest.cs" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

namespace Examples
{
    using System;
    using System.Collections.Generic;
    using System.Linq;
    using System.Text;

    using BEmu; //un-comment this line to use the Bloomberg API Emulator
    //using Bloomberglp.Blpapi; //un-comment this line to use the actual Bloomberg API

    public static class IntradayBarDataRequest
    {
        public static void RunExample()
        {
            SessionOptions soptions = new SessionOptions();
            soptions.ServerHost = "127.0.0.1";
            soptions.ServerPort = 8194;

            Session session = new Session(soptions);
            if (session.Start() && session.OpenService("//blp/refdata"))
            {
                Service service = session.GetService("//blp/refdata");
                Request request = service.CreateRequest("IntradayBarRequest");

                string security = "SPY US EQUITY";
                request.Set("security", security); //required

                request.Set("eventType", "TRADE"); //TRADE(default), BID, ASK, BID_BEST, ASK_BEST, BEST_BID, BEST_ASK, BID_YIELD, ASK_YIELD, MID_PRICE, AT_TRADE, SETTLE
                //note that BID_YIELD, ASK_YIELD, MID_PRICE, AT_TRADE, and SETTLE don't appear in the API documentation, but you will see them if you call "service.ToString() using the actual Bloomberg API"

                request.Set("interval", 60); // bar interval in minutes (despite A.2.8, the interval cannot be omitted.  it must be an int32 between 1 and 1440)

                //data goes back no farther than 140 days (7.2.4)
                DateTime dtStart = DateTime.Today.AddDays(-1); //yesterday
                request.Set("startDateTime", new Datetime(dtStart.AddHours(9.5).ToUniversalTime())); //UTC time
                request.Set("endDateTime", new Datetime(dtStart.AddHours(16).ToUniversalTime())); //UTC time

                session.SendRequest(request, new CorrelationID(-999));

                bool continueLoop = true;
                while (continueLoop)
                {
                    Event evt = session.NextEvent();
                    switch (evt.Type)
                    {
                        case Event.EventType.RESPONSE:
                            ProcessResponse(evt, security);
                            continueLoop = false;
                            break;
                        case Event.EventType.PARTIAL_RESPONSE:
                            ProcessResponse(evt, security);
                            break;
                    }
                }

            }
        }

        private static void ProcessResponse(Event evt, string security)
        {
            Console.WriteLine(security);
            foreach (var msg in evt.GetMessages())
            {
                Element elmBarTickDataArray = msg["barData"]["barTickData"];
                for (int valueIndex = 0; valueIndex < elmBarTickDataArray.NumValues; valueIndex++)
                {
                    Element elmBarTickData = elmBarTickDataArray.GetValueAsElement(valueIndex);

                    DateTime dtTick = elmBarTickData.GetElementAsDatetime("time").ToSystemDateTime();

                    double open = elmBarTickData.GetElementAsFloat64("open");
                    double high = elmBarTickData.GetElementAsFloat64("high");
                    double low = elmBarTickData.GetElementAsFloat64("low");
                    double close = elmBarTickData.GetElementAsFloat64("close");

                    int numEvents = elmBarTickData.GetElementAsInt32("numEvents");
                    long volume = elmBarTickData.GetElementAsInt64("volume");
                    double value = elmBarTickData.GetElementAsFloat64("value");

                    Console.WriteLine(dtTick.ToString("HH:mm:ss"));
                    Console.WriteLine(string.Format("\t open = {0:c2}", open));
                    Console.WriteLine(string.Format("\t high = {0:c2}", high));
                    Console.WriteLine(string.Format("\t low = {0:c2}", low));
                    Console.WriteLine(string.Format("\t close = {0:c2}", close));

                    Console.WriteLine(string.Format("\t numEvents = {0:n0}", numEvents));
                    Console.WriteLine(string.Format("\t volume = {0:n0}", volume));
                    Console.WriteLine(string.Format("\t value = {0:n0}", value));

                    Console.WriteLine();
                }
            }
        }

    }
}
