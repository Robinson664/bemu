//------------------------------------------------------------------------------
// <copyright project="BEmuJava" file="BEmu.MarketDataRequest.MessageMarketSubscriptionFailure.java" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

package com.bemu.BEmu.MarketDataRequest;

import com.bemu.BEmu.Element;
import com.bemu.BEmu.Subscription;
import com.bemu.BEmu.Message;
import com.bemu.BEmu.Name;

public class MessageMarketSubscriptionFailure extends Message
{
    private final String _topicName;
    private final ElementMarketReason _reason;

    MessageMarketSubscriptionFailure(Subscription sub) throws Exception
    {
    	super(new Name("SubscriptionFailure"), sub.correlationID(), null);
    	
        this._topicName = sub.security();
        this._reason = new ElementMarketReason(ElementMarketReason.ReasonTypeEnum.badSecurity);
    }

    public String topicName()
    {
    	return this._topicName;
    }
    
    public int numElements()
    {
    	return 1;
    }
	
	public boolean hasElement(String name, boolean excludeNullElements) throws Exception
	{
		return this._reason.name().toString().equals(name);
	}
	
	public Element getElement(String name) throws Exception
	{
		if(this._reason.name().toString().equals(name))
			return this._reason;
		else
			return super.getElement(name);
	}
    
	public String toString()
	{
        StringBuilder result = new StringBuilder();

        result.append(String.format("SubscriptionFailure = {%s", System.getProperty("line.separator")));
    	try
    	{
    		result.append(this._reason.prettyPrint(1));
		}
	    catch (Exception e) { }        
        result.append(String.format("}%s", System.getProperty("line.separator")));
        
        return result.toString();
	}

}
