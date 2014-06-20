//------------------------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="src/HistoricalDataRequest.cpp" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------------------------

#include <iostream>
#include <sstream>
#include <time.h>
#include "api_selector.h"

using namespace std;

namespace Examples
{
	void ProcessHistoricalDataEvent(Event evt);
	char * DatetimeToYYYYMMDD(const Datetime& arg);

	void RunHistoricalDataExample()
	{
		SessionOptions soptions;
		soptions.setServerHost("localhost");
		soptions.setServerPort(8194);

		Session session(soptions);
		if(session.start() && session.openService("//blp/refdata"))
		{
			Service refDataSvc = session.getService("//blp/refdata");

			Request request = refDataSvc.createRequest("HistoricalDataRequest");

            //request information for the following securities
            request.append("securities", "MSFT US EQUITY");
            request.append("securities", "C A COMDTY");
            request.append("securities", "AAPL 150117C00600000 EQUITY"); //this is a stock option: TICKER yyMMdd[C/P]\d{8} EQUITY

            //uncomment the following line to see what a request for a nonexistent security looks like
            //request.append("securities", "ZIBM US EQUITY");
            //  My code treats all securities that start with a 'Z' as a nonexistent security


            //include the following simple fields in the result
            request.append("fields", "BID");
            request.append("fields", "ASK");

            //uncomment the following line to see what a request for an invalid field looks like
            //request.append("fields", "ZBID");
            //  My code treats all fields that start with a 'Z' as an invalid field

            //Historical requests allow a few overrides.  See the developer's guide A.2.4 for more information.
			
			//30 days in the past
			time_t tStart = time(NULL) - (30 * 24 * 60 * 60); //days * hours * minutes * seconds
			struct tm *aTimeStart = localtime(&tStart); //Visual Studio complains about this call, but the localtime_s replacement is not portable.
			int day = aTimeStart->tm_mday;
			int month = aTimeStart->tm_mon + 1;
			int year = aTimeStart->tm_year + 1900;
			Datetime dtStart(year, month, day);
			char * strDtStart = DatetimeToYYYYMMDD(dtStart);
			request.set("startDate", strDtStart); //Request that the information start three months ago from today.  This override is required.
			delete strDtStart;
			strDtStart = 0;

			//10 days in the future
			time_t tEnd = time(NULL) + (10 * 24 * 60 * 60); //days * hours * minutes * seconds
			struct tm *aTimeEnd = localtime(&tEnd); //Visual Studio complains about this call, but the localtime_s replacement is not portable.
			day = aTimeEnd->tm_mday;
			month = aTimeEnd->tm_mon + 1;
			year = aTimeEnd->tm_year + 1900;
			Datetime dtEnd(year, month, day);
			char * strDtEnd = DatetimeToYYYYMMDD(dtEnd);
            request.set("endDate", strDtEnd); //Request that the information end three days before today.  This is an optional override.  The default is today.
			delete strDtEnd;
			strDtEnd = 0;


            //Determine the frequency and calendar type of the output. To be used in conjunction with Period Selection.
            request.set("periodicityAdjustment", "CALENDAR"); //Optional string.  Valid values are ACTUAL (default), CALENDAR, and FISCAL.

            //Determine the frequency of the output. To be used in conjunction with Period Adjustment.
            request.set("periodicitySelection", "DAILY"); //Optional string.  Valid values are DAILY (default), WEEKLY, MONTHLY, QUARTERLY, SEMI_ANNUALLY, and YEARLY

            //Sets quote to Price or Yield for a debt instrument whose default value is quoted in yield (depending on pricing source).
            request.set("pricingOption", "PRICING_OPTION_PRICE"); //Optional string.  Valid values are PRICING_OPTION_PRICE (default) and PRICING_OPTION_YIELD

            //Adjust for "change on day"
            request.set("adjustmentNormal", true); //Optional bool. Valid values are true and false (default = false)

            //Adjusts for Anormal Cash Dividends
            request.set("adjustmentAbnormal", false); //Optional bool. Valid values are true and false (default = false)

            //Capital Changes Defaults
            request.set("adjustmentSplit", true); //Optional bool. Valid values are true and false (default = false)
			
            //The maximum number of data points to return, starting from the startDate
            //request.Set("maxDataPoints", 5); //Optional integer.  Valid values are positive integers.  The default is unspecified in which case the response will have all data points between startDate and endDate

            //Indicates whether to use the average or the closing price in quote calculation.
            request.set("overrideOption", "OVERRIDE_OPTION_CLOSE"); //Optional string.  Valid values are OVERRIDE_OPTION_GPA for an average and OVERRIDE_OPTION_CLOSE (default) for the closing price
			
			CorrelationId requestId(17); //17 is just some number I picked
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
						ProcessHistoricalDataEvent(evt);
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

	void ProcessHistoricalDataEvent(Event evt)
	{
		cout << "EventType = " << evt.eventType();
		MessageIterator iter(evt);
		while(iter.next())
		{
			Message msg = iter.message();

			cout << endl;
			cout << "correlationID = " << msg.correlationId() << endl;
			cout << "messageType = " << msg.messageType() << endl;

			if(msg.hasElement("securityData", true))
			{
				Element elmSecurityData = msg.getElement("securityData");

				Element elmSecurity = elmSecurityData.getElement("security");
				const char * security = elmSecurity.getValueAsString();
				cout << security << endl;

				bool isSecurityError = elmSecurityData.hasElement("securityError", true);
				if(isSecurityError)
				{
					Element elmSecError = elmSecurityData.getElement("securityError");
					string source = elmSecError.getElementAsString("source");
					int code = elmSecError.getElementAsInt32("code");
					string category = elmSecError.getElementAsString("category");
					string errorMessage = elmSecError.getElementAsString("message");
					string subCategory = elmSecError.getElementAsString("subcategory");

					cerr << "security error" << endl;
					cerr << "source = " << source << endl;
					cerr << "code = " << code << endl;
					cerr << "category = " << category << endl;
					cerr << "errorMessage = " << errorMessage << endl;
					cerr << "subcategory = " << subCategory << endl;
				}
				else
				{
					bool hasFieldErrors = elmSecurityData.hasElement("fieldExceptions", true);
					if(hasFieldErrors)
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

							cerr << endl;
							cerr << endl;
							cerr << "field error: " << endl;
							cerr << "\tfieldId = " << fieldId << endl;
							cerr << "\tsource = " << source << endl;
							cerr << "\tcode = " << code << endl;
							cerr << "\tcategory = " << category << endl;
							cerr << "\terrorMessage = " << strMessage << endl;
							cerr << "\tsubCategory = " << subCategory << endl;
						}
					}

					Element elmFieldData = elmSecurityData.getElement("fieldData");
					for (size_t valueIndex = 0; valueIndex < elmFieldData.numValues(); valueIndex++)
					{
						Element elmValues = elmFieldData.getValueAsElement(valueIndex);
						Datetime date = elmValues.getElementAsDatetime("date");
						double bid = elmValues.getElementAsFloat64("BID");
						double ask = elmValues.getElementAsFloat64("ASK");

						cout << date << ": BID = " << bid << ", ASK = " << ask << endl;
					}

				}
			}
			else
			{
				cout << "no security data" << endl;
				msg.print(cout);
			}

		}
	}

	char * DatetimeToYYYYMMDD(const Datetime& arg)
	{
		stringstream ss;

		ss << arg.year();

		if(arg.month() < 10)
			ss << '0';
		ss << arg.month();

		if(arg.day() < 10)
			ss << '0';
		ss << arg.day();

		string str = ss.str();
		const char * temp = str.c_str();

		char * result = new char[9];
		strncpy(result, temp, 9);

		return result;
	}

}