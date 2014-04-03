//------------------------------------------------------------------------------
// <copyright project="BEmuJava" file="BEmu.IntradayTickRequest.EventIntradayTick.java" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

package com.bemu.BEmu.IntradayTickRequest;

import com.bemu.BEmu.Event;
import com.bemu.BEmu.Message;
import com.bemu.BEmu.Datetime;

import java.util.Calendar;
import java.util.List;
import java.util.ArrayList;
import java.util.Map;
import java.util.TreeMap;
import java.util.Iterator;
import com.bemu.BEmu.types.Rules;

public class EventIntradayTick extends Event
{	
	public EventIntradayTick(RequestIntradayTick request) throws Exception
	{
		super._request = request;
		super._messages = this.generateMessages();
	}
	
	private List<Message> generateMessages() throws Exception
	{
		List<Message> result = new ArrayList<Message>();
		RequestIntradayTick ireq = (RequestIntradayTick)super._request;

        String security = ireq.security();
        boolean isResponseError = Rules.isSecurityError(security);

        if (isResponseError)
        {
            MessageIntradayTick msg = new MessageIntradayTick(super._request.correlationId(), ireq.getService());
            result.add(msg);
        }
        else
        {		
			Map<Datetime, Tuple3<String, Double, Integer>> tickData = new TreeMap<Datetime, Tuple3<String, Double, Integer>>();
			
			if(ireq.dtStart() != null)
			{
				List<Datetime> dates = ireq.getDates();
				Iterator<Datetime> iterator = dates.iterator();
				while (iterator.hasNext())
				{
					Datetime dtCurrent = iterator.next();
					if(dtCurrent.calendar().get(Calendar.DAY_OF_WEEK) != Calendar.SATURDAY && dtCurrent.calendar().get(Calendar.DAY_OF_WEEK) != Calendar.SUNDAY)
					{
						String t1 = "TRADE";
						Double t2 = com.bemu.BEmu.types.RandomDataGenerator.randomDouble();
						Integer t3 = com.bemu.BEmu.types.RandomDataGenerator.intradayTickTradeSize();
						
						Tuple3<String, Double, Integer> value = new Tuple3<String, Double, Integer>(t1, t2, t3);
						
						tickData.put(dtCurrent, value);
					}
				}
			}

			MessageIntradayTick msg = new MessageIntradayTick(super._request.correlationId(), tickData, ireq.includeConditionCodes(), ireq.getService());
			result.add(msg);
        }
		
		
		return result;		
	}
}
