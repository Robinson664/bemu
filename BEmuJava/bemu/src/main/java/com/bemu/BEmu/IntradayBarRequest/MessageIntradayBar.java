//------------------------------------------------------------------------------
// <copyright project="BEmuJava" file="BEmu.IntradayBarRequest.MessageIntradayBar.java" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

package com.bemu.BEmu.IntradayBarRequest;

import com.bemu.BEmu.Element;
import com.bemu.BEmu.Name;
import com.bemu.BEmu.Service;
import com.bemu.BEmu.Message;
import com.bemu.BEmu.CorrelationID;
import java.lang.StringBuilder;
import java.util.List;

public class MessageIntradayBar extends Message
{
	private final ElementBarData _parent;
    private final ElementIntradayBarResponseError _responseError;
    private final boolean _isResponseError;
	
    public MessageIntradayBar(CorrelationID corr, Service service, String security)
    {
    	super(new Name("IntradayBarResponse"), corr, service);
        this._responseError = new ElementIntradayBarResponseError(security);
        this._parent = null;
        this._isResponseError = true;
    }
    
    
	public MessageIntradayBar(CorrelationID corr, List<BarTickDataType> bars, Service service)
	{
		super(new Name("IntradayBarResponse"), corr, service);
		this._parent = new ElementBarData(bars);
        this._responseError = null;
        this._isResponseError = false;
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
        result.append("IntradayBarResponse (choice) = {" + System.getProperty("line.separator"));
        
        if(this._isResponseError)
        	result.append(this._responseError.prettyPrint(1));
        else        
        	result.append(this._parent.prettyPrint(1));
        
        result.append("}");

        return result.toString();
    }
	
}
