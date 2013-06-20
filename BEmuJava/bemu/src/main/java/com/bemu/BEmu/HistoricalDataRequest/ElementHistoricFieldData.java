//------------------------------------------------------------------------------
// <copyright project="BEmuJava" file="BEmu.HistoricalDataRequest.ElementHistoricFieldData.java" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

package com.bemu.BEmu.HistoricalDataRequest;

import com.bemu.BEmu.Datetime;
import com.bemu.BEmu.Name;

import java.util.Map;
import java.util.HashMap;

public class ElementHistoricFieldData extends ElementParent
{
	private final Map<String, ElementParent> _fields;
	
	ElementHistoricFieldData(Datetime date, Map<String, Object> values)
	{
		this._fields = new HashMap<String, ElementParent>();
		
		ElementParent elmDate = new ElementHistoricDateTime(date);
		this._fields.put(elmDate.name().toString().toUpperCase(), elmDate);
		
		for (Map.Entry<String, Object> item : values.entrySet())
		{
			if(item.getValue().getClass() == Double.class)
			{
				ElementParent elmDouble = new ElementHistoricDouble(item.getKey().toUpperCase(), (Double)item.getValue());
                this._fields.put(elmDouble.name().toString(), elmDouble);
			}
		}
	}
	
    public Name name()
    {
    	return new Name("fieldData");
    }
    
    public int numValues()
    {
    	return 1;
    }
    
    public int numElements()
    {
    	return this._fields.size();
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
	
	public int getElementAsInt32(String name) throws Exception
	{
		return this._fields.get(name.toUpperCase()).getValueAsInt32();
	}
    
    public Datetime getElementAsDatetime(String name) throws Exception
    {
    	return this._fields.get(name.toUpperCase()).getValueAsDatetime();
    }
    
    public Datetime getElementAsDate(String name) throws Exception
    {
    	return this._fields.get(name.toUpperCase()).getValueAsDate();
    }
    
    public Datetime getElementAsTime(String name) throws Exception
    {
    	return this._fields.get(name.toUpperCase()).getValueAsTime();
    }
    
    public String getElementAsString(String name) throws Exception
    {
    	return this._fields.get(name.toUpperCase()).getValueAsString();
    }
	
	public float getElementAsFloat32(String name) throws Exception
	{
		return this._fields.get(name.toUpperCase()).getValueAsFloat32();
	}
	
	public double getElementAsFloat64(String name) throws Exception
	{
		return this._fields.get(name.toUpperCase()).getValueAsFloat64();
	}
	
	public long getElementAsInt64(String name) throws Exception
	{
		return this._fields.get(name.toUpperCase()).getValueAsInt64();
	}
	
	public boolean hasElement(String name)
	{
		return this._fields.containsKey(name);
	}
	
	public boolean hasElement(String name, boolean excludeNullElements)
	{
		return this._fields.containsKey(name);
	}
	
    protected StringBuilder prettyPrint(int tabIndent)
    {
        String tabs = com.bemu.BEmu.types.IndentType.Indent(tabIndent);
        StringBuilder result = new StringBuilder();

        result.append(String.format("%sfieldData = {%s", tabs, System.getProperty("line.separator")));
        
        for (Map.Entry<String, ElementParent> item : this._fields.entrySet())
        {
        	result.append(item.getValue().prettyPrint(tabIndent + 1));
        }

        result.append(String.format("%s}%s", tabs, System.getProperty("line.separator")));
        return result;
    }
	
}
