//------------------------------------------------------------------------------
// <copyright project="BEmu_maven" file="/BEmu_maven/bemu/src/main/java/com/bloomberglp/blpapi/Event.java" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

package com.bloomberglp.blpapi;

import java.util.List;

public abstract class Event
{
	protected EventType _eventType;
	protected List<Message> _messages;
	
	protected Request _request;
	
	static Event EventFactory(Request request, boolean isLastRequest) throws Exception
	{	
		Event result;
		if(request.getClass() == com.bloomberglp.blpapi.IntradayBarRequest.class)
		{
			result = new com.bloomberglp.blpapi.IntradayBarEvent((com.bloomberglp.blpapi.IntradayBarRequest)request);
			result._eventType = isLastRequest ? Event.EventType.RESPONSE : Event.EventType.PARTIAL_RESPONSE;
			return result;
		}
		else if(request.getClass() == com.bloomberglp.blpapi.IntradayTickRequest.class)
		{
			result = new com.bloomberglp.blpapi.IntradayTickEvent((com.bloomberglp.blpapi.IntradayTickRequest)request);
			result._eventType = isLastRequest ? Event.EventType.RESPONSE : Event.EventType.PARTIAL_RESPONSE;
			return result;
		}
		else if(request.getClass() == com.bloomberglp.blpapi.HistoricRequest.class)
		{
			result = new com.bloomberglp.blpapi.HistoricEvent((com.bloomberglp.blpapi.HistoricRequest)request);
			result._eventType = isLastRequest ? Event.EventType.RESPONSE : Event.EventType.PARTIAL_RESPONSE;
			return result;			
		}
		else if(request.getClass() == com.bloomberglp.blpapi.ReferenceRequest.class)
		{
			result = new com.bloomberglp.blpapi.ReferenceEvent((com.bloomberglp.blpapi.ReferenceRequest)request);
			result._eventType = isLastRequest ? Event.EventType.RESPONSE : Event.EventType.PARTIAL_RESPONSE;
			return result;
		}
		throw new Exception("not implemented");
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
		
		public boolean equals(Object arg)
		{
			if(arg == null)
				return false;
			
			else if(arg.getClass() == EventType.class)
				return this._value == ((EventType)arg)._value;
			
			else
				return false;
		}
		
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

		public static final EventType RESPONSE = new EventType(Constants.RESPONSE);
		public static final EventType PARTIAL_RESPONSE = new EventType(Constants.PARTIAL_RESPONSE);
		public static final EventType ADMIN = new EventType(Constants.ADMIN);
		public static final EventType SESSION_STATUS = new EventType(Constants.SESSION_STATUS);
		public static final EventType SUBSCRIPTION_STATUS = new EventType(Constants.SUBSCRIPTION_STATUS);
		public static final EventType REQUEST_STATUS = new EventType(Constants.REQUEST_STATUS);
		public static final EventType SUBSCRIPTION_DATA = new EventType(Constants.SUBSCRIPTION_DATA);
		public static final EventType SERVICE_STATUS = new EventType(Constants.SERVICE_STATUS);
		public static final EventType TIMEOUT = new EventType(Constants.TIMEOUT);
		public static final EventType AUTHORIZATION_STATUS = new EventType(Constants.AUTHORIZATION_STATUS);
		public static final EventType RESOLUTION_STATUS = new EventType(Constants.RESOLUTION_STATUS);
		public static final EventType TOPIC_STATUS = new EventType(Constants.TOPIC_STATUS);
		public static final EventType TOKEN_STATUS = new EventType(Constants.TOKEN_STATUS);
		public static final EventType REQUEST = new EventType(Constants.REQUEST);
	}
}
