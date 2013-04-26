//------------------------------------------------------------------------------
// <copyright project="BEmuJava" file="BEmu.Event.java" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

package BEmu;

import java.util.List;

public abstract class Event {
	protected EventType _eventType;
	protected List<Message> _messages;
	
	protected Request _request;
	
	static Event EventFactory(Request request, boolean isLastRequest) throws Exception
	{	
		Event result;
		if(request.getClass() == BEmu.IntradayBarRequest.RequestIntradayBar.class)
		{
			result = new BEmu.IntradayBarRequest.EventIntradayBar((BEmu.IntradayBarRequest.RequestIntradayBar)request);
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
