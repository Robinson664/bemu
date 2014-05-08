//------------------------------------------------------------------------------
// <copyright project="BEmu_maven" file="/BEmu_maven/bemu/src/main/java/com/bloomberglp/blpapi/ReferenceEvent.java" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

package com.bloomberglp.blpapi;

import com.bloomberglp.blpapi.Event;
import com.bloomberglp.blpapi.Message;
import com.bloomberglp.blpapi.CorrelationID;
import java.util.List;
import java.util.ArrayList;
import java.util.Map;
import java.util.HashMap;
import java.util.regex.Pattern;
import java.util.regex.Matcher;

public class ReferenceEvent extends Event
{
    public ReferenceEvent(ReferenceRequest request) throws Exception
    {
        super._request = request;
        super._messages = this.generateMessages();
    }
    
    private List<Message> generateMessages() throws Exception
    {
        List<Message> result = new ArrayList<Message>();
        ReferenceRequest rreq = (ReferenceRequest)super._request;

        Map<String, Map<String, Object>> securities = new HashMap<String, Map<String, Object>>();
        for(int i = 0; i < rreq.securities().size(); i++)
        {
        	String security = rreq.securities().get(i);
        	if(!securities.containsKey(security))
        	{
        		String strPattern = "[A-Z]{1,4}\\s+\\d{6}[CP]\\d{8} EQUITY";
        		Pattern p = Pattern.compile(strPattern);
        		Matcher m = p.matcher(security.toUpperCase());
        		boolean isOption = m.find();
        		
        		Map<String, Object> fieldData = new HashMap<String, Object>();
        		securities.put(security, fieldData);
        		
        		for(int j = 0; j < rreq.fields().size(); j++)
        		{
        			String field = rreq.fields().get(j);
                    Object value = com.bloomberglp.blpapi.RandomDataGenerator.referenceDataFromFieldName(field, security, isOption, rreq);
                    
                    if(value != null)
                    {
                    	fieldData.put(field, value);
                    }
        		}
        		
        	}
        }

        CorrelationID corr = super._request.correlationId(); 
        com.bloomberglp.blpapi.ReferenceMessage msg = new com.bloomberglp.blpapi.ReferenceMessage(corr, securities);
        result.add(msg);
        
        return result;
        
    }
}
