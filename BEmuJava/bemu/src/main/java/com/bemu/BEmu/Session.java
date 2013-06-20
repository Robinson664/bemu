//------------------------------------------------------------------------------
// <copyright project="BEmuJava" file="BEmu.Session.java" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

package com.bemu.BEmu;

import com.bemu.BEmu.SessionOptions;
import com.bemu.BEmu.CorrelationID;
import com.bemu.BEmu.Request;
import com.bemu.BEmu.Event;
import com.bemu.BEmu.types.RandomDataGenerator;
import com.bemu.BEmu.MarketDataRequest.EventMarket;

import java.util.ArrayList;
import java.util.List;
import java.util.Queue;
import java.util.LinkedList;
import java.util.concurrent.atomic.AtomicBoolean;

public class Session {
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
        this._sessionState = SessionStateType.serviceOpened;
        return true;
    }
    
    public Service getService(String uri) throws Exception
    {
        if (uri.equals("//blp/refdata"))
        {
            this._sessionUri = SessionUriType.refData;
            return new ServiceRefData();
        }
        else
            throw new Exception(String.format("BEmu.Session.GetService: Service %s not supported", uri));
    }
    
    public CorrelationID sendRequest(Request request, CorrelationID correlationId)
    {
        request.correlationId(correlationId);
        this._sentRequests.add(request);
        return correlationId;
    }
    
    public Event nextEvent() throws Exception
    {
    	boolean isLastRequest = this._sentRequests.size() == 1;
    	Request next = this._sentRequests.poll();
    	return Event.EventFactory(next, isLastRequest);
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
        EventMarket evtSubStatus = new EventMarket(evttSub, null, subscriptionList.list());
        if (this._asyncHandler != null)
        {
            this._asyncHandler.processEvent(evtSubStatus, this);
        }
    }
    
    public boolean startAsync() throws Exception
    {
        this._sessionState = SessionStateType.started;
        this._isMarketSimulatorRunning.set(true);

        Event.EventType evttSession = new Event.EventType(Event.EventType.Constants.SESSION_STATUS);
        Event.EventType evttService = new Event.EventType(Event.EventType.Constants.SERVICE_STATUS);
        
        EventMarket evtSessionStatus = new EventMarket(evttSession, null, null);
        EventMarket evtServiceStatus = new EventMarket(evttService, new CorrelationID(), null);

        if (this._asyncHandler != null)
        {
            this._asyncHandler.processEvent(evtSessionStatus, this);
            this._asyncHandler.processEvent(evtServiceStatus, this);
        }
        
        this._marketSimulatorTypeClass.run();
        
        return true;
    }

    public void stop()
    {
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
    				EventMarket evt = new EventMarket(evtt, null, subsToUse);
    				if(this._session._asyncHandler != null)
    					this._session._asyncHandler.processEvent(evt, this._session);
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
