//------------------------------------------------------------------------------
// <copyright project="BEmu_maven" file="/BEmu_maven/bemu/src/main/java/com/bloomberglp/blpapi/IntradayTickElementData.java" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

package com.bloomberglp.blpapi;

import com.bloomberglp.blpapi.Element;
import com.bloomberglp.blpapi.Datetime;
import com.bloomberglp.blpapi.Name;
import com.bloomberglp.blpapi.SchemaTypeDefinition;

import java.lang.StringBuilder;
import java.util.Map;
import java.util.HashMap;

public class IntradayTickElementData extends Element
{
	private final Map<String, Element> _fields; //for getElement(String)
	private final Element[] _fieldsArr; //for getElement(int)
	
	IntradayTickElementData(Datetime datetime, String type, double value, int size, boolean includeConditionCodes) throws Exception
	{
		this._fields = new HashMap<String, Element>();
		
		if(includeConditionCodes)
			this._fieldsArr = new Element[5];
		else
			this._fieldsArr = new Element[4];

		Element elmTime = new IntradayTickElementDateTime(datetime);
		this._fields.put(elmTime.name().toString(), elmTime);
		this._fieldsArr[0] = elmTime;

        //TODO: This should actually be an enumeration, not a string
		Element elmType = new IntradayTickElementString("type", type);
        this._fields.put(elmType.name().toString(), elmType);
		this._fieldsArr[1] = elmType;

		Element elmValue = new IntradayTickElementDouble("value", value);
        this._fields.put(elmValue.name().toString(), elmValue);
		this._fieldsArr[2] = elmValue;

		Element elmSize = new IntradayTickElementInt("size", size);
        this._fields.put(elmSize.name().toString(), elmSize);
		this._fieldsArr[3] = elmSize;
		
        if (includeConditionCodes)
        {
        	Element elmConditionCodes = new IntradayTickElementString("conditionCodes", "R6,IS");
            this._fields.put(elmConditionCodes.name().toString(), elmConditionCodes);
    		this._fieldsArr[4] = elmConditionCodes;
        }
	}
    
    public SchemaTypeDefinition typeDefinition() throws Exception
    {
    	return new SchemaTypeDefinition(this.datatype(), new Name("IntradayTickData"));
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
    
    public Element getElement(int index) throws Exception
    {
    	if(index < this._fieldsArr.length)
    		return this._fieldsArr[index];
    	else
    		return super.getElement(index);
    }
    
    public Element getElement(String name) throws Exception
    {
    	if(this._fields.containsKey(name))
    		return this._fields.get(name);
    	else
    		return super.getElement(name);
    }
    
    public int getElementAsInt32(String name) throws Exception
    {
    	return this.getElement(name).getValueAsInt32();
    }
    
    public Datetime getElementAsDatetime(String name) throws Exception
    {
    	return this.getElement(name).getValueAsDatetime();
    }
    
    public Datetime getElementAsDate(String name) throws Exception
    {
    	return this.getElement(name).getValueAsDate();
    }
    
    public Datetime getElementAsTime(String name) throws Exception
    {
    	return this.getElement(name).getValueAsTime();
    }
    
    public String getElementAsString(String name) throws Exception
    {
    	return this.getElement(name).getValueAsString();
    }
    
    public float getElementAsFloat32(String name) throws Exception
    {
    	return this.getElement(name).getValueAsFloat32();
    }
    
    public double getElementAsFloat64(String name) throws Exception
    {
    	return this.getElement(name).getValueAsFloat64();
    }
    
    public long getElementAsInt64(String name) throws Exception
    {
    	return this.getElement(name).getValueAsInt64();
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

        result.append(String.format("%stickData = {%s", tabs, System.getProperty("line.separator")));
        for(int i = 0; i < this._fieldsArr.length; i++)
        {
        	result.append(this._fieldsArr[i].prettyPrint(tabIndent + 1));
        }
        result.append(String.format("%s}%s", tabs, System.getProperty("line.separator")));
        return result;
    }

}
