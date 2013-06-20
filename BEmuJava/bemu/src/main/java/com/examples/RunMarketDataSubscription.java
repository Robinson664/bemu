package com.examples;

import java.util.ArrayList;
import java.util.List;

//import com.bloomberglp.blpapi.*;
import com.bemu.BEmu.*;

public class RunMarketDataSubscription
{
	public static void RunExample() throws Exception
	{
		SessionOptions soptions = new SessionOptions();
		soptions.setServerHost("127.0.0.1");
		soptions.setServerPort(8194);

		RunMarketDataSubscription r = new RunMarketDataSubscription();
		MyEventHandler mevt = r.new MyEventHandler();
        Session session = new Session(soptions, mevt);
        session.startAsync();
	}
	
	public class MyEventHandler implements EventHandler
	{
		void dumpEvent(Event event)
		{
			System.out.println("eventType=" + event.eventType());
			MessageIterator messageIterator = event.messageIterator();
			while (messageIterator.hasNext())
			{
				Message message = messageIterator.next();
				System.out.println("messageType=" + message.messageType());
				System.out.println("CorrelationID=" + message.correlationID());
				try
				{
					System.out.print(message.toString());
				}
				catch (Exception e)
				{
					//do nothing
				}
			}
		}
		
		public void processEvent(Event event, Session session)
		{
			switch (event.eventType().intValue())
			{
				case Event.EventType.Constants.SESSION_STATUS:
				{
					MessageIterator iter = event.messageIterator();
					while (iter.hasNext())
					{
						Message message = iter.next();
						if (message.messageType().equals("SessionStarted"))
						{
							try
							{
								session.openServiceAsync("//blp/refdata", new CorrelationID(-9999));
							}
							catch (Exception e)
							{
								System.err.println("Could not open //blp/refdata for async");
							}
						}
					}
					break;
				}
				
				case Event.EventType.Constants.SERVICE_STATUS:
				{
					MessageIterator iter = event.messageIterator();
					while (iter.hasNext())
					{
						Message message = iter.next();
						
						if (/*message.correlationID().value() == -9999 && */message.messageType().equals("ServiceOpened"))
						{	
							List<String> fields = new ArrayList<String>();
							fields.add("BID");
							fields.add("ASK");
							fields.add("LAST_PRICE");

							Subscription subIBM = new Subscription("IBM US EQUITY", fields);
							Subscription subSPY = new Subscription("IBM US EQUITY", fields);
							Subscription subOption = new Subscription("AAPL 150117C00600000 EQUITY", fields);
							
							SubscriptionList slist = new SubscriptionList();
							slist.add(subIBM);
							slist.add(subSPY);
							slist.add(subOption);
							
							try
							{
								session.subscribe(slist);
							}
							catch (Exception e)
							{
								System.err.println("Subscription error");
							}
						}
					}
				}

				case Event.EventType.Constants.SUBSCRIPTION_DATA:
				case Event.EventType.Constants.PARTIAL_RESPONSE:
				case Event.EventType.Constants.RESPONSE:	
				{
					dumpEvent(event); // Handle Partial Response
					break;
				}
				
			}
		}
	}
}
