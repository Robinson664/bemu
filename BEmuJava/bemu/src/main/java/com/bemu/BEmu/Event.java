//------------------------------------------------------------------------------
// <copyright project="BEmuJava" file="BEmu.Event.java" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

package com.bemu.BEmu;

import java.util.List;

public abstract class Event {
	protected EventType _eventType;
	protected List<Message> _messages;
	
	protected Request _request;
	
	static Event EventFactory(Request request, boolean isLastRequest) throws Exception
	{	
		Event result;
		if(request.getClass() == com.bemu.BEmu.IntradayBarRequest.RequestIntradayBar.class)
		{
			result = new com.bemu.BEmu.IntradayBarRequest.EventIntradayBar((com.bemu.BEmu.IntradayBarRequest.RequestIntradayBar)request);
			result._eventType = isLastRequest ? new EventType(Event.EventType.Constants.RESPONSE) : new EventType(Event.EventType.Constants.PARTIAL_RESPONSE);
			return result;
		}
		else if(request.getClass() == com.bemu.BEmu.IntradayTickRequest.RequestIntradayTick.class)
		{
			result = new com.bemu.BEmu.IntradayTickRequest.EventIntradayTick((com.bemu.BEmu.IntradayTickRequest.RequestIntradayTick)request);
			result._eventType = isLastRequest ? new EventType(Event.EventType.Constants.RESPONSE) : new EventType(Event.EventType.Constants.PARTIAL_RESPONSE);
			return result;
		}
		else if(request.getClass() == com.bemu.BEmu.HistoricalDataRequest.RequestHistoric.class)
		{
			result = new com.bemu.BEmu.HistoricalDataRequest.EventHistoric((com.bemu.BEmu.HistoricalDataRequest.RequestHistoric)request);
			result._eventType = isLastRequest ? new EventType(Event.EventType.Constants.RESPONSE) : new EventType(Event.EventType.Constants.PARTIAL_RESPONSE);
			return result;			
		}
		else if(request.getClass() == com.bemu.BEmu.ReferenceDataRequest.RequestReference.class)
		{
			result = new com.bemu.BEmu.ReferenceDataRequest.EventReference((com.bemu.BEmu.ReferenceDataRequest.RequestReference)request);
			result._eventType = isLastRequest ? new EventType(Event.EventType.Constants.RESPONSE) : new EventType(Event.EventType.Constants.PARTIAL_RESPONSE);
			return result;
		}
		throw new Exception("Todo: return appropriate events from requests");
	}
	
	public MessageIterator messageIterator()
	{
		return new MessageIterator(this._messages);
	}
	
	public EventType eventType()
	{
		return this._eventType;
	}
	
	public static class EventType
	{
		private int _value;
		
		public EventType(int value)
		{
			this._value = value;
		}
		
		public String toString()
		{
			switch (this._value)
			{
				case Constants.ADMIN: return "ADMIN";
				case Constants.SESSION_STATUS: return "SESSION_STATUS";
				case Constants.SUBSCRIPTION_STATUS: return "SUBSCRIPTION_STATUS";
				case Constants.REQUEST_STATUS: return "REQUEST_STATUS";
				case Constants.RESPONSE: return "RESPONSE";
				case Constants.PARTIAL_RESPONSE: return "PARTIAL_RESPONSE";
				case Constants.SUBSCRIPTION_DATA: return "SUBSCRIPTION_DATA";
				case Constants.SERVICE_STATUS: return "SERVICE_STATUS";
				case Constants.TIMEOUT: return "TIMEOUT";
				case Constants.AUTHORIZATION_STATUS: return "AUTHORIZATION_STATUS";
				case Constants.RESOLUTION_STATUS: return "RESOLUTION_STATUS";
				case Constants.TOPIC_STATUS: return "TOPIC_STATUS";
				case Constants.TOKEN_STATUS: return "TOKEN_STATUS";
				case Constants.REQUEST: return "REQUEST";
			}

			return "not implemented";
		}
		
		public int intValue()
		{
			return this._value;
		}
		
		public class Constants
		{
			public static final int ADMIN = 1;
			public static final int SESSION_STATUS = 2;
			public static final int SUBSCRIPTION_STATUS = 3;
			public static final int REQUEST_STATUS = 4;
			public static final int RESPONSE = 5;
			public static final int PARTIAL_RESPONSE = 6;
			public static final int SUBSCRIPTION_DATA = 8;
			public static final int SERVICE_STATUS = 9;
			public static final int TIMEOUT = 10;
			public static final int AUTHORIZATION_STATUS = 11;
			public static final int RESOLUTION_STATUS = 12;
			public static final int TOPIC_STATUS = 13;
			public static final int TOKEN_STATUS = 14;
			public static final int REQUEST = 15;
		}
	}
}
