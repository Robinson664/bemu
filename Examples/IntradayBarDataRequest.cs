using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using BEmu; //un-comment this line to use the Bloomberg API Emulator
//using Bloomberglp.Blpapi; //un-comment this line to use the actual Bloomberg API

namespace Examples
{
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
            foreach (var msg in evt.GetMessages())
            {
                //The TIME in the response appears to be the *start* of the time interval
                Console.WriteLine(msg);
            }
        }

    }
}
