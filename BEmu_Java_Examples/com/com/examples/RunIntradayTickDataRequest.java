//------------------------------------------------------------------------------
// <copyright project="BEmu_Java_Examples" file="/BEmu_Java_Examples/com/com/examples/RunIntradayTickDataRequest.java" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

package com.examples;

import java.text.SimpleDateFormat;
import java.util.Calendar;

import com.bloomberglp.blpapi.Datetime;
import com.bloomberglp.blpapi.Element;
import com.bloomberglp.blpapi.Message;
import com.bloomberglp.blpapi.MessageIterator;
import com.bloomberglp.blpapi.Event;
import com.bloomberglp.blpapi.CorrelationID;
import com.bloomberglp.blpapi.Request;
import com.bloomberglp.blpapi.Service;
import com.bloomberglp.blpapi.Session;
import com.bloomberglp.blpapi.SessionOptions;

public class RunIntradayTickDataRequest
{
	private final static java.text.NumberFormat currency = java.text.NumberFormat.getCurrencyInstance();
	private static SimpleDateFormat timeFmt = new SimpleDateFormat("HH:mm:ss");
	
	public static void RunExample() throws Exception
	{
		SessionOptions soptions = new SessionOptions();
		soptions.setServerHost("127.0.0.1");
		soptions.setServerPort(8194);
		
		Session session = new Session(soptions);
		if(session.start() && session.openService("//blp/refdata"))
		{
			Service service = session.getService("//blp/refdata");
			Request request = service.createRequest("IntradayTickRequest");

            String security = "SPY US Equity";
            //security = "ZYZZ US EQUITY";  //the code treats securities that start with a "Z" as non-existent
            request.set("security", security);

            request.append("eventTypes", "TRADE"); //One of TRADE (default), BID, ASK, BID_BEST, ASK_BEST, MID_PRICE, AT_TRADE, BEST_BID, BEST_ASK (see documentation A.2.6 for explanations)
            request.append("eventTypes", "BID"); //A request can have multiple eventTypes
            //Note 1) refDataService.ToString() using the Bloomberg API indicates an additional eventType called "SETTLE".  "SETTLE" doesn't seem to produce any results.
            //Note 2) If you request an eventType that isn't supported, the API will throw a KeyNotSupportedException at the "request.Append("eventType", "XXX")" line
            //Note 3) eventType values are case-sensitive.  Requesting "bid" instead of "BID" will throw a KeyNotSupportedException at the "request.Append("eventType", "bid")" line
            
            { //dates
            	
            	//goes back at most 140 days (documentation section 7.2.3)
	            Calendar cStart = Calendar.getInstance();
	            cStart.add(Calendar.DAY_OF_MONTH, -3);
	            cStart.set(Calendar.HOUR, 2);
	            cStart.set(Calendar.MINUTE, 0);
				Datetime dtStart = new Datetime(cStart);	
				request.set("startDateTime", dtStart);		
	
	            Calendar cEnd = Calendar.getInstance();
	            cEnd.add(Calendar.DAY_OF_MONTH, -3);
	            cEnd.set(Calendar.HOUR, 3);
	            cEnd.set(Calendar.MINUTE, 0);
				Datetime dtEnd = new Datetime(cEnd);
				request.set("endDateTime", dtEnd);
            }

            //A comma delimited list of exchange condition codes associated with the event. Review QR<GO> for more information on each code returned.
            request.set("includeConditionCodes", false); //Optional bool. Valid values are true and false (default = false)

            //Returns all ticks, including those with condition codes.
            request.set("includeNonPlottableEvents", false); //Optional bool. Valid values are true and false (default = false)

            //The exchange code where this tick originated. Review QR<GO> for more information.
            request.set("includeExchangeCodes", false); //Optional bool. Valid values are true and false (default = false)

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
            

            CorrelationID corr = new CorrelationID(17);
            session.sendRequest(request, corr);
            
            boolean continueToLoop = true;
            while (continueToLoop)
            {
				Event evt = session.nextEvent();
				
				switch(evt.eventType().intValue())
				{
					case Event.EventType.Constants.RESPONSE:
						RunIntradayTickDataRequest.processResponseTick(evt, security);
						continueToLoop = false;
						break;
					case Event.EventType.Constants.PARTIAL_RESPONSE:
						RunIntradayTickDataRequest.processResponseTick(evt, security);
						break;
				}
				
				if(evt.eventType() == Event.EventType.RESPONSE)
				{
					RunIntradayTickDataRequest.processResponseTick(evt, security);
					continueToLoop = false;
					
					System.out.println("response");
				}
				else if(evt.eventType() == Event.EventType.PARTIAL_RESPONSE)
				{
					RunIntradayTickDataRequest.processResponseTick(evt, security);

					System.out.println("partial response");
				}
            }
		}
	}
	
	private static void processResponseTick(Event evt, String security) throws Exception
	{
		MessageIterator miter = evt.messageIterator();
		while(miter.hasNext())
		{
			Message msg = miter.next();

            boolean isSecurityError = msg.hasElement("responseError", true);
            if(isSecurityError)
            {                	
                Element secError = msg.getElement("responseError");
                String source = secError.getElementAsString("source");
                int code = secError.getElementAsInt32("code");
                String category = secError.getElementAsString("category");
                String errorMessage = secError.getElementAsString("message");
                String subCategory = secError.getElementAsString("subcategory");

                System.err.println("response error");
                System.err.println(String.format("source = %s", source));
                System.err.println(String.format("code = %s", code));
                System.err.println(String.format("category = %s", category));
                System.err.println(String.format("errorMessage = %s", errorMessage));
                System.err.println(String.format("subCategory = %s", subCategory));
            }
            else
            {
    			Element elmTickData = msg.getElement("tickData");
    			Element elmTickDataArray = elmTickData.getElement("tickData");
    			
    			for(int valueIndex = 0; valueIndex < elmTickDataArray.numValues(); valueIndex++)
    			{
					Element elmTickDataItem = elmTickDataArray.getValueAsElement(valueIndex);
					
					Datetime time = elmTickDataItem.getElementAsDatetime("time");
					String type = elmTickDataItem.getElementAsString("type");
					double value = elmTickDataItem.getElementAsFloat64("value");
					int size = elmTickDataItem.getElementAsInt32("size");
					
					String out = String.format("%s: %s, %s @ %d",
							RunIntradayTickDataRequest.timeFmt.format(time.calendar().getTime()),
							type,
							currency.format(value),
							size); 
					
					System.out.println(out);
    			}
            }
		}
	}
	
}
