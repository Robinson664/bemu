//------------------------------------------------------------------------------
// <copyright project="BEmuJava" file="BEmu.CorrelationID.java" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

package com.bemu.BEmu;

public class CorrelationID {
	private boolean _isInternal;
	public boolean IsInternal()
	{
		return this._isInternal;
	}
	
	private long _value;
	public long value()
	{
		return this._value;
	}
	
	private static long _nextInternalCorrelationId = 1;
	
	public CorrelationID(long value)
	{
		this._value = value;
		this._isInternal = false;
	}
	
	public CorrelationID()
	{
		this._value = CorrelationID._nextInternalCorrelationId++;
		this._isInternal = true;
	}
	
	public String toString()
	{
		return String.format("%s: %d",
				this._isInternal ? "Internal" : "User",
				this._value);
	}
}