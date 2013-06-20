//------------------------------------------------------------------------------
// <copyright project="BEmuJava" file="BEmu.MarketDataRequest.MessageMarketSubscriptionData.java" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

package com.bemu.BEmu.MarketDataRequest;

import java.util.Map;
import java.util.HashMap;
import java.util.Map.Entry;

import com.bemu.BEmu.Name;
import com.bemu.BEmu.Subscription;
import com.bemu.BEmu.Datetime;
import com.bemu.BEmu.Message;

public class MessageMarketSubscriptionData extends Message
{
    private final Map<String, ElementParent> _fields;
    private final String _security;

    MessageMarketSubscriptionData(Subscription sub, Map<String, Object> fields)
    {
    	super(new Name("MarketDataEvents"), sub.correlationID(), null);
    	
        this._fields = new HashMap<String, ElementParent>();
        
        for(Entry<String, Object> item : fields.entrySet())
        {
            ElementParent elm = null;
            
            if (item.getValue().getClass() == double.class || item.getValue().getClass() == Double.class)
                elm = new ElementMarketDouble(item.getKey(), (Double)item.getValue());

            else if (item.getValue().getClass() == Datetime.class)
            {
                Datetime temp = (Datetime)item.getValue();
                switch (temp.DateTimeType())
                {
                    case date:
                        elm = new ElementMarketDate(item.getKey(), temp);
                        break;
                    case time:
                        elm = new ElementMarketTime(item.getKey(), temp);
                        break;
                    case both:
                        elm = new ElementMarketDatetime(item.getKey(), temp);
                        break;
                    default:
                    	break;
                }
            }

            else if (item.getValue().getClass() == int.class ||item.getValue().getClass() == Integer.class)
                elm = new ElementMarketInt(item.getKey(), (Integer)item.getValue());
            
            else if (item.getValue().getClass() == String.class)
                elm = new ElementMarketString(item.getKey(), (String)item.getValue());
            
            else if (item.getValue().getClass() == boolean.class || item.getValue().getClass() == Boolean.class)
                elm = new ElementMarketBool(item.getKey(), (Boolean)item.getValue());

            String key = item.getKey().toUpperCase();
            
            if (elm != null)
                this._fields.put(key, elm);
        }
        this._security = sub.security();
    }

    public String topicName()
    {
    	return this._security;
    }
    
    public int numElements()
    {
    	return this._fields.size();
    }
    
	public String toString()
	{
        StringBuilder result = new StringBuilder();

        result.append(String.format("%s = {%s", this.messageType().toString(), System.getProperty("line.separator")));
        
        for(Entry<String, ElementParent> item : this._fields.entrySet())
        {
        	result.append(item.getValue().prettyPrint(1));
        }
        result.append(String.format("}%s", System.getProperty("line.separator")));
        
        return result.toString();
	}
    
}
