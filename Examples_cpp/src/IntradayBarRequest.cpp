//------------------------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="src/IntradayBarRequest.cpp" company="Jordan Robinson">
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
	void ProcessIntradayBarEvent(Event evt, const char* security);

	void RunIntradayBarExample()
	{
		SessionOptions soptions;
		soptions.setServerHost("localhost");
		soptions.setServerPort(8194);

		Session session(soptions);
		if(session.start() && session.openService("//blp/refdata"))
		{
			Service refDataSvc = session.getService("//blp/refdata");
			
			Request request = refDataSvc.createRequest("IntradayBarRequest");

            const char * security = "MSFT US EQUITY";
            //security = "ZYZZ US EQUITY";  //the code treats securities that start with a "Z" as non-existent
            request.set("security", security); //required

            request.set("eventType", "TRADE"); //optional: TRADE(default), BID, ASK, BID_BEST, ASK_BEST, BEST_BID, BEST_ASK, BID_YIELD, ASK_YIELD, MID_PRICE, AT_TRADE, SETTLE
            request.set("eventType", "BID"); //A request cannot have multiple eventTypes.  This "BID" setter overwrites the "TRADE" setter above
            //Note 1) BID_YIELD, ASK_YIELD, MID_PRICE, AT_TRADE, and SETTLE don't appear in the API documentation, but you will see them if you call "service.ToString()" using the actual Bloomberg API
            //Note 2) If you request an eventType that isn't supported, the API will throw a KeyNotSupportedException at the "request.Set("eventType", "XXX")" line
            //Note 3) eventType values are case-sensitive.  Requesting "bid" instead of "BID" will throw a KeyNotSupportedException at the "request.Set("eventType", "bid")" line
			
			//the end time is right now
			time_t tToday = time(NULL);
			struct tm *aTimeToday = localtime(&tToday); //Visual Studio complains about this call, but the localtime_s replacement is not portable.
			int day = aTimeToday->tm_mday;
			int month = aTimeToday->tm_mon + 1;
			int year = aTimeToday->tm_year + 1900;
			Datetime dtToday(year, month, day);
			request.set("endDateTime", dtToday);
			
			//the start time is 1 day ago
			time_t tYesterday = tToday - (1 * 24 * 60 * 60); //days * hours * minutes * seconds
			struct tm *aTimeYesterday = localtime(&tYesterday); //Visual Studio complains about this call, but the localtime_s replacement is not portable.
			day = aTimeYesterday->tm_mday;
			month = aTimeYesterday->tm_mon + 1;
			year = aTimeYesterday->tm_year + 1900;
			Datetime dtYesterday(year, month, day);
			request.set("startDateTime", dtYesterday);

            //(Required) Sets the length of each time bar in the response. Entered as a whole number, between 1 and 1440 in minutes.
            //  One minute is the lowest possible granularity. (despite A.2.8, the interval setting cannot be omitted)
            request.set("interval", 60);

            //When set to true, a bar contains the previous bar values if there was no tick during this time interval.
            request.set("gapFillInitialBar", false); //Optional bool. Valid values are true and false (default = false)

            //Option on whether to return EIDs for the security.
            request.set("returnEids", false); //Optional bool. Valid values are true and false (default = false)

            ////Setting this to true will populate fieldData with an extra element containing a name and value for the relative date. For example RELATIVE_DATE = 2002 Q2
            //request.set("returnRelativeDate", false); //Optional bool. Valid values are true and false (default = false)

            //Adjust historical pricing to reflect: Regular Cash, Interim, 1st Interim, 2nd Interim, 3rd Interim, 4th Interim, 5th Interim, Income,
            //  Estimated, Partnership Distribution, Final, Interest on Capital, Distribution, Prorated.
            request.set("adjustmentNormal", false); //Optional bool. Valid values are true and false (default = false)

            //Adjust historical pricing to reflect: Special Cash, Liquidation, Capital Gains, Long-Term Capital Gains, Short-Term Capital Gains, Memorial,
            //  Return of Capital, Rights Redemption, Miscellaneous, Return Premium, Preferred Rights Redemption, Proceeds/Rights, Proceeds/Shares, Proceeds/Warrants.
            request.set("adjustmentAbnormal", false); //Optional bool. Valid values are true and false (default = false)

            //Adjust historical pricing and/or volume to reflect: Spin-Offs, Stock Splits/Consolidations, Stock Dividend/Bonus, Rights Offerings/Entitlement.
            request.set("adjustmentSplit", false); //Optional bool. Valid values are true and false (default = false)

            //Setting to true will follow the DPDF<GO> BLOOMBERG PROFESSIONAL service function. True is the default setting for this option..
            request.set("adjustmentFollowDPDF", false); //Optional bool. Valid values are true and false (default = true)

			
			CorrelationId requestId(29); //29 is just some number I picked
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
						ProcessIntradayBarEvent(evt, security);
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
	
	void ProcessIntradayBarEvent(Event evt, const char* security)
	{	
		cout << security << endl;

		MessageIterator iter(evt);
		while(iter.next())
		{
			Message msg = iter.message();

			bool isSecurityError = msg.hasElement("responseError", true);
            if (isSecurityError)
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
				Element elmBarData = msg.getElement("barData");
				Element elmBarTickDataArray = elmBarData.getElement("barTickData");

				for (size_t valueIndex = 0; valueIndex < elmBarTickDataArray.numValues(); valueIndex++)
				{
                    Element elmBarTickData = elmBarTickDataArray.getValueAsElement(valueIndex);

					Datetime dtTick = elmBarTickData.getElementAsDatetime("time");

                    double open = elmBarTickData.getElementAsFloat64("open");
                    double high = elmBarTickData.getElementAsFloat64("high");
                    double low = elmBarTickData.getElementAsFloat64("low");
                    double close = elmBarTickData.getElementAsFloat64("close");

                    int numEvents = elmBarTickData.getElementAsInt32("numEvents");
                    long volume = elmBarTickData.getElementAsInt64("volume");
                    double value = elmBarTickData.getElementAsFloat64("value");

					cout << dtTick << endl;
					cout << "\t open = " << open << endl;
					cout << "\t high = " << high << endl;
					cout << "\t low = " << low << endl;
					cout << "\t close = " << close << endl;
					
					cout << "\t numEvents = " << numEvents << endl;
					cout << "\t volume = " << volume << endl;
					cout << "\t value = " << value << endl;

					cout << endl;
				}
			}
		}

	}
}