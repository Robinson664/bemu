//------------------------------------------------------------------------------
// <copyright project="Examples" file="ReferenceDataRequest.cs" company="Jordan Robinson">
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
            if (session.Start() && session.OpenService("//blp/refdata"))
            {
                Service refDataSvc = session.GetService("//blp/refdata");
                if (refDataSvc == null)
                {
                    Console.WriteLine("Cannot get service");
                }
                else
                {
                    CorrelationID requestID = new CorrelationID(1);
                    Request request = refDataSvc.CreateRequest("ReferenceDataRequest");

                    //request information for the following securities
                    request.Append("securities", "SPY US EQUITY");
                    request.Append("securities", "MSFT US EQUITY");
                    request.Append("securities", "AAPL 150117C00600000 EQUITY"); //this is a stock option: TICKER yyMMdd[C/P]\d{8} EQUITY
                    //request.Append("securities", "ZYZZ US EQUITY"); //the code treats securities that start with a "Z" as non-existent

                    //include the following simple fields in the result
                    //request.Append("fields", "ZPX_LAST"); //the code treats a field that starts with a "Z" as a bad field
                    request.Append("fields", "PX_LAST");
                    request.Append("fields", "BID");
                    request.Append("fields", "ASK");
                    request.Append("fields", "TICKER");
                    request.Append("fields", "OPT_EXPIRE_DT"); //only stock options have this field

                    //request a field that can be overriden and returns bulk data
                    request.Append("fields", "CHAIN_TICKERS"); //only stocks have this field 
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
                    ovrdDtExps.SetElement("value", "20141220"); //accepts dates in the format yyyyMMdd (this is Dec. 20, 2014)

                    session.SendRequest(request, requestID);

                    bool continueToLoop = true;
                    while (continueToLoop)
                    {
                        Event eventObj = session.NextEvent();
                        switch (eventObj.Type)
                        {
                            case Event.EventType.RESPONSE: // final event
                                continueToLoop = false;
                                ReferenceDataRequest.handleResponseEvent(eventObj);
                                break;
                            case Event.EventType.PARTIAL_RESPONSE:
                                ReferenceDataRequest.handleResponseEvent(eventObj);
                                break;
                            default:
                                ReferenceDataRequest.handleOtherEvent(eventObj);
                                break;
                        }
                    }
                }
            }
            else
            {
                Console.WriteLine("Cannot connect to server.  Check that the server host is \"localhost\" or \"127.0.0.1\" and that the server port is 8194.");
            }
        }

        private static void handleResponseEvent(Event eventObj)
        {
            Console.WriteLine();
            Console.WriteLine();
            Console.WriteLine("EventType =" + eventObj.Type);
            foreach (Message message in eventObj.GetMessages())
            {
                Console.WriteLine();
                Console.WriteLine();
                Console.WriteLine("correlationID=" + message.CorrelationID);
                Console.WriteLine("messageType =" + message.MessageType);

                Element elmSecurityDataArray = message["securityData"];

                for (int valueIndex = 0; valueIndex < elmSecurityDataArray.NumValues; valueIndex++)
                {
                    Element elmSecurityData = elmSecurityDataArray.GetValueAsElement(valueIndex);

                    string security = elmSecurityData.GetElementAsString("security");
                    Console.WriteLine(security);

                    bool hasFieldErrors = elmSecurityData.HasElement("fieldExceptions", true);
                    if (hasFieldErrors)
                    {
                        Element elmFieldErrors = elmSecurityData["fieldExceptions"];
                        for (int errorIndex = 0; errorIndex < elmFieldErrors.NumValues; errorIndex++)
                        {
                            Element fieldError = elmFieldErrors.GetValueAsElement(errorIndex);
                            string fieldId = fieldError.GetElementAsString("fieldId");

                            Element errorInfo = fieldError["errorInfo"];
                            string source = errorInfo.GetElementAsString("source");
                            int code = errorInfo.GetElementAsInt32("code");
                            string category = errorInfo.GetElementAsString("category");
                            string strMessage = errorInfo.GetElementAsString("message");
                            string subCategory = errorInfo.GetElementAsString("subcategory");

                            Console.Error.WriteLine();
                            Console.Error.WriteLine();
                            Console.Error.WriteLine("\tfield error: " + security);
                            Console.Error.WriteLine(string.Format("\tfieldId = {0}", fieldId));
                            Console.Error.WriteLine(string.Format("\tsource = {0}", source));
                            Console.Error.WriteLine(string.Format("\tcode = {0}", code));
                            Console.Error.WriteLine(string.Format("\tcategory = {0}", category));
                            Console.Error.WriteLine(string.Format("\terrorMessage = {0}", strMessage));
                            Console.Error.WriteLine(string.Format("\tsubCategory = {0}", subCategory));
                        }
                    }

                    bool isSecurityError = elmSecurityData.HasElement("securityError", true);
                    if (isSecurityError)
                    {
                        Element secError = elmSecurityData["securityError"];
                        string source = secError.GetElementAsString("source");
                        int code = secError.GetElementAsInt32("code");
                        string category = secError.GetElementAsString("category");
                        string errorMessage = secError.GetElementAsString("message");
                        string subCategory = secError.GetElementAsString("subcategory");

                        Console.Error.WriteLine();
                        Console.Error.WriteLine();
                        Console.Error.WriteLine("\tsecurity error");
                        Console.Error.WriteLine(string.Format("\tsource = {0}", source));
                        Console.Error.WriteLine(string.Format("\tcode = {0}", code));
                        Console.Error.WriteLine(string.Format("\tcategory = {0}", category));
                        Console.Error.WriteLine(string.Format("\terrorMessage = {0}", errorMessage));
                        Console.Error.WriteLine(string.Format("\tsubCategory = {0}", subCategory));
                    }
                    else
                    {
                        Element elmFieldData = elmSecurityData["fieldData"];

                        double pxLast = elmFieldData.GetElementAsFloat64("PX_LAST");
                        double bid = elmFieldData.GetElementAsFloat64("BID");
                        double ask = elmFieldData.GetElementAsFloat64("ASK");
                        string ticker = elmFieldData.GetElementAsString("TICKER");

                        Console.WriteLine();
                        Console.WriteLine();
                        Console.WriteLine("\tPX_LAST = " + pxLast.ToString());
                        Console.WriteLine("\tBID = " + bid.ToString());
                        Console.WriteLine("\tASK = " + ask.ToString());
                        Console.WriteLine("\tTICKER = " + ticker.ToString());

                        bool excludeNullElements = true;
                        if (elmFieldData.HasElement("CHAIN_TICKERS", excludeNullElements)) //be careful, the excludeNullElements argument is false by default
                        {
                            Element chainTickers = elmFieldData["CHAIN_TICKERS"];
                            for (int chainTickerValueIndex = 0; chainTickerValueIndex < chainTickers.NumValues; chainTickerValueIndex++)
                            {
                                Element chainTicker = chainTickers.GetValueAsElement(chainTickerValueIndex);
                                string strChainTicker = chainTicker.GetElementAsString("Ticker");

                                Console.WriteLine("\tCHAIN_TICKER = " + strChainTicker.ToString());
                            }
                        }
                        else
                        {
                            Console.WriteLine("\tNo CHAIN_TICKER information");
                        }
                    }

                }
            }
        }

        private static void handleOtherEvent(Event eventObj)
        {
            Console.WriteLine("EventType=" + eventObj.Type);
            foreach (Message message in eventObj.GetMessages())
            {
                Console.WriteLine("correlationID=" + message.CorrelationID);
                Console.WriteLine("messageType=" + message.MessageType);
                Console.WriteLine(message.ToString());
                if (Event.EventType.SESSION_STATUS == eventObj.Type && message.MessageType.Equals("SessionTerminated"))
                {
                    Console.WriteLine("Terminating: " + message.MessageType);
                }
            }
        }
    }
}
