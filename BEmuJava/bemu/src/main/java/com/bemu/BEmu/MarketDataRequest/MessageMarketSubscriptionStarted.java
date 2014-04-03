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
import com.bemu.BEmu.types.Rules;
import java.util.List;
import java.util.ArrayList;

public class MessageMarketSubscriptionStarted extends Message
{
    private final String _topicName;
    private final ElementMarketNull _exceptionsNull;
    private final ElementMarketExceptionsArray _exceptionsBadFields;

    MessageMarketSubscriptionStarted(Subscription sub) throws Exception
    {
    	super(new Name("SubscriptionStarted"), sub.correlationID(), null);
    	
        this._topicName = sub.security();

        { //deal with bad fields
            List<String> badFields = new ArrayList<String>();
            for (int i = sub.fields().size() - 1; i >= 0; i--)
            {
                if (Rules.isBadField(sub.fields().get(i)))
                {
                    badFields.add(sub.fields().get(i));
                    sub.fields().remove(i);
                }
            }

            if (badFields.size() == 0)
            {
                this._exceptionsNull = new ElementMarketNull("exceptions");
                this._exceptionsBadFields = null;
            }
            else
            {
            	this._exceptionsNull = null;
                this._exceptionsBadFields = new ElementMarketExceptionsArray(badFields);
            }
        }
    }
	
	public boolean hasElement(String name, boolean excludeNullElements) throws Exception
	{
		return (this._exceptionsNull != null && this._exceptionsNull.name().toString().equals(name)) ||
				(this._exceptionsBadFields != null && this._exceptionsBadFields.name().toString().equals(name));
	}

	public Element getElement(String name) throws Exception
	{
		if(this._exceptionsNull != null && name.equals(this._exceptionsNull.name().toString()))
			return this._exceptionsNull;
		
		else if(this._exceptionsBadFields != null && name.equals(this._exceptionsBadFields.name().toString()))
			return this._exceptionsBadFields;
		
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
    	String result;
    	
    	if(this._exceptionsNull != null)    	
    		result = String.format("SubscriptionStarted = {%s}%s", System.getProperty("line.separator"), System.getProperty("line.separator"));
    	
    	else if(this._exceptionsBadFields != null)
    	{
            StringBuilder strb = new StringBuilder();
            strb.append(String.format("SubscriptionStarted = {%s", this.messageType().toString(), System.getProperty("line.separator")));
            try
            {
            	strb.append(this._exceptionsBadFields.prettyPrint(1));
    		}
    	    catch (Exception e) { }
            strb.append("}" + System.getProperty("line.separator"));
            result = strb.toString();
    	}
    	else
    		result = "";
    		
    	return result;
    }
}
