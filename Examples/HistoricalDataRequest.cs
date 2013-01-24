using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using BEmu; //un-comment this line to use the Bloomberg API Emulator
//using Bloomberglp.Blpapi; //un-comment this line to use the actual Bloomberg API

namespace Examples
{
    public static class HistoricalDataRequest
    {
        public static void RunExample()
        {
            SessionOptions sessionOptions = new SessionOptions();
            sessionOptions.ServerHost = "127.0.0.1";
            sessionOptions.ServerPort = 8194;

            Session session = new Session(sessionOptions);
            session.Start();
            session.OpenService("//blp/refdata");

            Service service = session.GetService("//blp/refdata");

            Request request = service.CreateRequest("HistoricalDataRequest");

            //request information for the following securities
            request.Append("securities", "IBM US EQUITY");
            request.Append("securities", "SPY US EQUITY");
            request.Append("securities", "AAPL 150117C00600000 EQUITY"); //this is a stock option: TICKER yyMMdd[C/P]\d{8} EQUITY

            //include the following simple fields in the result
            request.Append("fields", "BID");
            request.Append("fields", "ASK");

            //Historical requests allow a few overrides.  See the developer's guide A.2.4 for more information.

            request.Set("startDate", DateTime.Today.AddMonths(3).ToString("yyyyMMdd")); //Request that the information start three months ago from today.  This override is required.
            request.Set("endDate", DateTime.Today.AddDays(-3).ToString("yyyyMMdd")); //Request that the information end three days before today.  This is an optional override.  The default is today.
            
            //Determine the frequency and calendar type of the output. To be used in conjunction with Period Selection.
            request.Set("periodicityAdjustment", "CALENDAR"); //Optional string.  Valid values are ACTUAL (default), CALENDAR, and FISCAL.

            //Determine the frequency of the output. To be used in conjunction with Period Adjustment.
            request.Set("periodicitySelection", "DAILY"); //Optional string.  Valid values are DAILY (default), WEEKLY, MONTHLY, QUARTERLY, SEMI_ANNUALLY, and YEARLY

            //Sets quote to Price or Yield for a debt instrument whose default value is quoted in yield (depending on pricing source).
            request.Set("pricingOption", "PRICING_OPTION_PRICE"); //Optional string.  Valid values are PRICING_OPTION_PRICE (default) and PRICING_OPTION_YIELD

            //Adjust for "change on day"
            request.Set("adjustmentNormal", true); //Optional bool. Valid values are true and false (default = false)

            //Adjusts for Anormal Cash Dividends
            request.Set("adjustmentAbnormal", false); //Optional bool. Valid values are true and false (default = false)

            //Capital Changes Defaults
            request.Set("adjustmentSplit", true); //Optional bool. Valid values are true and false (default = false)

            //The maximum number of data points to return, starting from the startDate
            request.Set("maxDataPoints", 5); //Optional integer.  Valid values are positive integers.  The default is unspecified in which case the response will have all data points between startDate and endDate

            //Indicates whether to use the average or the closing price in quote calculation.
            request.Set("overrideOption", "OVERRIDE_OPTION_CLOSE"); //Optional string.  Valid values are OVERRIDE_OPTION_GPA for an average and OVERRIDE_OPTION_CLOSE (default) for the closing price

            CorrelationID requestID = new CorrelationID(1);
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
