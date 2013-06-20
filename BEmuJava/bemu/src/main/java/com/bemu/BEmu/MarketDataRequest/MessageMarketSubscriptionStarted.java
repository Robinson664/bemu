//------------------------------------------------------------------------------
// <copyright project="BEmuJava" file="BEmu.MarketDataRequest.MessageMarketSubscriptionStarted.java" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

package com.bemu.BEmu.MarketDataRequest;

import com.bemu.BEmu.Element;
import com.bemu.BEmu.Message;
import com.bemu.BEmu.Subscription;
import com.bemu.BEmu.Name;

public class MessageMarketSubscriptionStarted extends Message
{
    private final String _topicName;
    private final ElementMarketNull _exceptions;

    MessageMarketSubscriptionStarted(Subscription sub)
    {
    	super(new Name("SubscriptionStarted"), sub.correlationID(), null);
    	
        this._topicName = sub.security();
        this._exceptions = new ElementMarketNull("exceptions");
    }

	public Element getElement(String name) throws Exception
	{
		if(name.toLowerCase().equals(this._exceptions.name().toString().toLowerCase()))
			return this._exceptions;
		else
			throw new Exception("not implemented");
	}
    
	public int numElements()
	{
		return 1;
	}
    
	public String topicName()
	{
		return this._topicName;
	}

    public String toString()
    {
    	return String.format("SubscriptionStarted = {%s}%s", System.getProperty("line.separator"), System.getProperty("line.separator"));
    }
}
