//------------------------------------------------------------------------------
// <copyright project="BEmuJava" file="BEmu.MarketDataRequest.EventMarket.java" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

package com.bemu.BEmu.MarketDataRequest;

import java.util.Map;
import java.util.List;
import java.util.ArrayList;

import com.bemu.BEmu.Event;
import com.bemu.BEmu.Message;
import com.bemu.BEmu.MessageIterator;
import com.bemu.BEmu.Subscription;
import com.bemu.BEmu.CorrelationID;

public class EventMarket extends Event
{
	private final List<Message> _messages;
	
	//don't use this.  It's not in the Bloomberg API
	public EventMarket(EventType evtType, CorrelationID corr, List<Subscription> subscriptions) throws Exception //use for subscribing
    {
        this._messages = new ArrayList<Message>();        
        
        switch (evtType.intValue())
        {        
            case Event.EventType.Constants.SESSION_STATUS:
            	super._eventType = evtType;
                MessageMarketSessionOpened msgSessionOpened = new MessageMarketSessionOpened();
                this._messages.add(msgSessionOpened);
                break;

            case Event.EventType.Constants.SERVICE_STATUS:
                super._eventType = evtType;
                MessageMarketServiceStatus msgServiceStatus = new MessageMarketServiceStatus(corr);
                this._messages.add(msgServiceStatus);
                break;

            case Event.EventType.Constants.SUBSCRIPTION_STATUS:
                super._eventType = evtType;
                
                for(int i = 0; i < subscriptions.size(); i++)
                {
                	Subscription item = subscriptions.get(i);
                	
                    MessageMarketSubscriptionStarted msgSubStatus = new MessageMarketSubscriptionStarted(item);
                    this._messages.add(msgSubStatus); 
                }
                break;

            case Event.EventType.Constants.SUBSCRIPTION_DATA:
                super._eventType = evtType;
                
                for(int i = 0; i < subscriptions.size(); i++)
                {
                	Subscription item = subscriptions.get(i);
                	
                    MessageMarketSubscriptionData msgSubData = new MessageMarketSubscriptionData(item, EventMarket.GenerateFakeMessageData(item));
                    this._messages.add(msgSubData);
                }
                break;

            default:
                throw new Exception(String.format("BEmu.MarketDataRequest.EventMarket.EventMarket: doesn't expect EventType %s", evtType.toString()));
        }
    }
	
    private static Map<String, Object> GenerateFakeMessageData(Subscription sub)
    {
    	return com.bemu.BEmu.types.RandomDataGenerator.getMarketDataFields(sub.fields());
    }
    
	public MessageIterator messageIterator()
	{
		return new MessageIterator(this._messages);
	}
    
}
