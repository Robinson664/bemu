//------------------------------------------------------------------------------
// <copyright project="BEmu_maven" file="/BEmu_maven/bemu/src/main/java/com/bloomberglp/blpapi/IntradayTickEvent.java" company="Jordan Robinson">
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

import java.util.Calendar;
import java.util.List;
import java.util.ArrayList;
import java.util.Map;
import java.util.TreeMap;
import java.util.Iterator;

public class IntradayTickEvent extends Event
{	
	public IntradayTickEvent(IntradayTickRequest request) throws Exception
	{
		super._request = request;
		super._messages = this.generateMessages();
	}
	
	private List<Message> generateMessages() throws Exception
	{
		List<Message> result = new ArrayList<Message>();
		IntradayTickRequest ireq = (IntradayTickRequest)super._request;

        String security = ireq.security();
        boolean isResponseError = Rules.isSecurityError(security);

        if (isResponseError)
        {
            IntradayTickMessage msg = new IntradayTickMessage(super._request.correlationId(), ireq.getService());
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
						Double t2 = com.bloomberglp.blpapi.RandomDataGenerator.randomDouble();
						Integer t3 = com.bloomberglp.blpapi.RandomDataGenerator.intradayTickTradeSize();
						
						Tuple3<String, Double, Integer> value = new Tuple3<String, Double, Integer>(t1, t2, t3);
						
						tickData.put(dtCurrent, value);
					}
				}
			}

			IntradayTickMessage msg = new IntradayTickMessage(super._request.correlationId(), tickData, ireq.includeConditionCodes(), ireq.getService());
			result.add(msg);
        }
		
		
		return result;		
	}
}
