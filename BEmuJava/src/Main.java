//------------------------------------------------------------------------------
// <copyright project="BEmuJava" file="Main.java" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

import java.text.SimpleDateFormat;

import BEmu.*;

public class Main {


	private static SimpleDateFormat timeFmt = new SimpleDateFormat("HH:mm:ss");
	

	/**
	 * @param args
	 * @throws Exception 
	 */
	public static void main(String[] args) throws Exception //I don't know how to fix or suppress this warning
	{
		Main.CallIntBar();
		
		System.in.read();
	}
	
	private static void CallIntBar() throws Exception
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
						Main.processResponse(evt, security);
						continueLoop = false;
						break;
					case Event.EventType.Constants.PARTIAL_RESPONSE:
						Main.processResponse(evt, security);
						break;
				}
			}
		}
	}
	
	private static void processResponse(Event evt, String security) throws Exception
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
                
                System.out.println(Main.timeFmt.format(dtTick.calendar().getTime()));
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
