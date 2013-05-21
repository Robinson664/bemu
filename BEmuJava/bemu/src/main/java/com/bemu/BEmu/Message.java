//------------------------------------------------------------------------------
// <copyright project="BEmuJava" file="BEmu.Message.java" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

package com.bemu.BEmu;

public abstract class Message {
	
	private Service _service;
	public Service service()
	{
		return this._service;
	}
	
	private Name _messageType;
	public Name messageType()
	{
		return this._messageType;
	}

	private CorrelationID _correlationID;
	public CorrelationID correlationID()
	{
		return this._correlationID;
	}
	
	protected Message(Name messageType, CorrelationID corr, Service service)
	{
		this._correlationID = corr;
		this._messageType = messageType;
		this._service = service;
	}
	
	public Element getElement(Name name) throws Exception
	{
		return this.getElement(name.toString());
	}
	
	public Element getElement(String name) throws Exception
	{
		throw new Exception("not implemented");
	}
	
	public boolean hasElement(String name, boolean excludeNullElements) throws Exception
	{
		throw new Exception("not implemented");
	}
	
	public boolean hasElement(String name) throws Exception
	{
		return this.hasElement(name, false);
	}
	
	public boolean hasElement(Name name, boolean excludeNullElements) throws Exception
	{
		return this.hasElement(name.toString(), excludeNullElements);
	}
	
	public boolean hasElement(Name name) throws Exception
	{
		return this.hasElement(name.toString());
	}
	
	public int numElements() throws Exception
	{
		throw new Exception("not implemented");
	}
	
	public int numValues() throws Exception
	{
		throw new Exception("not implemented");
	}
	
	public String topicName() throws Exception
	{
		throw new Exception("not implemented");
	}

	
	public double getElementAsFloat64(String name) throws Exception
	{
		return this.getElement(name).getValueAsFloat64();
	}
	
	public float getElementAsFloat32(String name) throws Exception
	{
		return this.getElement(name).getValueAsFloat32();
	}
	
	public long getElementAsInt64(String name) throws Exception
	{
		return this.getElement(name).getValueAsInt64();
	}
	
	public int getElementAsInt32(String name) throws Exception
	{
		return this.getElement(name).getValueAsInt32();
	}
	
	public String getElementAsString(String name) throws Exception
	{
		return this.getElement(name).getValueAsString();
	}
	
	public Datetime getElementAsDatetime(String name) throws Exception
	{
		return this.getElement(name).getValueAsDatetime();
	}
	
	public Datetime getElementAsDate(String name) throws Exception
	{
		return this.getElement(name).getValueAsDate();
	}
	
	public Datetime getElementAsTime(String name) throws Exception
	{
		return this.getElement(name).getValueAsTime();
	}
	
}
