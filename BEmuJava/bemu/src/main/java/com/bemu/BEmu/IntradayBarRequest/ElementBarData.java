//------------------------------------------------------------------------------
// <copyright project="BEmuJava" file="BEmu.IntradayBarRequest.ElementBarData.java" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

package com.bemu.BEmu.IntradayBarRequest;

import java.util.List;
import com.bemu.BEmu.Element;

import com.bemu.BEmu.Name;

public class ElementBarData extends Element
{
    private final ElementBarTickDataArray _array;
    
    ElementBarData(List<BarTickDataType> bars)
    {
        this._array = new ElementBarTickDataArray(bars);
    }
    
    public Name name()
    {
    	return new Name("barData");
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
    	if(this._array.name().toString().toLowerCase().equals(name.toLowerCase()))
    		return this._array;
    	else
    		return super.getElement(name);
    }
    
    protected StringBuilder prettyPrint(int tabIndent)
    {
        String tabs = com.bemu.BEmu.types.IndentType.Indent(tabIndent);
        StringBuilder result = new StringBuilder();

        result.append(String.format("%s%s = {%s", tabs, this.name(), System.getProperty("line.separator")));
        result.append(this._array.prettyPrint(tabIndent + 1));
        result.append(String.format("%s}%s", tabs, System.getProperty("line.separator")));

        return result;
    }
    
}
