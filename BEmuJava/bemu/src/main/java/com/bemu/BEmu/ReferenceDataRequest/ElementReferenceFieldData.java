//------------------------------------------------------------------------------
// <copyright project="BEmuJava" file="BEmu.ReferenceDataRequest.ElementReferenceFieldData.java" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

package com.bemu.BEmu.ReferenceDataRequest;

import java.util.List;
import java.util.ArrayList;
import java.util.Map;

import com.bemu.BEmu.Name;
import com.bemu.BEmu.Element;
import com.bemu.BEmu.Datetime;
import com.bemu.BEmu.SchemaTypeDefinition;

public class ElementReferenceFieldData extends ElementParent
{
    private final List<ElementParent> _fields;

    ElementReferenceFieldData(Map<String, Object> values)
    {
        this._fields = new ArrayList<ElementParent>();
        for(Map.Entry<String, Object> item : values.entrySet())
        {
        	String itemKey = item.getKey();
        	Object itemValue = item.getValue();
        	
        	if(itemValue instanceof Double)
        	{
        		ElementParent elmDouble = new ElementReferenceDouble(itemKey, (Double)itemValue);
        		this._fields.add(elmDouble);
        	}
        	else if(itemValue instanceof Integer)
        	{
        		ElementParent elmInt = new ElementReferenceInt(itemKey, (Integer)itemValue);
                this._fields.add(elmInt);
        	}
        	else if(itemValue instanceof Datetime)
        	{
        		ElementParent elmDatetime = new ElementReferenceDateTime(itemKey, (Datetime)itemValue);
                this._fields.add(elmDatetime);
        	}
        	else if(itemValue instanceof String)
        	{
        		ElementParent elmString = new ElementReferenceString(itemKey, (String)itemValue);
                this._fields.add(elmString);
        	}
        	else if(itemValue instanceof ElementReferenceArrayChainTickers)
                this._fields.add((ElementReferenceArrayChainTickers)itemValue);
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
        String tabs = com.bemu.BEmu.types.IndentType.Indent(tabIndent);
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
