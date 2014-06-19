//------------------------------------------------------------------------------
// <copyright project="BEmu_Java_Examples" file="/BEmu_Java_Examples/com/com/examples/RunIntradayBarDataRequest.java" company="Jordan Robinson">
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

public class RunIntradayBarDataRequest
{
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
			Request request = service.createRequest("IntradayBarRequest");
			
			String security = "SPY US EQUITY";
            //security = "ZYZZ US EQUITY";  //the code treats securities that start with a "Z" as non-existent
			request.set("security", security); //required

			request.set("eventType", "TRADE"); //optional: TRADE(default), BID, ASK, BID_BEST, ASK_BEST, BEST_BID, BEST_ASK, BID_YIELD, ASK_YIELD, MID_PRICE, AT_TRADE, SETTLE
            request.set("eventType", "BID"); //A request cannot have multiple eventTypes.  This "BID" setter overwrites the "TRADE" setter above
            //Note 1) BID_YIELD, ASK_YIELD, MID_PRICE, AT_TRADE, and SETTLE don't appear in the API documentation, but you will see them if you call "service.ToString()" using the actual Bloomberg API
            //Note 2) If you request an eventType that isn't supported, the API will throw a KeyNotSupportedException at the "request.Set("eventType", "XXX")" line
            //Note 3) eventType values are case-sensitive.  Requesting "bid" instead of "BID" will throw a KeyNotSupportedException at the "request.Set("eventType", "bid")" line
			
			{ //dates

                //data goes back no farther than 140 days (7.2.4)
				Calendar cStart = Calendar.getInstance();
				cStart.add(Calendar.DAY_OF_YEAR, -1); //yesterday			
				Datetime dtStart = new Datetime(cStart);
				request.set("startDateTime", dtStart); //Required Datetime, UTC time
	
				Calendar cEnd = Calendar.getInstance();
				Datetime dtEnd = new Datetime(cEnd);
				request.set("endDateTime", dtEnd); //Required Datetime, UTC time
			}

            //(Required) Sets the length of each time bar in the response. Entered as a whole number, between 1 and 1440 in minutes.
            //  One minute is the lowest possible granularity. (despite A.2.8, the interval setting cannot be omitted)
            request.set("interval", 60);

            //When set to true, a bar contains the previous bar values if there was no tick during this time interval.
            request.set("gapFillInitialBar", false); //Optional bool. Valid values are true and false (default = false)

            //Option on whether to return EIDs for the security.
            request.set("returnEids", false); //Optional bool. Valid values are true and false (default = false)

            ////Setting this to true will populate fieldData with an extra element containing a name and value for the relative date. For example RELATIVE_DATE = 2002 Q2
            //request.Set("returnRelativeDate", false); //Optional bool. Valid values are true and false (default = false)

            //Adjust historical pricing to reflect: Regular Cash, Interim, 1st Interim, 2nd Interim, 3rd Interim, 4th Interim, 5th Interim, Income,
            //  Estimated, Partnership Distribution, Final, Interest on Capital, Distribution, Prorated.
            request.set("adjustmentNormal", false); //Optional bool. Valid values are true and false (default = false)

            //Adjust historical pricing to reflect: Special Cash, Liquidation, Capital Gains, Long-Term Capital Gains, Short-Term Capital Gains, Memorial,
            //  Return of Capital, Rights Redemption, Miscellaneous, Return Premium, Preferred Rights Redemption, Proceeds/Rights, Proceeds/Shares, Proceeds/Warrants.
            request.set("adjustmentAbnormal", false); //Optional bool. Valid values are true and false (default = false)

            //Adjust historical pricing and/or volume to reflect: Spin-Offs, Stock Splits/Consolidations, Stock Dividend/Bonus, Rights Offerings/Entitlement.
            request.set("adjustmentSplit", false); //Optional bool. Valid values are true and false (default = false)

            //Setting to true will follow the DPDF<GO> BLOOMBERG PROFESSIONAL service function. True is the default setting for this option.
            request.set("adjustmentFollowDPDF", false); //Optional bool. Valid values are true and false (default = true)
						
			session.sendRequest(request, new CorrelationID(-999));
			boolean continueLoop = true;
			while(continueLoop)
			{
				Event evt = session.nextEvent();
				switch(evt.eventType().intValue())
				{
					case Event.EventType.Constants.RESPONSE:
						RunIntradayBarDataRequest.processResponseBar(evt, security);
						continueLoop = false;
						break;
					case Event.EventType.Constants.PARTIAL_RESPONSE:
						RunIntradayBarDataRequest.processResponseBar(evt, security);
						break;
				}
			}
		}
	}
	
	private static void processResponseBar(Event evt, String security) throws Exception
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
                String subCategory = secError.getElementAsString("subCategory");

                System.err.println("response error");
                System.err.println(String.format("source = %s", source));
                System.err.println(String.format("code = %s", code));
                System.err.println(String.format("category = %s", category));
                System.err.println(String.format("errorMessage = %s", errorMessage));
                System.err.println(String.format("subCategory = %s", subCategory));
            }
            else
            {
				Element elmBarData = msg.getElement("barData");
				Element elmBarTickDataArray = elmBarData.getElement("barTickData");
				for(int valueIndex = 0; valueIndex < elmBarTickDataArray.numValues(); valueIndex++)
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
	                
	                System.out.println(RunIntradayBarDataRequest.timeFmt.format(dtTick.calendar().getTime()));
	                System.out.println(String.format("\t open = $%,.2f", open));
	                System.out.println(String.format("\t high = $%,.2f", high));
	                System.out.println(String.format("\t low = $%,.2f", low));
	                System.out.println(String.format("\t close = $%,.2f", close));
	                
	                System.out.println(String.format("\t numEvents = %,d", numEvents));
	                System.out.println(String.format("\t volume = %,d", volume));
	                System.out.println(String.format("\t value = %,.0f", value));
	                System.out.println();
				}
            }
		}
	}
	
}
