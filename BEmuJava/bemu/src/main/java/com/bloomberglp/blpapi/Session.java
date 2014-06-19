//------------------------------------------------------------------------------
// <copyright project="BEmu_maven" file="/BEmu_maven/bemu/src/main/java/com/bloomberglp/blpapi/Session.java" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

package com.bloomberglp.blpapi;

import com.bloomberglp.blpapi.SessionOptions;
import com.bloomberglp.blpapi.CorrelationID;
import com.bloomberglp.blpapi.Request;
import com.bloomberglp.blpapi.Event;
import com.bloomberglp.blpapi.EventHandler;

import java.util.ArrayList;
import java.util.List;
import java.util.Queue;
import java.util.LinkedList;
import java.util.concurrent.atomic.AtomicBoolean;

public class Session
{
	public static final class SubscriptionStatus
	{
		private int be;
		private String _strValue;
		public static final SubscriptionStatus SUBSCRIBING = new SubscriptionStatus(0, "SUBSCRIBING");
		public static final SubscriptionStatus WAITING_FOR_MESSAGES = new SubscriptionStatus(1, "WAITING_FOR_MESSAGES");
		public static final SubscriptionStatus RECEIVING_MESSAGES = new SubscriptionStatus(2, "RECEIVING_MESSAGES");
		public static final SubscriptionStatus UNSUBSCRIBED = new SubscriptionStatus(3, "UNSUBSCRIBED");
		private static SubscriptionStatus[] Cm;
		
		private SubscriptionStatus(int value, String strValue)
		{
			Cm = new SubscriptionStatus[] { SUBSCRIBING, WAITING_FOR_MESSAGES, RECEIVING_MESSAGES, UNSUBSCRIBED };
			this.be = value;
			this._strValue = strValue;
		}
		
		public int intValue()
		{
			return this.be;
		}
		
		public String toString()
		{
			return this._strValue;
		}
		
		static SubscriptionStatus bj(int paramInt)
		{
			if ((paramInt >= 0) && (paramInt < Cm.length)) {
				return Cm[paramInt];
			}
			return null;
		}
		
		public static class Constants
		{
			public static final int SUBSCRIBING = 0;
			public static final int WAITING_FOR_MESSAGES = 1;
			public static final int RECEIVING_MESSAGES = 2;
			public static final int UNSUBSCRIBED = 3;
		}
	}
	
	@SuppressWarnings("unused")
	private SessionOptions _sessionOptions;
	
	@SuppressWarnings("unused")
	private SessionResponseType _sessionResponse;
	private enum SessionResponseType { sync, async };
	
	@SuppressWarnings("unused")
	private SessionUriType _sessionUri = SessionUriType.undefined;
	private enum SessionUriType { undefined, refData, mktData };
	
	@SuppressWarnings("unused")
	private SessionStateType _sessionState = SessionStateType.initialized;
	private enum SessionStateType { initialized, started, serviceOpened };
	
	private final Queue<Request> _sentRequests;
    
	////////////////////////////////////////
	// Start Sync
	////////////////////////////////////////
	
	public Session(SessionOptions sessionOptions)
	{
		this._sessionOptions = sessionOptions;
		this._sessionResponse = SessionResponseType.sync;
		this._sentRequests = new LinkedList<Request>();
        this._asyncHandler = null;
        //this._marketSimulatorTimer = null;
        this._marketSimulatorTypeClass = null;
        this._subscriptions = null;
	}
	
    public boolean start()
    {
        this._sessionState = SessionStateType.started;
        return true;
    }
    
    public boolean openService(String uri)
    {
    	if(uri.equals("//blp/refdata"))
    	{
            this._sessionState = SessionStateType.serviceOpened;
            return true;
    	}
    	else
    		return false;
    }
    
    public Service getService(String uri) throws Exception
    {
        if (uri.equals("//blp/refdata"))
        {
            this._sessionUri = SessionUriType.refData;
            return new ServiceRefData();
        }
        else
            return null;
    }
    
    public CorrelationID sendRequest(Request request, CorrelationID correlationId)
    {
        request.correlationId(correlationId);
        this._sentRequests.add(request);
        return correlationId;
    }
    
    public Event nextEvent() throws Exception
    {
    	if(this._sentRequests.isEmpty())
    		return null;
    	else
    	{
	    	boolean isLastRequest = this._sentRequests.size() == 1;
	    	Request next = this._sentRequests.poll();
	    	return Event.EventFactory(next, isLastRequest);
    	}
    }
    
    //The actual API will block up to timeoutMillis.  My code simply ignores the timeoutMillis argument.
    public Event nextEvent(long timeoutMillis) throws Exception
    {
        return nextEvent();
    }
    
	////////////////////////////////////////
	// End Sync
	////////////////////////////////////////
    

    
	////////////////////////////////////////
	// Start Async
	////////////////////////////////////////

    private final EventHandler _asyncHandler;
    private final SubscriptionList _subscriptions;
    private final Object _syncroot = new Object();
    private final MarketSimulatorTypeClass _marketSimulatorTypeClass;
    private AtomicBoolean _isMarketSimulatorRunning;
    
    @SuppressWarnings("unused")
	private CorrelationID _asyncOpenCorrelation;
    
