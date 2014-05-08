//------------------------------------------------------------------------------
// <copyright project="BEmu_maven" file="/BEmu_maven/bemu/src/main/java/com/bloomberglp/blpapi/MarketMessageSubscriptionCanceled.java" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

package com.bloomberglp.blpapi;

import com.bloomberglp.blpapi.Message;
import com.bloomberglp.blpapi.Subscription;
import com.bloomberglp.blpapi.Name;
import com.bloomberglp.blpapi.Element;

public class MarketMessageSubscriptionCanceled extends Message
{
    private final String _topicName;
    private final MarketElementSubscriptionCancelReason _reason;

    MarketMessageSubscriptionCanceled(Subscription sub) throws Exception
    {
    	super(new Name("SubscriptionTerminated"), sub.correlationID(), null);
    	
        this._topicName = sub.security();
        this._reason = new MarketElementSubscriptionCancelReason();
    }
    
	public int numElements()
	{
		return 1;
	}
    
	public String topicName()
	{
		return this._topicName;
	}
	
	public boolean hasElement(String name, boolean excludeNullElements) throws Exception
	{
		return this._reason.name().toString().equals(name);
	}
	
	public Element getElement(String name) throws Exception
	{
		if(name.equals(this._reason.name().toString()))
			return this._reason;
			
		else
			return super.getElement(name);
	}
	
    public String toString()
    {
        StringBuilder result = new StringBuilder();
        result.append(String.format("%s = {%s", this.messageType().toString(), System.getProperty("line.separator")));
        try
        {
        	result.append(this._reason.prettyPrint(1));
		}
	    catch (Exception e) { }
        result.append("}" + System.getProperty("line.separator"));

        return result.toString();
    }

}
