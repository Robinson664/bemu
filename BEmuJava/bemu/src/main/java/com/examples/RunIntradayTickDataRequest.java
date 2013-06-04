package com.examples;

import com.bemu.BEmu.*; //un-comment this line to use the Bloomberg API Emulator
//import com.bloomberglp.blpapi.*; //un-comment this line to use the actual Bloomberg API

import java.text.SimpleDateFormat;
import java.util.Calendar;

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

            Calendar cStart = Calendar.getInstance();
            cStart.add(Calendar.DAY_OF_MONTH, -1);
            cStart.set(Calendar.HOUR, 2);
            cStart.set(Calendar.MINUTE, 50);
			Datetime dtStart = new Datetime(cStart);
			

            Calendar cEnd = Calendar.getInstance();
            cEnd.add(Calendar.DAY_OF_MONTH, -1);
            cEnd.set(Calendar.HOUR, 3);
            cEnd.set(Calendar.MINUTE, 0);
			Datetime dtEnd = new Datetime(cEnd);
			
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
