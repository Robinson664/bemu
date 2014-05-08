//------------------------------------------------------------------------------
// <copyright project="BEmu_maven" file="/BEmu_maven/bemu/src/main/java/com/bloomberglp/blpapi/HistoricElementFieldData.java" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

package com.bloomberglp.blpapi;

import com.bloomberglp.blpapi.Datetime;
import com.bloomberglp.blpapi.Name;
import com.bloomberglp.blpapi.SchemaTypeDefinition;

import java.util.Map;
import java.util.HashMap;

public class HistoricElementFieldData extends Element
{
	private final Map<String, Element> _fields;
	
	HistoricElementFieldData(Datetime date, Map<String, Object> values) throws Exception
	{
		this._fields = new HashMap<String, Element>();
		
		Element elmDate = new HistoricElementDateTime(date);
		this._fields.put(elmDate.name().toString(), elmDate);
		
		for (Map.Entry<String, Object> item : values.entrySet())
		{
			if(item.getValue().getClass() == Double.class)
			{
				Element elmDouble = new HistoricElementDouble(item.getKey(), (Double)item.getValue());
                this._fields.put(elmDouble.name().toString(), elmDouble);
			}
		}
	}
    
    public SchemaTypeDefinition typeDefinition() throws Exception
    {
    	return new SchemaTypeDefinition(this.datatype(), new Name("HistoricalDataRow"));
    }
	
    public Name name() throws Exception
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
		return this._fields.get(name).getValueAsInt32();
	}
    
    public Datetime getElementAsDatetime(String name) throws Exception
    {
    	return this._fields.get(name).getValueAsDatetime();
    }
    
    public Datetime getElementAsDate(String name) throws Exception
    {
    	return this._fields.get(name).getValueAsDate();
    }
    
    public Datetime getElementAsTime(String name) throws Exception
    {
    	return this._fields.get(name).getValueAsTime();
    }
    
    public String getElementAsString(String name) throws Exception
    {
    	return this._fields.get(name).getValueAsString();
    }
	
	public float getElementAsFloat32(String name) throws Exception
	{
		return this._fields.get(name).getValueAsFloat32();
	}
	
	public double getElementAsFloat64(String name) throws Exception
	{
		return this._fields.get(name).getValueAsFloat64();
	}
	
	public long getElementAsInt64(String name) throws Exception
	{
		return this._fields.get(name).getValueAsInt64();
	}
	
	public boolean hasElement(String name)
	{
		return this._fields.containsKey(name);
	}
	
	public boolean hasElement(String name, boolean excludeNullElements)
	{
		return this._fields.containsKey(name);
	}
	
    protected StringBuilder prettyPrint(int tabIndent) throws Exception
    {
        String tabs = com.bloomberglp.blpapi.IndentType.Indent(tabIndent);
        StringBuilder result = new StringBuilder();

        result.append(String.format("%sfieldData = {%s", tabs, System.getProperty("line.separator")));
        
        for (Map.Entry<String, Element> item : this._fields.entrySet())
        {
        	result.append(item.getValue().prettyPrint(tabIndent + 1));
        }

        result.append(String.format("%s}%s", tabs, System.getProperty("line.separator")));
        return result;
    }
	
}
