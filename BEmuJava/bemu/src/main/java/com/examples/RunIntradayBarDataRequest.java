package com.examples;


import java.text.SimpleDateFormat;

//import com.bemu.*; //un-comment this line to use the Bloomberg API Emulator
import com.bloomberglp.blpapi.*; //un-comment this line to use the actual Bloomberg API

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
			request.set("security", security);
			
			Datetime dtStart = new Datetime(2013, 4, 23);
			Datetime dtEnd = new Datetime(2013, 4, 25);
			request.set("startDateTime", dtStart);
			request.set("endDateTime", dtEnd);
			
			request.set("interval", 60);
			
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
