//------------------------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="src/IntradayTickRequest.cpp" company="Jordan Robinson">
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
	void ProcessIntradayTickEvent(Event evt, const char* security);

	void RunIntradayTickExample()
	{
		SessionOptions soptions;
		soptions.setServerHost("localhost");
		soptions.setServerPort(8194);

		Session session(soptions);
		if(session.start() && session.openService("//blp/refdata"))
		{
			Service refDataSvc = session.getService("//blp/refdata");
			const char* security = "MSFT US Equity";
			
			Request request = refDataSvc.createRequest("IntradayTickRequest");

			//security = "ZYZZ US EQUITY";  //the code treats securities that start with a "Z" as non-existent
			request.set("security", security);

			request.append("eventTypes", "TRADE"); //One of TRADE (default), BID, ASK, BID_BEST, ASK_BEST, MID_PRICE, AT_TRADE, BEST_BID, BEST_ASK (see documentation A.2.6 for explanations)
			request.append("eventTypes", "BID"); //A request can have multiple eventTypes
			//Note 1) refDataService.ToString() using the Bloomberg API indicates an additional eventType called "SETTLE".  "SETTLE" doesn't seem to produce any results.
			//Note 2) If you request an eventType that isn't supported, the API will throw a KeyNotSupportedException at the "request.Append("eventType", "XXX")" line
			//Note 3) eventType values are case-sensitive.  Requesting "bid" instead of "BID" will throw a KeyNotSupportedException at the "request.Append("eventType", "bid")" line

			//today
			time_t theTime = time(NULL);
			struct tm *aTime = localtime(&theTime); //Visual Studio complains about this call, but the localtime_s replacement is not portable.

			int day = aTime->tm_mday;
			int month = aTime->tm_mon + 1;
			int year = aTime->tm_year + 1900;
			
			Datetime dtStart(year, month, day, 13, 0, 0);  //today at 1:00:00 PM
			Datetime dtEnd(year, month, day, 13, 9, 0); //today at 1:09:00 PM

			request.set("startDateTime", dtStart);
			request.set("endDateTime", dtEnd); //goes back at most 140 days (documentation section 7.2.3)

			//A comma delimited list of exchange condition codes associated with the event. Review QR<GO> for more information on each code returned.
			request.set("includeConditionCodes", false); //Optional bool. Valid values are true and false (default = false)

			//Returns all ticks, including those with condition codes.
			request.set("includeNonPlottableEvents", false); //Optional bool. Valid values are true and false (default = false)

			//The exchange code where this tick originated. Review QR<GO> for more information.
			request.set("includeExchangeCodes", false); //Optional bool. Valid values are true and false (default = false)
			request.set("includeExchangeCodes", false);

			//Option on whether to return EIDs for the security.
			request.set("returnEids", false); //Optional bool. Valid values are true and false (default = false)

			//The broker code for Canadian, Finnish, Mexican, Philippine, and Swedish equities only.
			//  The Market Maker Lookup screen, MMTK<GO>, displays further information on market makers and their corresponding codes.
			request.set("includeBrokerCodes", false); //Optional bool. Valid values are true and false (default = false)

			//The Reporting Party Side. The following values appear:
			//  -B: A customer transaction where the dealer purchases securities from the customer.
			//  -S: A customer transaction where the dealer sells securities to the customer.
			//  -D: An inter-dealer transaction (always from the sell side).
			request.set("includeRpsCodes", false); //Optional bool. Valid values are true and false (default = false)

			//The BIC, or Bank Identifier Code, as a 4-character unique identifier for each bank that executed and reported the OTC trade, as required by MiFID.
			//  BICs are assigned and maintained by SWIFT (Society for Worldwide Interbank Financial Telecommunication).
			//  The MIC is the Market Identifier Code, and this indicates the venue on which the trade was executed.
			request.set("includeBicMicCodes", false); //Optional bool. Valid values are true and false (default = false)

			CorrelationId requestId(15); //15 is just some number I picked
			session.sendRequest(request, requestId);			

			bool continueToLoop = true;
			while(continueToLoop)
			{
				Event evt(session.nextEvent());
				switch (evt.eventType())
				{
					case Event::RESPONSE:
						continueToLoop = false; //fall through
					case Event::PARTIAL_RESPONSE:
						ProcessIntradayTickEvent(evt, security);
						break;
				}
			}

			session.stop();
		}
		else
		{
			cerr << "Cannot connect to server";
		}
	}

	void ProcessIntradayTickEvent(Event evt, const char* security)
	{
		cout << security << endl;

		MessageIterator iter(evt);
		while(iter.next())
		{
			Message msg = iter.message();

			bool isSecurityError = msg.hasElement("responseError", true);
			if(isSecurityError)
			{
                Element secError = msg.getElement("responseError");
                const char * source = secError.getElementAsString("source");
                int code = secError.getElementAsInt32("code");
                const char * category = secError.getElementAsString("category");
                const char * errorMessage = secError.getElementAsString("message");
                const char * subCategory = secError.getElementAsString("subcategory");

				cerr << "response error" << endl;
                cerr << "source = " << source << endl;
                cerr << "code = " << code << endl;
                cerr << "category = " << category << endl;
                cerr << "errorMessage = " << errorMessage << endl;
                cerr << "subCategory = " << subCategory << endl;
			}
			else
			{
				Element elmTickDataArr = msg.getElement("tickData");
				Element elmTickData = elmTickDataArr.getElement("tickData");

                for (size_t valueCount = 0; valueCount < elmTickData.numValues(); valueCount++)
                {
                    Element elmTickDataValue = elmTickData.getValueAsElement(valueCount);

                    int size = elmTickDataValue.getElementAsInt32("size");
                    Datetime time = elmTickDataValue.getElementAsDatetime("time");
                    const char * type = elmTickDataValue.getElementAsString("type");
                    double value = elmTickDataValue.getElementAsFloat64("value");

					cout << time << ": " << type << ", " << size << " @ " << value << endl;
                }
			}
		
		}
	}
}