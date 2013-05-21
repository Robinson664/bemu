//------------------------------------------------------------------------------
// <copyright project="BEmuJava" file="BEmu.IntradayBarRequest.ElementIntradayBarInt.java" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

package com.bemu.BEmu.IntradayBarRequest;

import com.bemu.BEmu.Element;
import com.bemu.BEmu.Name;
import java.lang.StringBuilder;

public class ElementIntradayBarInt extends Element
{
    private final int _value;
    private final String _name;

    ElementIntradayBarInt(String name, int value)
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
    	return super.prettyPrintHelper(tabIndent, String.valueOf(this._value));
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
    
    public int getValueAsInt32()
    {
        return this._value;
    }

    public int getValueAsInt32(int index) throws Exception
    {
        if (index == 0)
            return this.getValueAsInt32();
        else
            return super.getValueAsInt32(index);
    }

}
