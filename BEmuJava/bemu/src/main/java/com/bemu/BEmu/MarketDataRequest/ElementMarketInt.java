//------------------------------------------------------------------------------
// <copyright project="BEmuJava" file="BEmu.MarketDataRequest.ElementMarketInt.java" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

package com.bemu.BEmu.MarketDataRequest;

import com.bemu.BEmu.Name;

public class ElementMarketInt extends ElementParent
{
	private final int _value;
	private final String _name;
	
	ElementMarketInt(String name, int value)
	{
		this._name = name;
		this._value = value;
	}
	
    public Name name()
    {
    	return new Name(this._name);
    }
    
    public int numValues()
    {
    	return 1;
    }
    
    public int numElements()
    {
    	return 0;
    }
    
    public boolean isComplexType()
    {
    	return false;
    }
    
    public boolean isArray()
    {
    	return false;
    }
    
    public boolean isNull()
    {
    	return false;
    }
    
    protected StringBuilder prettyPrint(int tabIndent)
    {
    	return super.prettyPrintHelper(tabIndent, String.valueOf(this._value));
    }
    
    public Object getValue()
    {
    	return this._value;
    }
    
    public double getValueAsFloat64()
    {
        return this._value;
    }
    
    public int getValueAsInt32()
    {
        return this._value;
    }
    
    public long getValueAsInt64()
    {
        return this._value;
    }
    
    public float getValueAsFloat32()
    {
        return this._value;
    }
}
