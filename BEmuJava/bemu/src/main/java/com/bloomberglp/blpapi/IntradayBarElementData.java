//------------------------------------------------------------------------------
// <copyright project="BEmu_maven" file="/BEmu_maven/bemu/src/main/java/com/bloomberglp/blpapi/IntradayBarElementData.java" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

package com.bloomberglp.blpapi;

import java.util.List;
import com.bloomberglp.blpapi.Element;
import com.bloomberglp.blpapi.SchemaTypeDefinition;

import com.bloomberglp.blpapi.Name;

public class IntradayBarElementData extends Element
{
    private final IntradayBarElementTickDataArray _array;
    
    IntradayBarElementData(List<IntradayBarTickDataType> bars)
    {
        this._array = new IntradayBarElementTickDataArray(bars);
    }
    
    public SchemaTypeDefinition typeDefinition() throws Exception
    {
    	return new SchemaTypeDefinition(this.datatype(), new Name("BarData"));
    }
    
    public Name name() throws Exception
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
    	if(this._array.name().toString().equals(name))
    		return this._array;
    	else
    		return super.getElement(name);
    }
    
    protected StringBuilder prettyPrint(int tabIndent) throws Exception
    {
        String tabs = com.bloomberglp.blpapi.IndentType.Indent(tabIndent);
        StringBuilder result = new StringBuilder();

        result.append(String.format("%s%s = {%s", tabs, this.name(), System.getProperty("line.separator")));
        result.append(this._array.prettyPrint(tabIndent + 1));
        result.append(String.format("%s}%s", tabs, System.getProperty("line.separator")));

        return result;
    }
    
}
