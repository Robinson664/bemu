//------------------------------------------------------------------------------
// <copyright project="BEmu_maven" file="/BEmu_maven/bemu/src/main/java/com/bloomberglp/blpapi/IntradayBarMessage.java" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

package com.bloomberglp.blpapi;

import com.bloomberglp.blpapi.Element;
import com.bloomberglp.blpapi.Name;
import com.bloomberglp.blpapi.Service;
import com.bloomberglp.blpapi.Message;
import com.bloomberglp.blpapi.CorrelationID;
import java.lang.StringBuilder;
import java.util.List;

public class IntradayBarMessage extends Message
{
	private final IntradayBarElementData _parent;
    private final IntradayBarElementResponseError _responseError;
    private final boolean _isResponseError;
	
    public IntradayBarMessage(CorrelationID corr, Service service, String security) throws Exception
    {
    	super(new Name("IntradayBarResponse"), corr, service);
        this._responseError = new IntradayBarElementResponseError(security);
        this._parent = null;
        this._isResponseError = true;
    }
    
    
	public IntradayBarMessage(CorrelationID corr, List<IntradayBarTickDataType> bars, Service service) throws Exception
	{
		super(new Name("IntradayBarResponse"), corr, service);
		this._parent = new IntradayBarElementData(bars);
        this._responseError = null;
        this._isResponseError = false;
	}
	
	public boolean hasElement(String name) throws Exception
	{
		return this.hasElement(name, false);
	}
	
	public boolean hasElement(String name, boolean excludeNullElements) throws Exception
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
        
        try
    	{
	        if(this._isResponseError)
				result.append(this._responseError.prettyPrint(1));
			else        
	        	result.append(this._parent.prettyPrint(1));
    	}
        catch (Exception e) { }
        
        result.append("}");

        return result.toString();
    }
	
}
