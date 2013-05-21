//------------------------------------------------------------------------------
// <copyright project="BEmuJava" file="BEmu.IntradayBarRequest.EventIntradayBar.java" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

package com.bemu.BEmu.IntradayBarRequest;

import com.bemu.BEmu.Event;
import com.bemu.BEmu.Message;
import com.bemu.BEmu.Datetime;
import java.util.List;
import java.util.ArrayList;

public class EventIntradayBar extends Event
{
	public EventIntradayBar(RequestIntradayBar request) throws Exception
	{
		super._request = request;
		super._messages = this.generateMessages();
	}
	
    private List<Message> generateMessages() throws Exception
    {
        List<Message> result = new ArrayList<Message>();
        RequestIntradayBar ireq = (RequestIntradayBar)super._request;

        List<BarTickDataType> barData = new ArrayList<BarTickDataType>();
        
        if(ireq.getDtStart() != null)
        {
        	List<Datetime> dates = ireq.getDateTimes();
        	for(int i = 0; i < dates.size(); i++)
        	{
        		Datetime dtCurrent = dates.get(i);
        		BarTickDataType value = com.bemu.BEmu.types.RandomDataGenerator.generateBarData(dtCurrent);
        		barData.add(value);
        	}
        }

        MessageIntradayBar msg = new MessageIntradayBar(super._request.correlationId(), barData, ireq.getService());
        result.add(msg);

        return result;
    }
	
}
