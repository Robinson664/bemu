//------------------------------------------------------------------------------
// <copyright project="BEmu_maven" file="/BEmu_maven/bemu/src/main/java/com/bloomberglp/blpapi/IntradayTickElementDataArray.java" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

package com.bloomberglp.blpapi;

import com.bloomberglp.blpapi.Datetime;
import com.bloomberglp.blpapi.Element;
import com.bloomberglp.blpapi.Name;
import com.bloomberglp.blpapi.SchemaTypeDefinition;

import java.util.List;
import java.util.ArrayList;
import java.util.Map;
import java.util.Map.Entry;

public class IntradayTickElementDataArray extends Element
{
	private List<IntradayTickElementData> _tickData;
	
	IntradayTickElementDataArray(Map<Datetime, Tuple3<String, Double, Integer>> ticks, boolean includeConditionCodes) throws Exception
	{
		this._tickData = new ArrayList<IntradayTickElementData>();
		
		for(Entry<Datetime, Tuple3<String, Double, Integer>> h : ticks.entrySet())
		{
			Datetime dt = h.getKey();
			Tuple3<String, Double, Integer> tpl = h.getValue();
			String str = tpl.item1();
			Double dd = tpl.item2();
			Integer it = tpl.item3();
			
			IntradayTickElementData elmFieldData = new IntradayTickElementData(dt, str, dd, it, includeConditionCodes);
			this._tickData.add(elmFieldData);
		}
	}
    
    public SchemaTypeDefinition typeDefinition() throws Exception
    {
    	return new SchemaTypeDefinition(this.datatype(), new Name("IntradayTickData"));
    }
	
	public Element getValueAsElement(int index)
	{
		return this._tickData.get(index);
	}

	public Name name() throws Exception
	{
		return new Name("tickData");
	}

	public int numValues()
	{
		return this._tickData.size();
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
    
    public Object getValue(int index)
    {
    	return this._tickData.get(index);
    }
	
	protected StringBuilder prettyPrint(int tabIndent) throws Exception
	{
        String tabs = com.bloomberglp.blpapi.IndentType.Indent(tabIndent);
        StringBuilder result = new StringBuilder();

		result.append(String.format("%s%s[] = {%s", tabs, this.name().toString(), System.getProperty("line.separator")));        
        for(int i = 0; i < this._tickData.size(); i++)
        {
        	result.append(this._tickData.get(i).prettyPrint(tabIndent + 1));
        }
        result.append(String.format("%s}%s", tabs, System.getProperty("line.separator")));
        return result;
	}
    
    
}
