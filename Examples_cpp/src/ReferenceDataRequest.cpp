//------------------------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="src/ReferenceDataRequest.cpp" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------------------------

#include <iostream>
#include <time.h>
#include "api_selector.h"

using namespace std;

namespace Examples
{
	void ProcessReferenceDataEvent(Event evt);

	void RunReferenceDataExample()
	{
		SessionOptions soptions;
		soptions.setServerHost("localhost");
		soptions.setServerPort(8194);

		Session session(soptions);
		if(session.start() && session.openService("//blp/refdata"))
		{
			Service refDataSvc = session.getService("//blp/refdata");

            CorrelationId requestID(1); //1 is just some number I picked
            Request request = refDataSvc.createRequest("ReferenceDataRequest");

            //request information for the following securities
            request.append("securities", "SPY US EQUITY");
            request.append("securities", "MSFT US EQUITY");
            request.append("securities", "AAPL 150117C00600000 EQUITY"); //this is a stock option: TICKER yyMMdd[C/P]\d{8} EQUITY
            //request.append("securities", "ZYZZ US EQUITY"); //the code treats securities that start with a "Z" as non-existent

            //include the following simple fields in the result
            //request.append("fields", "ZPX_LAST"); //the code treats a field that starts with a "Z" as a bad field
            request.append("fields", "PX_LAST");
            request.append("fields", "BID");
            request.append("fields", "ASK");
            request.append("fields", "TICKER");
            request.append("fields", "OPT_EXPIRE_DT"); //only stock options have this field

            //request a field that can be overriden and returns bulk data
            request.append("fields", "CHAIN_TICKERS"); //only stocks have this field 
			Element overrides = request.getElement("overrides");
			
            //request only puts
			Element ovrdPutCall = overrides.appendElement();
            ovrdPutCall.setElement("fieldId", "CHAIN_PUT_CALL_TYPE_OVRD");
            ovrdPutCall.setElement("value", "P"); //accepts either "C" for calls or "P" for puts

            //request 5 options in the result
            Element ovrdNumStrikes = overrides.appendElement();
            ovrdNumStrikes.setElement("fieldId", "CHAIN_POINTS_OVRD");
            ovrdNumStrikes.setElement("value", 5); //accepts a positive integer

            //request options that expire on Dec. 20, 2014
            Element ovrdDtExps = overrides.appendElement();
            ovrdDtExps.setElement("fieldId", "CHAIN_EXP_DT_OVRD");
            ovrdDtExps.setElement("value", "20141220"); //accepts dates in the format yyyyMMdd (this is Dec. 20, 2014)

            session.sendRequest(request, requestID);

            bool continueToLoop = true;
            while (continueToLoop)
            {
                Event evt = session.nextEvent();
				switch (evt.eventType())
                {
					case Event::RESPONSE:
						continueToLoop = false; //fall through
					case Event::PARTIAL_RESPONSE:
						ProcessReferenceDataEvent(evt);
						break;
                }
            }
		}
		else
		{
			cerr << "Cannot connect to server";
		}
	}

	void ProcessReferenceDataEvent(Event evt)
	{
		const string level1 = "";
		const string level2 = "\t";
		const string level3 = "\t\t";
		const string level4 = "\t\t\t";

		cout << endl << endl;
		cout << level1 << "EventType = " << evt.eventType();

		MessageIterator iter(evt);
		while(iter.next())
		{
			Message msg = iter.message();

			cout << endl << endl;
			cout << level1 << "correlationID = " << msg.correlationId().asInteger() << endl;
			cout << level1 << "messageType = " << msg.messageType().string() << endl;

			cout << endl << endl;
			Element elmSecurityDataArray = msg.getElement("securityData");
			
			for (size_t valueIndex = 0; valueIndex < elmSecurityDataArray.numValues(); valueIndex++)
			{
				Element elmSecurityData = elmSecurityDataArray.getValueAsElement(valueIndex);

				string security = elmSecurityData.getElementAsString("security");
				cout << level2 << security << endl;

				bool hasFieldErrors = elmSecurityData.hasElement("fieldExceptions", true);
				if (hasFieldErrors)
				{
					Element elmFieldErrors = elmSecurityData.getElement("fieldExceptions");
					for (size_t errorIndex = 0; errorIndex < elmFieldErrors.numValues(); errorIndex++)
					{
						Element fieldError = elmFieldErrors.getValueAsElement(errorIndex);
						string fieldId = fieldError.getElementAsString("fieldId");

						Element errorInfo = fieldError.getElement("errorInfo");
                        string source = errorInfo.getElementAsString("source");
                        int code = errorInfo.getElementAsInt32("code");
                        string category = errorInfo.getElementAsString("category");
                        string strMessage = errorInfo.getElementAsString("message");
                        string subCategory = errorInfo.getElementAsString("subcategory");

						cerr << level3 << "field error:" << endl;
						cerr << level4 << "fieldId = " << fieldId << endl;
						cerr << level4 << "source = " << source << endl;
						cerr << level4 << "code = " << code << endl;
						cerr << level4 << "category = " << category << endl;
						cerr << level4 << "errorMessage = " << strMessage << endl;
						cerr << level4 << "subCategory = " << subCategory << endl;
					}
				}

				bool isSecurityError = elmSecurityData.hasElement("securityError", true);
				if (isSecurityError)
				{
					Element secError = elmSecurityData.getElement("securityError");
                    string source = secError.getElementAsString("source");
                    int code = secError.getElementAsInt32("code");
                    string category = secError.getElementAsString("category");
                    string errorMessage = secError.getElementAsString("message");
                    string subCategory = secError.getElementAsString("subcategory");

					cerr << level3 << "security error:" << endl;
					cerr << level4 << "source = " << source << endl;
					cerr << level4 << "code = " << code << endl;
					cerr << level4 << "category = " << category << endl;
					cerr << level4 << "errorMessage = " << errorMessage << endl;
					cerr << level4 << "subCategory = " << subCategory << endl;
				}
				else
				{
					Element elmFieldData = elmSecurityData.getElement("fieldData");

                    double pxLast = elmFieldData.getElementAsFloat64("PX_LAST");
                    double bid = elmFieldData.getElementAsFloat64("BID");
                    double ask = elmFieldData.getElementAsFloat64("ASK");
                    string ticker = elmFieldData.getElementAsString("TICKER");
					
					cout << level3 << "fields: " << endl;
                    cout << level4 << "PX_LAST = " << pxLast << endl;
                    cout << level4 << "BID = " << bid << endl;
                    cout << level4 << "ASK = " << ask << endl;
                    cout << level4 << "TICKER = " << ticker << endl;

					bool excludeNullElements = true;
					if (elmFieldData.hasElement("CHAIN_TICKERS", excludeNullElements)) //be careful, the excludeNullElements argument is false by default
					{
						Element chainTickers = elmFieldData.getElement("CHAIN_TICKERS");
						for (size_t chainTickerValueIndex = 0; chainTickerValueIndex < chainTickers.numValues(); chainTickerValueIndex++)
						{
                            Element chainTicker = chainTickers.getValueAsElement(chainTickerValueIndex);
                            string strChainTicker = chainTicker.getElementAsString("Ticker");

							cout << level4 << "CHAIN_TICKER = " << strChainTicker << endl;
						}
					}
					else
					{
						cout << level4 << "No CHAIN_TICKER information" << endl;
					}


				}

			}

		}

	}
}