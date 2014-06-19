//------------------------------------------------------------------------------
// <copyright project="BEmu_maven" file="/BEmu_maven/bemu/src/main/java/com/bloomberglp/blpapi/MarketMessageSubscriptionData.java" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

package com.bloomberglp.blpapi;

import java.util.Map;
import java.util.HashMap;
import java.util.Map.Entry;

import com.bloomberglp.blpapi.Name;
import com.bloomberglp.blpapi.Element;
import com.bloomberglp.blpapi.Subscription;
import com.bloomberglp.blpapi.Datetime;
import com.bloomberglp.blpapi.Message;

public class MarketMessageSubscriptionData extends Message
{
    private final Map<String, Element> _fields;
    private final String _security;

    MarketMessageSubscriptionData(Subscription sub, Map<String, Object> fields) throws Exception
    {
    	super(new Name("MarketDataEvents"), sub.correlationID(), null);
    	
        this._fields = new HashMap<String, Element>();
        
        for(Entry<String, Object> item : fields.entrySet())
        {
            Element elm = null;
            
            if (item.getValue().getClass() == double.class || item.getValue().getClass() == Double.class)
                elm = new MarketElementDouble(item.getKey(), (Double)item.getValue());

            else if (item.getValue().getClass() == Datetime.class)
            {
                Datetime temp = (Datetime)item.getValue();
                
                boolean isDate = temp.hasParts(Datetime.DATE);
                boolean isTime = temp.hasParts(Datetime.TIME);
                boolean isBoth = isDate && isTime;
                
                if(isBoth)
                	elm = new MarketElementDatetime(item.getKey(), temp);
                else if(isDate)
                	elm = new MarketElementDate(item.getKey(), temp);
                else if(isTime)
                	elm = new MarketElementTime(item.getKey(), temp);
            }

            else if (item.getValue().getClass() == int.class ||item.getValue().getClass() == Integer.class)
                elm = new MarketElementInt(item.getKey(), (Integer)item.getValue());
            
            else if (item.getValue().getClass() == String.class)
                elm = new MarketElementString(item.getKey(), (String)item.getValue());
            
            else if (item.getValue().getClass() == boolean.class || item.getValue().getClass() == Boolean.class)
                elm = new MarketElementBool(item.getKey(), (Boolean)item.getValue());

            String key = item.getKey();
            
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
	
	public boolean hasElement(String name, boolean excludeNullElements) throws Exception
	{
		for(Entry<String, Element> item : this._fields.entrySet())
		{
			if(item.getValue().name().toString().equals(name))
				return true;
		}
		return false;
	}
	
	public Element getElement(String name) throws Exception
	{
		for(Entry<String, Element> item : this._fields.entrySet())
		{
			if(item.getValue().name().toString().equals(name))
				return item.getValue();
		}
		return super.getElement(name);
	}
    
	public String toString()
	{
        StringBuilder result = new StringBuilder();

        result.append(String.format("%s = {%s", this.messageType().toString(), System.getProperty("line.separator")));
        
        try
        {
	        for(Entry<String, Element> item : this._fields.entrySet())
	        {
	        	result.append(item.getValue().prettyPrint(1));
	        }
		}
	    catch (Exception e) { }
        result.append(String.format("}%s", System.getProperty("line.separator")));
        
        return result.toString();
	}
    
}
