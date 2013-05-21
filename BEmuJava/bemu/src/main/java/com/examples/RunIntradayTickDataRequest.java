package com.examples;


//import com.bemu.*;
import com.bloomberglp.blpapi.*;

import java.text.SimpleDateFormat;

public class RunIntradayTickDataRequest
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
			Request request = service.createRequest("IntradayTickRequest");

            String security = "SPY US Equity";
            request.set("security", security);
            
            request.append("eventTypes", "TRADE");

			Datetime dtStart = new Datetime(2013, 5, 1);
			Datetime dtEnd = new Datetime(2013, 5, 2);
			request.set("startDateTime", dtStart);
			request.set("endDateTime", dtEnd);

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
            }
		}
	}
	
	private static void processResponseTick(Event evt, String security) throws Exception
	{
		MessageIterator miter = evt.messageIterator();
		while(miter.hasNext())
		{
			Message msg = miter.next();

			Element elmTickData = msg.getElement("tickData");
			Element elmTickDataArray = elmTickData.getElement("tickData");
			
			for(int valueIndex = 0; valueIndex < elmTickDataArray.numValues(); valueIndex++)
			{
				Element elmTickDataItem = elmTickDataArray.getValueAsElement(valueIndex);
				
				Datetime time = elmTickDataItem.getElementAsDatetime("time");
				String type = elmTickDataItem.getElementAsString("type");
				double value = elmTickDataItem.getElementAsFloat64("value");
				int size = elmTickDataItem.getElementAsInt32("size");
				
				String out = String.format("%s: %s, %f @ %d",
						RunIntradayTickDataRequest.timeFmt.format(time.calendar().getTime()),
						type,
						value,
						size); 
				
				System.out.println(out);
			}
		}
	}
	
}
