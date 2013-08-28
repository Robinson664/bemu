//------------------------------------------------------------------------------
// <copyright project="BEmuJava" file="BEmu.IntradayTickRequest.MessageIntradayTick.java" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

package com.bemu.BEmu.IntradayTickRequest;

import com.bemu.BEmu.Element;
import com.bemu.BEmu.Message;
import com.bemu.BEmu.Service;
import com.bemu.BEmu.Name;
import com.bemu.BEmu.Datetime;
import com.bemu.BEmu.CorrelationID;

import java.util.Map;

public class MessageIntradayTick extends Message
{
	private final ElementIntradayTickDataParent _parent;
    private final ElementIntradayTickResponseError _responseError;
    private final boolean _isResponseError;
	
    MessageIntradayTick(CorrelationID corr, Map<Datetime, Tuple3<String, Double, Integer>> ticks, boolean includeConditionCodes, Service service)
    {
    	super(new Name("IntradayTickResponse"), corr, service);
        this._parent = new ElementIntradayTickDataParent(ticks, includeConditionCodes);
        this._responseError = null;
        this._isResponseError = false;
    }
    
    MessageIntradayTick(CorrelationID corr, Service service)
    {
    	super(new Name("IntradayTickResponse"), corr, service);
        this._parent = null;
        this._responseError = new ElementIntradayTickResponseError();
        this._isResponseError = true;
    }
    
	public Element getElement(String name) throws Exception
	{
		if(this._isResponseError)
		{
			if(name.equals(this._responseError.name().toString()))
				return this._responseError;
		}
		else
		{
			if(name.equals(this._parent.name().toString()))
				return this._parent;
		}
		
		throw new Exception("not implemented. names are case-sensitive.");
	}
	
	public boolean hasElement(String name)
	{
		return this.hasElement(name, false);
	}
	
	public boolean hasElement(String name, boolean excludeNullElements)
	{
		return 
				(this._isResponseError && name.equals(this._responseError.name().toString())) ||
				(!this._isResponseError && name.equals(this._parent.name().toString()));
	}
	
	ElementIntradayTickDataParent firstElement()
	{
		return this._parent;
	}
    
	public String topicName()
	{
		return "";
	}
	
	public int numElements()
	{
		return 1;
	}
	
    public String toString()
    {
        StringBuilder result = new StringBuilder();
        result.append("IntradayTickResponse (choice) = {" + System.getProperty("line.separator"));
        
        if(this._isResponseError)
        	result.append(this._responseError.prettyPrint(1));
        
        else
        	result.append(this._parent.prettyPrint(1));
        
        result.append("}");

        return result.toString();
    }
}