    public Session(SessionOptions sessionOptions, EventHandler handler) //for MarketData (async)
    {
        this._sessionResponse = SessionResponseType.async;
        this._sessionOptions = sessionOptions;
        this._sentRequests = null;
        this._asyncHandler = handler;
        this._subscriptions = new SubscriptionList(); 
        this._isMarketSimulatorRunning = new AtomicBoolean(false);
        this._marketSimulatorTypeClass = new MarketSimulatorTypeClass(this);
    }
    
    public void openServiceAsync(String url, CorrelationID correlationId)
    {
    	this._sessionUri = SessionUriType.mktData;
    	this._sessionState = SessionStateType.serviceOpened;
        this._asyncOpenCorrelation = correlationId;
    }
    
    public void openServiceAsync(String url)
    {
    	this._sessionUri = SessionUriType.mktData;
    	this._sessionState = SessionStateType.serviceOpened;
        this._asyncOpenCorrelation = new CorrelationID();
    }
    
    public void subscribe(SubscriptionList subscriptionList) throws Exception
    {
    	synchronized (this._syncroot) //protect _subscriptions
    	{
    		List<Subscription> slist = subscriptionList.list();
    		for(int i = 0; i < slist.size(); i++)
    		{
    			this._subscriptions.add(slist.get(i));
    		}
    	}

        Event.EventType evttSub = new Event.EventType(Event.EventType.Constants.SUBSCRIPTION_STATUS);
        MarketEvent evtSubStatus = new MarketEvent(evttSub, null, subscriptionList.list());
        if (this._asyncHandler != null)
        {
            this._asyncHandler.processEvent(evtSubStatus, this);
        }
    }
    
    public void unsubscribe(CorrelationID corr) throws Exception
    {
    	synchronized (this._syncroot) //protect _subscriptions
    	{
    		for(int i = this._subscriptions.size() - 1; i >= 0; i--)
    		{
    			Subscription sub = this._subscriptions.get(i); 
    			if(sub.correlationID().equals(corr))
    			{
    				Event.EventType evttSub = new Event.EventType(Event.EventType.Constants.SUBSCRIPTION_STATUS);
    				MarketEvent evtSubCancel = new MarketEvent(evttSub, sub);
    				
    				if (this._asyncHandler != null)
    		        {
    		            this._asyncHandler.processEvent(evtSubCancel, this);
    		        }    				
    				
    				this._subscriptions.remove(i);
    			}
    		}
    	}
    }

    public void unsubscribe(SubscriptionList subs) throws Exception
    {
    	for(int i = 0; i < subs.size(); i++)
    	{
    		this.unsubscribe(subs.get(i).correlationID());
    	}
    }
    
    public boolean startAsync() throws Exception
    {
        this._sessionState = SessionStateType.started;
        this._isMarketSimulatorRunning.set(true);

        Event.EventType evttSession = new Event.EventType(Event.EventType.Constants.SESSION_STATUS);
        Event.EventType evttService = new Event.EventType(Event.EventType.Constants.SERVICE_STATUS);
        
        MarketEvent evtSessionStatus = new MarketEvent(evttSession, null, null);
        MarketEvent evtServiceStatus = new MarketEvent(evttService, new CorrelationID(), null);

        if (this._asyncHandler != null)
        {
            this._asyncHandler.processEvent(evtSessionStatus, this);
            this._asyncHandler.processEvent(evtServiceStatus, this);
        }
        
        this._marketSimulatorTypeClass.start();
        
        return true;
    }

    public void stop()
    {
    	if(this._isMarketSimulatorRunning != null)
    		this._isMarketSimulatorRunning.set(false);
    }
    
    private class MarketSimulatorTypeClass extends java.lang.Thread
    {
    	private final Session _session;
    	
    	public MarketSimulatorTypeClass(Session session)
    	{
    		this._session = session;
    	}
    	
    	public void run()
    	{
    		boolean interrupted = false;
    		while(this._session._isMarketSimulatorRunning.get() && !interrupted)
    		{
                Long conflationIntervalInMilleseconds = null;

                List<Subscription> subsToUse = new ArrayList<Subscription>();  
                synchronized (this._session._syncroot) //protect _subscriptions
                {
                	List<Subscription> subscriptions = this._session._subscriptions.list();
                    
                	for(int i = 0; i < subscriptions.size(); i++)
                	{
                        if (RandomDataGenerator.shouldIncludeQuote()) //70% chance that I'll send a new quote for the current subscription (after the first response which contains all tickers)
                        	subsToUse.add(subscriptions.get(i));

                        if (subscriptions.get(i).conflationInterval() != null)
                            conflationIntervalInMilleseconds = (long)(subscriptions.get(i).conflationInterval() * 1000L);
                	}
                }
                
            	Event.EventType evtt = new Event.EventType(Event.EventType.Constants.SUBSCRIPTION_DATA);            	
                try
                {
                	if(subsToUse.size() > 0)
                	{
	    				MarketEvent evt = new MarketEvent(evtt, null, subsToUse);
	    				if(this._session._asyncHandler != null)
	    				{
	    					this._session._asyncHandler.processEvent(evt, this._session);
	    				}
                	}
    			}
                catch (Exception e)
                {
                	//do nothing
    			}
                
                if(conflationIntervalInMilleseconds == null)
                	conflationIntervalInMilleseconds = RandomDataGenerator.millisecondsBetweenMarketDataEvents();
                try
                {
                	Thread.sleep(conflationIntervalInMilleseconds);
				}
                catch (Exception e)
                {
                	interrupted = true;
				}
    		}
    	}
    }
    
	////////////////////////////////////////
	// End Async
	////////////////////////////////////////
    
}
