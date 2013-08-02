//------------------------------------------------------------------------------
// <copyright project="Examples" file="IntradayTickDataRequest.cs" company="Jordan Robinson">
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

            string security = "SPY US Equity";
            //security = "ZYZZ US EQUITY";  //the code treats securities that start with a "Z" as non-existent
            request.Set("security", security);

            request.Append("eventTypes", "TRADE"); //One of TRADE (default), BID, ASK, BID_BEST, ASK_BEST, MID_PRICE, AT_TRADE, BEST_BID, BEST_ASK (see documentation A.2.6 for explanations)
            request.Append("eventTypes", "BID"); //A request can have multiple eventTypes
            //Note 1) refDataService.ToString() using the Bloomberg API indicates an additional eventType called "SETTLE".  "SETTLE" doesn't seem to produce any results.
            //Note 2) If you request an eventType that isn't supported, the API will throw a KeyNotSupportedException at the "request.Append("eventType", "XXX")" line
            //Note 3) eventType values are case-sensitive.  Requesting "bid" instead of "BID" will throw a KeyNotSupportedException at the "request.Append("eventType", "bid")" line

            request.Set("startDateTime", new Datetime(DateTime.Today.AddHours(9.5999).ToUniversalTime()));
            request.Set("endDateTime", new Datetime(DateTime.Today.AddHours(9.6).ToUniversalTime())); //goes back at most 140 days (documentation section 7.2.3)

            //A comma delimited list of exchange condition codes associated with the event. Review QR<GO> for more information on each code returned.
            request.Set("includeConditionCodes", false); //Optional bool. Valid values are true and false (default = false)

            //Returns all ticks, including those with condition codes.
            request.Set("includeNonPlottableEvents", false); //Optional bool. Valid values are true and false (default = false)

            //The exchange code where this tick originated. Review QR<GO> for more information.
            request.Set("includeExchangeCodes", false); //Optional bool. Valid values are true and false (default = false)

            //Option on whether to return EIDs for the security.
            request.Set("returnEids", false); //Optional bool. Valid values are true and false (default = false)

            //The broker code for Canadian, Finnish, Mexican, Philippine, and Swedish equities only.
            //  The Market Maker Lookup screen, MMTK<GO>, displays further information on market makers and their corresponding codes.
            request.Set("includeBrokerCodes", false); //Optional bool. Valid values are true and false (default = false)

            //The Reporting Party Side. The following values appear:
            //  -B: A customer transaction where the dealer purchases securities from the customer.
            //  -S: A customer transaction where the dealer sells securities to the customer.
            //  -D: An inter-dealer transaction (always from the sell side).
            request.Set("includeRpsCodes", false); //Optional bool. Valid values are true and false (default = false)

            //The BIC, or Bank Identifier Code, as a 4-character unique identifier for each bank that executed and reported the OTC trade, as required by MiFID.
            //  BICs are assigned and maintained by SWIFT (Society for Worldwide Interbank Financial Telecommunication).
            //  The MIC is the Market Identifier Code, and this indicates the venue on which the trade was executed.
            request.Set("includeBicMicCodes", false); //Optional bool. Valid values are true and false (default = false)

            {
                //refDataService.ToString() using the Bloomberg API specifies several boolean overrides that the API documentation doesn't (doc version 2.40).  These are:
                //   forcedDelay, includeSpreadPrice, includeYield, includeActionCodes, includeIndicatorCodes, includeTradeTime, and includeUpfrontPrice
                //These overrides are optional.  Their meanings may be obvious given their names, but I can't be sure.

                request.Set("forcedDelay", false); //Optional bool. Undocumented. default = ???
                request.Set("includeSpreadPrice", false); //Optional bool. Undocumented. default = ???
                request.Set("includeYield", false); //Optional bool. Undocumented. default = ???
                request.Set("includeActionCodes", false); //Optional bool. Undocumented. default = ???
                request.Set("includeIndicatorCodes", false); //Optional bool. Undocumented. default = ???
                request.Set("includeTradeTime", false); //Optional bool. Undocumented. default = ???
                request.Set("includeUpfrontPrice", true); //Optional bool. Undocumented. default = ???
            }

            CorrelationID corr = new CorrelationID(17);

            session.SendRequest(request, corr);

            bool continueToLoop = true;
            while (continueToLoop)
            {
                Event evt = session.NextEvent();

                switch (evt.Type)
                {
                    case Event.EventType.RESPONSE:
                        IntradayTickDataRequest.ProcessResponse(evt, security);
                        continueToLoop = false;
                        break;
                    case Event.EventType.PARTIAL_RESPONSE:
                        IntradayTickDataRequest.ProcessResponse(evt, security);
                        break;
                }
            }
        }

        private static void ProcessResponse(Event evt, string security)
        {
            //Note that the IntradayTickResponse does not include the name of the requested security anywhere
            Console.WriteLine(security);

            foreach (var msg in evt.GetMessages())
            {
                bool isSecurityError = msg.HasElement("responseError", true);

                if (isSecurityError)
                {
                    Element secError = msg["responseError"];
                    string source = secError.GetElementAsString("source");
                    int code = secError.GetElementAsInt32("code");
                    string category = secError.GetElementAsString("category");
                    string errorMessage = secError.GetElementAsString("message");
                    string subCategory = secError.GetElementAsString("subcategory");

                    Console.WriteLine("response error");
                    Console.WriteLine(string.Format("source = {0}", source));
                    Console.WriteLine(string.Format("code = {0}", code));
                    Console.WriteLine(string.Format("category = {0}", category));
                    Console.WriteLine(string.Format("errorMessage = {0}", errorMessage));
                    Console.WriteLine(string.Format("subCategory = {0}", subCategory));
                }
                else
                {
                    Element elmTickDataArr = msg["tickData"];
                    Element elmTickData = elmTickDataArr["tickData"];

                    for (int valueCount = 0; valueCount < elmTickData.NumValues; valueCount++)
                    {
                        Element elmTickDataValue = elmTickData.GetValueAsElement(valueCount);

                        DateTime time = elmTickDataValue.GetElementAsTime("time").ToSystemDateTime();
                        string type = elmTickDataValue.GetElementAsString("type");
                        double value = elmTickDataValue.GetElementAsFloat64("value");
                        int size = elmTickDataValue.GetElementAsInt32("size");

                        Console.WriteLine(string.Format("{0:HH:mm:ss}: {1}, {2} @ {3}", time, type, size, value));
                    }
                }

            }
        }

    }
}
