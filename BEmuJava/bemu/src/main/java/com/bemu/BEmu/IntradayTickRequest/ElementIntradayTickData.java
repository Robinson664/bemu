//------------------------------------------------------------------------------
// <copyright project="BEmuJava" file="BEmu.IntradayTickRequest.ElementIntradayTickData.java" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

package com.bemu.BEmu.IntradayTickRequest;

import com.bemu.BEmu.Element;
import com.bemu.BEmu.Datetime;
import com.bemu.BEmu.Name;

import java.lang.StringBuilder;
import java.util.Map;
import java.util.HashMap;

public class ElementIntradayTickData extends ElementParent
{
	private final Map<String, ElementParent> _fields; //for getElement(String)
	private final ElementParent[] _fieldsArr; //for getElement(int)
	
	ElementIntradayTickData(Datetime datetime, String type, double value, int size, boolean includeConditionCodes)
	{
		this._fields = new HashMap<String, ElementParent>();
		
		if(includeConditionCodes)
			this._fieldsArr = new ElementParent[5];
		else
			this._fieldsArr = new ElementParent[4];

		ElementParent elmTime = new ElementIntradayTickDateTime(datetime);
		this._fields.put(elmTime.name().toString().toUpperCase(), elmTime);
		this._fieldsArr[0] = elmTime;

        //TODO: This should actually be an enumeration, not a string
		ElementParent elmType = new ElementIntradayTickString("type", type);
        this._fields.put(elmType.name().toString().toUpperCase(), elmType);
		this._fieldsArr[1] = elmType;

		ElementParent elmValue = new ElementIntradayTickDouble("value", value);
        this._fields.put(elmValue.name().toString().toUpperCase(), elmValue);
		this._fieldsArr[2] = elmValue;

		ElementParent elmSize = new ElementIntradayTickInt("size", size);
        this._fields.put(elmSize.name().toString().toUpperCase(), elmSize);
		this._fieldsArr[3] = elmSize;
		
        if (includeConditionCodes)
        {
        	ElementParent elmConditionCodes = new ElementIntradayTickString("conditionCodes", "R6,IS");
            this._fields.put(elmConditionCodes.name().toString().toUpperCase(), elmConditionCodes);
    		this._fieldsArr[4] = elmConditionCodes;
        }
	}
	
    public Name name()
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
    	String key = name.toUpperCase();
    	if(this._fields.containsKey(key))
    		return this._fields.get(key);
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
    	return this._fields.containsKey(name.toUpperCase());
    }
    
    public boolean hasElement(String name, boolean excludeNullElements)
    {
    	return this._fields.containsKey(name.toUpperCase());
    }
    
    protected StringBuilder prettyPrint(int tabIndent)
    {
        String tabs = com.bemu.BEmu.types.IndentType.Indent(tabIndent);
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
