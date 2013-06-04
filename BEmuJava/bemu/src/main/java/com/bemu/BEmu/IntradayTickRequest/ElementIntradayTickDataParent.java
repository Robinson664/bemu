//------------------------------------------------------------------------------
// <copyright project="BEmuJava" file="BEmu.IntradayTickRequest.ElementIntradayTickDataParent.java" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

package com.bemu.BEmu.IntradayTickRequest;

import java.util.Map;
import java.lang.StringBuilder;

import com.bemu.BEmu.Element;
import com.bemu.BEmu.Name;
import com.bemu.BEmu.Datetime;

public class ElementIntradayTickDataParent extends ElementParent
{
    private final ElementIntradayTickDataArray _array;
    
    ElementIntradayTickDataParent(Map<Datetime, Tuple3<String, Double, Integer>> ticks, boolean includeConditionCodes)
    {
        this._array = new ElementIntradayTickDataArray(ticks, includeConditionCodes);
    }
    
	public Name name()
	{
		return new Name("tickData");
	}

	public int numValues()
	{
		return 1;
	}

	public int numElements()
	{
		return 1;
	}
	
    public boolean isComplexType()
    {
    	return true;
    }
    
    public boolean isArray()
    {
    	return false;
    }
    
    public boolean isNull()
    {
    	return false;
    }
    
    public Element getElement(String name) throws Exception
    {
    	if(this._array.name().toString().toUpperCase().equals(name.toUpperCase()))
    		return this._array;
    	else
    		return super.getElement(name);
    }
    
	protected StringBuilder prettyPrint(int tabIndent)
	{
        String tabs = com.bemu.BEmu.types.IndentType.Indent(tabIndent);
        StringBuilder result = new StringBuilder();

        result.append(String.format("%s%s = {%s", tabs, this.name().toString(), System.getProperty("line.separator")));
    	result.append(this._array.prettyPrint(tabIndent + 1));
        result.append(String.format("%s}%s", tabs, System.getProperty("line.separator")));
        
        return result;
	}
    
}
