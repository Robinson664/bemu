//------------------------------------------------------------------------------
// <copyright project="BEmuJava" file="BEmu.CorrelationID.java" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

package com.bemu.BEmu;

public class CorrelationID
{
	private final boolean _isInternal;
	public boolean isInternal()
	{
		return this._isInternal;
	}
	
	private final boolean _isObject;
	public boolean isObject()
	{
		return this._isObject;
	}
	
	private final boolean _isValue;
	public boolean isValue()
	{
		return this._isValue;
	}
	
	private final long _value;
	public long value()
	{
		return this._value;
	}
	
	private final Object _object;
	public Object object()
	{
		return this._object;
	}
	
	private static long _nextInternalCorrelationId = 1;
	
	public CorrelationID(long value)
	{
		this._isValue = true;
		this._isObject = false;
		this._isInternal = false;
		this._value = value;
		this._object = null;
	}
	
    public CorrelationID(CorrelationID value)
    {
		this._isValue = value._isValue;
		this._isObject = value._isObject;
		this._isInternal = value._isInternal;
		this._value = value._value;
		this._object = value._object;
    }
	
	public CorrelationID()
	{
		this._isValue = true;
		this._isObject = false;
		this._isInternal = true;
		this._value = CorrelationID._nextInternalCorrelationId++;
		this._object = null;
	}
	
	public boolean equals(Object arg0)
	{
		if(arg0 != null && arg0.getClass() == CorrelationID.class)
		{
			CorrelationID corr = (CorrelationID)arg0;
			
			if (this._isObject != corr._isObject)
			    return false;
			
			else if (this._isObject)
				return this._object.equals(corr._object);
			
			else //value
			    return this._value == corr._value;
		}
		else
			return false;
	}
	
	public int hashCode()
	{
		if (this._isObject)
		    return this._object.hashCode();
		
		else
		    return (int)this._value;
	}
	
	public String toString()
	{
		if (this._isValue)
		        return String.format("%s: %d",
			        this._isInternal ? "Internal" : "User",
			        this._value);
		
		else //object
		    return String.format("%s: %s",
		        this._isInternal ? "Internal" : "User",
		        this._object.toString());
	}
}