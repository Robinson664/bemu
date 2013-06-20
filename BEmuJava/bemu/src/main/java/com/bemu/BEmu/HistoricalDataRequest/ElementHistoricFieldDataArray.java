//------------------------------------------------------------------------------
// <copyright project="BEmuJava" file="BEmu.HistoricalDataRequest.ElementHistoricFieldDataArray.java" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

package com.bemu.BEmu.HistoricalDataRequest;

import java.util.List;
import java.util.ArrayList;
import java.util.Map;
import com.bemu.BEmu.Datetime;
import com.bemu.BEmu.Name;
import com.bemu.BEmu.Element;

public class ElementHistoricFieldDataArray extends ElementParent
{
	private final List<ElementHistoricFieldData> _fieldData;
	
	ElementHistoricFieldDataArray(Map<Datetime, Map<String, Object>> fieldData)
	{
		this._fieldData = new ArrayList<ElementHistoricFieldData>();
		
		for (Map.Entry<Datetime, Map<String, Object>> item : fieldData.entrySet())
		{
			ElementHistoricFieldData elmFieldData = new ElementHistoricFieldData(item.getKey(), item.getValue());
			this._fieldData.add(elmFieldData);
		}
	}
	
	public Element getValueAsElement(int index)
	{
		return this._fieldData.get(index);
	}
	
    public Name name()
    {
    	return new Name("fieldData");
    }
    
    public int numValues()
    {
    	return this._fieldData.size();
    }
    
    public int numElements()
    {
    	return 0;
    }
    
    public boolean isComplexType()
    {
    	return true;
    }
    
    public boolean isArray()
    {
    	return true;
    }
    
    public boolean isNull()
    {
    	return false;
    }
    
    protected StringBuilder prettyPrint(int tabIndent)
    {
        String tabs = com.bemu.BEmu.types.IndentType.Indent(tabIndent);
        StringBuilder result = new StringBuilder();

        result.append(String.format("%s%s[] = {%s", tabs, this.name().toString(), System.getProperty("line.separator")));
        
        for(int i = 0; i < this._fieldData.size(); i++)
        {
        	result.append(this._fieldData.get(i).prettyPrint(tabIndent + 1));
        }

        result.append(String.format("%s}%s", tabs, System.getProperty("line.separator")));
        return result;
    }
}
