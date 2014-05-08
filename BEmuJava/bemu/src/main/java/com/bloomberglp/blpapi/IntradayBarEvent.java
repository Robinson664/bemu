//------------------------------------------------------------------------------
// <copyright project="BEmu_maven" file="/BEmu_maven/bemu/src/main/java/com/bloomberglp/blpapi/IntradayBarEvent.java" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

package com.bloomberglp.blpapi;

import com.bloomberglp.blpapi.Event;
import com.bloomberglp.blpapi.Message;
import com.bloomberglp.blpapi.Datetime;
import java.util.List;
import java.util.ArrayList;

public class IntradayBarEvent extends Event
{
	public IntradayBarEvent(IntradayBarRequest request) throws Exception
	{
		super._request = request;
		super._messages = this.generateMessages();
	}
	
    private List<Message> generateMessages() throws Exception
    {
        List<Message> result = new ArrayList<Message>();
        IntradayBarRequest ireq = (IntradayBarRequest)super._request;

        String security = ireq.security();
        boolean securityError = Rules.isSecurityError(security);
        if(securityError)
        {
            IntradayBarMessage msg = new IntradayBarMessage(super._request.correlationId(), ireq.getService(), security);
            result.add(msg);
        }
        else
        {
	        List<IntradayBarTickDataType> barData = new ArrayList<IntradayBarTickDataType>();	        
	        if(ireq.getDtStart() != null)
	        {
	        	List<Datetime> dates = ireq.getDateTimes();
	        	for(int i = 0; i < dates.size(); i++)
	        	{
	        		Datetime dtCurrent = dates.get(i);
	        		IntradayBarTickDataType value = com.bloomberglp.blpapi.RandomDataGenerator.generateBarData(dtCurrent);
	        		barData.add(value);
	        	}
	        }
	        
	        IntradayBarMessage msg = new IntradayBarMessage(super._request.correlationId(), barData, ireq.getService());
	        result.add(msg);
        }

        return result;
    }

    public List<Message> GetMessages()
    {
        return this._messages;
    }
	
}
