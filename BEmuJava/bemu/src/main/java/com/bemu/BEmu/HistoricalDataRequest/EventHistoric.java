//------------------------------------------------------------------------------
// <copyright project="BEmuJava" file="BEmu.HistoricalDataRequest.EventHistoric.java" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

package com.bemu.BEmu.HistoricalDataRequest;

import java.util.Calendar;
import java.util.List;
import java.util.ArrayList;
import java.util.Map;
import java.util.LinkedHashMap; //preserves insertion order
import com.bemu.BEmu.Event;
import com.bemu.BEmu.Message;
import com.bemu.BEmu.Datetime;

public class EventHistoric extends Event
{
    public EventHistoric(RequestHistoric request)
    {
        super._request = request;
        super._messages = this.generateMessages();
    }

    private List<Message> generateMessages()
    {
    	List<Message> result = new ArrayList<Message>();
    	RequestHistoric hreq = (RequestHistoric)super._request;
    	
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
    						fields.put(hfields.get(k), com.bemu.BEmu.types.RandomDataGenerator.randomDouble());
    					}

    					fieldData.put(current, fields);
    				}
    			}
    		}    		

            MessageHistoric msg = new MessageHistoric(super._request.correlationId(), security, fieldData, result.size());
            result.add(msg);    		
    	}
    	
    	return result;
    }
    
}
