package com.bemu.BEmu.ReferenceDataRequest;

import com.bemu.BEmu.Event;
import com.bemu.BEmu.Message;
import com.bemu.BEmu.CorrelationID;
import java.util.List;
import java.util.ArrayList;
import java.util.Map;
import java.util.HashMap;
import java.util.regex.Pattern;
import java.util.regex.Matcher;

public class EventReference extends Event
{
    public EventReference(RequestReference request) throws Exception
    {
        super._request = request;
        super._messages = this.generateMessages();
    }
    
    private List<Message> generateMessages() throws Exception
    {
        List<Message> result = new ArrayList<Message>();
        RequestReference rreq = (RequestReference)super._request;

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
                    Object value = com.bemu.BEmu.types.RandomDataGenerator.referenceDataFromFieldName(field, security, isOption, rreq);
                    
                    if(value != null)
                    {
                    	fieldData.put(field.toUpperCase(), value);
                    }
        		}
        		
        	}
        }

        CorrelationID corr = super._request.correlationId(); 
        com.bemu.BEmu.ReferenceDataRequest.MessageReference msg = new com.bemu.BEmu.ReferenceDataRequest.MessageReference(corr, securities);
        result.add(msg);
        
        return result;
        
    }
}
