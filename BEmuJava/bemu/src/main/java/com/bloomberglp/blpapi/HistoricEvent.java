//------------------------------------------------------------------------------
// <copyright project="BEmu_maven" file="/BEmu_maven/bemu/src/main/java/com/bloomberglp/blpapi/HistoricEvent.java" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

package com.bloomberglp.blpapi;

import java.util.Calendar;
import java.util.List;
import java.util.ArrayList;
import java.util.Map;
import java.util.LinkedHashMap; //preserves insertion order
import com.bloomberglp.blpapi.Event;
import com.bloomberglp.blpapi.Message;
import com.bloomberglp.blpapi.Datetime;

public class HistoricEvent extends Event
{
    public HistoricEvent(HistoricRequest request) throws Exception
    {
        super._request = request;
        super._messages = this.generateMessages();
    }

    private List<Message> generateMessages() throws Exception
    {
    	List<Message> result = new ArrayList<Message>();
    	HistoricRequest hreq = (HistoricRequest)super._request;
    	
    	List<String> badFields = new ArrayList<String>();
    	for(int i = hreq.fields().size() - 1; i >= 0; i--)
    	{
    		if(Rules.isBadField(hreq.fields().get(i)))
    		{
    			badFields.add(hreq.fields().get(i));
    			hreq.fields().remove(i);
    		}
    	}    	
    	
    	List<String> securities = hreq.securities();
    	for(int i = 0; i < securities.size(); i++)
    	{
    		String security = securities.get(i);
    		Map<Datetime, Map<String, Object>> fieldData = new LinkedHashMap<Datetime, Map<String, Object>>();
    		
    		if(hreq.dtStart() != null)
    		{
    			List<Datetime> dates = hreq.getDates();
    			for(int j = 0; j < dates.size(); j++)
    			{
    				Datetime current = dates.get(j);
    				if((current.calendar().get(Calendar.DAY_OF_WEEK) != Calendar.SUNDAY) && (current.calendar().get(Calendar.DAY_OF_WEEK) != Calendar.SATURDAY))
    				{
    					Map<String, Object> fields = new LinkedHashMap<String, Object>();
    					
    					List<String> hfields = hreq.fields();
    					for(int k = 0; k < hfields.size(); k++)
    					{
    						double dbl = com.bloomberglp.blpapi.RandomDataGenerator.randomDouble();
    						fields.put(hfields.get(k), dbl);
    					}

    					fieldData.put(current, fields);
    				}
    			}
    		}    		

            HistoricMessage msg = new HistoricMessage(super._request.correlationId(), security, badFields, fieldData, result.size());
            result.add(msg);    		
    	}
    	
    	return result;
    }
    
}
