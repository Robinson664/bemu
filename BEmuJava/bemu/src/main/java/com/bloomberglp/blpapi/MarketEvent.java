//------------------------------------------------------------------------------
// <copyright project="BEmu_maven" file="/BEmu_maven/bemu/src/main/java/com/bloomberglp/blpapi/MarketEvent.java" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

package com.bloomberglp.blpapi;

import java.util.Map;
import java.util.List;
import java.util.ArrayList;

import com.bloomberglp.blpapi.Event;
import com.bloomberglp.blpapi.Message;
import com.bloomberglp.blpapi.MessageIterator;
import com.bloomberglp.blpapi.Subscription;
import com.bloomberglp.blpapi.CorrelationID;

public class MarketEvent extends Event
{
	private final List<Message> _messages;
	
	//don't use this.  It's not in the Bloomberg API
	public MarketEvent(EventType evtType, CorrelationID corr, List<Subscription> subscriptions) throws Exception //use for subscribing
    {
        this._messages = new ArrayList<Message>();        
        
        switch (evtType.intValue())
        {        
            case Event.EventType.Constants.SESSION_STATUS:
            	super._eventType = evtType;
                MarketMessageSessionOpened msgSessionOpened = new MarketMessageSessionOpened();
                this._messages.add(msgSessionOpened);
                break;

            case Event.EventType.Constants.SERVICE_STATUS:
                super._eventType = evtType;
                MarketMessageServiceStatus msgServiceStatus = new MarketMessageServiceStatus(corr);
                this._messages.add(msgServiceStatus);
                break;

            case Event.EventType.Constants.SUBSCRIPTION_STATUS:
                super._eventType = evtType;
                
                for(int i = 0; i < subscriptions.size(); i++)
                {
                	Subscription item = subscriptions.get(i); 
                	boolean securityError = Rules.isSecurityError(item.security());
                	if(securityError)
                	{
                        MarketMessageSubscriptionFailure msgError = new MarketMessageSubscriptionFailure(item);
                        this._messages.add(msgError);
                	}
                	else
                	{
                        MarketMessageSubscriptionStarted msgSubStatus = new MarketMessageSubscriptionStarted(item);
                        this._messages.add(msgSubStatus);
                	}
                }
                break;

            case Event.EventType.Constants.SUBSCRIPTION_DATA:
                super._eventType = evtType;
                
                for(int i = 0; i < subscriptions.size(); i++)
                {
                	Subscription item = subscriptions.get(i); 
                	boolean securityError = Rules.isSecurityError(item.security());
                	if(!securityError)
                	{
	                    MarketMessageSubscriptionData msgSubData = new MarketMessageSubscriptionData(item, MarketEvent.GenerateFakeMessageData(item));
	                    this._messages.add(msgSubData);
                	}
                }
                break;

            default:
                throw new Exception(String.format("BEmu.MarketDataRequest.EventMarket.EventMarket: doesn't expect EventType %s", evtType.toString()));
        }
    }
	
	public MarketEvent(EventType evtType, Subscription subscription) throws Exception //use for unsubscribing
	{
        this._messages = new ArrayList<Message>();

        switch (evtType.intValue())
        {
	        case Event.EventType.Constants.SUBSCRIPTION_STATUS:
	        {
	        	this._eventType = evtType;
	        	MarketMessageSubscriptionCanceled msgCancel = new MarketMessageSubscriptionCanceled(subscription);
	        	this._messages.add(msgCancel);
	        }
	        break;
        }
        
	}
	
    private static Map<String, Object> GenerateFakeMessageData(Subscription sub)
    {
    	return com.bloomberglp.blpapi.RandomDataGenerator.getMarketDataFields(sub.fields());
    }
    
	public MessageIterator messageIterator()
	{
		return new MessageIterator(this._messages);
	}
    
}
