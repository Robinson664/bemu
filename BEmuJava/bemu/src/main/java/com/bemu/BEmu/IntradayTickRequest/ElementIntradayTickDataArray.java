//------------------------------------------------------------------------------
// <copyright project="BEmuJava" file="BEmu.IntradayTickRequest.ElementIntradayTickDataArray.java" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

package com.bemu.BEmu.IntradayTickRequest;

import com.bemu.BEmu.Datetime;
import com.bemu.BEmu.Element;
import com.bemu.BEmu.Name;

import java.util.List;
import java.util.ArrayList;
import java.util.Map;
import java.util.Map.Entry;

public class ElementIntradayTickDataArray extends ElementParent
{
	private List<ElementIntradayTickData> _tickData;
	
	ElementIntradayTickDataArray(Map<Datetime, Tuple3<String, Double, Integer>> ticks, boolean includeConditionCodes)
	{
		this._tickData = new ArrayList<ElementIntradayTickData>();
		
		for(Entry<Datetime, Tuple3<String, Double, Integer>> h : ticks.entrySet())
		{
			Datetime dt = h.getKey();
			Tuple3<String, Double, Integer> tpl = h.getValue();
			String str = tpl.item1();
			Double dd = tpl.item2();
			Integer it = tpl.item3();
			
			ElementIntradayTickData elmFieldData = new ElementIntradayTickData(dt, str, dd, it, includeConditionCodes);
			this._tickData.add(elmFieldData);
		}
	}
	
	public Element getValueAsElement(int index)
	{
		return this._tickData.get(index);
	}

	public Name name()
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
	
	protected StringBuilder prettyPrint(int tabIndent)
	{
        String tabs = com.bemu.BEmu.types.IndentType.Indent(tabIndent);
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
