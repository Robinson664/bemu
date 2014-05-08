//------------------------------------------------------------------------------
// <copyright project="BEmu_maven" file="/BEmu_maven/bemu/src/main/java/com/bloomberglp/blpapi/IntradayTickElementDataParent.java" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

package com.bloomberglp.blpapi;

import java.util.Map;
import java.lang.StringBuilder;

import com.bloomberglp.blpapi.Element;
import com.bloomberglp.blpapi.Name;
import com.bloomberglp.blpapi.Datetime;
import com.bloomberglp.blpapi.SchemaTypeDefinition;

public class IntradayTickElementDataParent extends Element
{
    private final IntradayTickElementDataArray _array;
    
    IntradayTickElementDataParent(Map<Datetime, Tuple3<String, Double, Integer>> ticks, boolean includeConditionCodes) throws Exception
    {
        this._array = new IntradayTickElementDataArray(ticks, includeConditionCodes);
    }
    
    public SchemaTypeDefinition typeDefinition() throws Exception
    {
    	return new SchemaTypeDefinition(this.datatype(), new Name("TickData"));
    }
    
	public Name name() throws Exception
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
    	if(this._array.name().toString().equals(name))
    		return this._array;
    	else
    		return super.getElement(name);
    }
    
	protected StringBuilder prettyPrint(int tabIndent) throws Exception
	{
        String tabs = com.bloomberglp.blpapi.IndentType.Indent(tabIndent);
        StringBuilder result = new StringBuilder();

        result.append(String.format("%s%s = {%s", tabs, this.name().toString(), System.getProperty("line.separator")));
    	result.append(this._array.prettyPrint(tabIndent + 1));
        result.append(String.format("%s}%s", tabs, System.getProperty("line.separator")));
        
        return result;
	}
    
}
