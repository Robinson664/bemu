package BEmu.HistoricalDataRequest;

import java.util.Calendar;
import java.util.List;
import java.util.ArrayList;
import java.util.Map;
import java.util.LinkedHashMap; //preserves insertion order
import BEmu.Event;
import BEmu.Message;
import BEmu.Datetime;

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
    						fields.put(hfields.get(k), BEmu.Types.RandomDataGenerator.randomDouble());
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
