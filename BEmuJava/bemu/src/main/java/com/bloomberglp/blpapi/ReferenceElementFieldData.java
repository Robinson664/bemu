//------------------------------------------------------------------------------
// <copyright project="BEmu_maven" file="/BEmu_maven/bemu/src/main/java/com/bloomberglp/blpapi/ReferenceElementFieldData.java" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

package com.bloomberglp.blpapi;

import java.util.List;
import java.util.ArrayList;
import java.util.Map;

import com.bloomberglp.blpapi.Name;
import com.bloomberglp.blpapi.Element;
import com.bloomberglp.blpapi.Datetime;
import com.bloomberglp.blpapi.SchemaTypeDefinition;

public class ReferenceElementFieldData extends Element
{
    private final List<Element> _fields;

    ReferenceElementFieldData(Map<String, Object> values)
    {
        this._fields = new ArrayList<Element>();
        for(Map.Entry<String, Object> item : values.entrySet())
        {
        	String itemKey = item.getKey();
        	Object itemValue = item.getValue();
        	
        	if(itemValue instanceof Double)
        	{
        		Element elmDouble = new ReferenceElementDouble(itemKey, (Double)itemValue);
        		this._fields.add(elmDouble);
        	}
        	else if(itemValue instanceof Integer)
        	{
        		Element elmInt = new ReferenceElementInt(itemKey, (Integer)itemValue);
                this._fields.add(elmInt);
        	}
        	else if(itemValue instanceof Datetime)
        	{
        		Element elmDatetime = new ReferenceElementDateTime(itemKey, (Datetime)itemValue);
                this._fields.add(elmDatetime);
        	}
        	else if(itemValue instanceof String)
        	{
        		Element elmString = new ReferenceElementString(itemKey, (String)itemValue);
                this._fields.add(elmString);
        	}
        	else if(itemValue instanceof ReferenceElementArrayChainTickers)
                this._fields.add((ReferenceElementArrayChainTickers)itemValue);
        }
    }
    
    public SchemaTypeDefinition typeDefinition() throws Exception
    {
    	return new SchemaTypeDefinition(this.datatype(), new Name("ReferenceFieldData"));
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
    
    public Element getElement(int index)
    {
    	return this._fields.get(index);
    }
    
    public Element getElement(String name) throws Exception
    {
    	for(int i = 0; i < this._fields.size(); i++)
    	{
    		Element item = this._fields.get(i);
    		if(item.name().toString().equals(name))
    		{
    			return item;
    		}
    	}
    	return super.getElement(name);
    }
    
    protected StringBuilder prettyPrint(int tabIndent) throws Exception
    {
        String tabs = com.bloomberglp.blpapi.IndentType.Indent(tabIndent);
        StringBuilder result = new StringBuilder();

        result.append(String.format("%sfieldData[] = {%s", tabs, System.getProperty("line.separator")));
        
        for(int i = 0; i < this._fields.size(); i++)
        {
        	result.append(this._fields.get(i).prettyPrint(tabIndent + 1));
        }

        result.append(String.format("%s}%s", tabs, System.getProperty("line.separator")));
        return result;
    }
    
    public boolean hasElement(String name) throws Exception
    {
    	return this.hasElement(name, false);
    }
    
    public boolean hasElement(String name, boolean excludeNullElements) throws Exception
    {
    	for(int i = 0; i < this._fields.size(); i++)
    	{
    		if(this._fields.get(i).name().toString().equals(name))
    			return true;
    	}
    	return false;
    }
    
    public double getElementAsFloat64(String name) throws Exception
    {
    	return this.getElement(name).getValueAsFloat64();
    }
    
    public int getElementAsInt32(String name) throws Exception
    {
    	return this.getElement(name).getValueAsInt32();
    }
    
    public long getElementAsInt64(String name) throws Exception
    {
    	return this.getElement(name).getValueAsInt64();
    }
    
    public String getElementAsString(String name) throws Exception
    {
    	return this.getElement(name).getValueAsString();
    }
    
    
    
}
