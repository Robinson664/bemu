//------------------------------------------------------------------------------
// <copyright project="BEmuJava" file="BEmu.IntradayTickRequest.ElementIntradayTickString.java" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

package com.bemu.BEmu.IntradayTickRequest;

import com.bemu.BEmu.Name;
import java.lang.StringBuilder;

public class ElementIntradayTickString extends ElementParent
{
    private final String _value;
    private final String _name;

    ElementIntradayTickString(String name, String value)
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
    
    public boolean hasElement(String name)
    {
    	return false;
    }
    
    public boolean hasElement(String name, boolean excludeNullElements)
    {
    	return false;
    }
    
    protected StringBuilder prettyPrint(int tabIndent)
    {
    	return super.prettyPrintHelper(tabIndent, this._value);
    }
    
    public Object getValue()
    {
    	return this._value;
    }
    
    public Object getValue(int index) throws Exception
    {
    	if(index == 0)
    		return this.getValue();
    	else
    		return super.getValue();
    }
    
    public String getValueAsString()
    {
        return this._value;
    }

    public String getValueAsString(int index) throws Exception
    {
        if (index == 0)
            return this.getValueAsString();
        else
            return super.getValueAsString(index);
    }
}
