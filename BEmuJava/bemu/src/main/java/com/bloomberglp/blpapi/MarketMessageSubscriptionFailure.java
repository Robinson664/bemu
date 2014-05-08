//------------------------------------------------------------------------------
// <copyright project="BEmu_maven" file="/BEmu_maven/bemu/src/main/java/com/bloomberglp/blpapi/MarketMessageSubscriptionFailure.java" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

package com.bloomberglp.blpapi;

import com.bloomberglp.blpapi.Element;
import com.bloomberglp.blpapi.Subscription;
import com.bloomberglp.blpapi.Message;
import com.bloomberglp.blpapi.Name;

public class MarketMessageSubscriptionFailure extends Message
{
    private final String _topicName;
    private final MarketElementReason _reason;

    MarketMessageSubscriptionFailure(Subscription sub) throws Exception
    {
    	super(new Name("SubscriptionFailure"), sub.correlationID(), null);
    	
        this._topicName = sub.security();
        this._reason = new MarketElementReason(MarketElementReason.ReasonTypeEnum.badSecurity);
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
