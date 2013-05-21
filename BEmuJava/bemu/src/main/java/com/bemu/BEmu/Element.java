//------------------------------------------------------------------------------
// <copyright project="BEmuJava" file="BEmu.Element.java" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

package com.bemu.BEmu;

import java.lang.StringBuilder;
import com.bemu.BEmu.Name;
import com.bemu.BEmu.types.IndentType;
import com.bemu.BEmu.Datetime;

public abstract class Element {
	protected abstract StringBuilder prettyPrint(int tabIndent);
	public abstract Name name();
	public abstract int numValues();
	public abstract int numElements();
	
	public String toString()
	{
		return this.prettyPrint(0).toString();
	}

    protected StringBuilder prettyPrintHelper(int tabIndent, String value)
    {
        String tabs = IndentType.Indent(tabIndent);
        StringBuilder result = new StringBuilder(String.format("%s%s = %s%s", 
        		tabs, this.name(), value, System.getProperty("line.separator")));
        return result;
    }

    public boolean isNull() throws Exception
    {
        throw new Exception("Element doesn't support IsNull");
    }

    public boolean isArray() throws Exception
    {
        throw new Exception("Element doesn't support IsArray");
    }

    public boolean isComplexType() throws Exception
    {
        throw new Exception("Element doesn't support IsComplexType");
    }

    public Object getValue() throws Exception { return this.GetValue(0); }
    public Object GetValue(int index) throws Exception
    {
        throw new Exception("Element is not a simple object (index)");
    }

    public String getElementAsString(Name name) throws Exception { return this.getElementAsString(name.toString()); }
    public String getElementAsString(String name) throws Exception
    {
        throw new Exception("Element doesn't support getting elements as strings");
    }

    public Datetime getElementAsTime(Name name) throws Exception { return this.getElementAsTime(name.toString()); }
    public Datetime getElementAsTime(String name) throws Exception
    {
        throw new Exception("Element doesn't support getting elements as Times");
    }

    public Datetime getElementAsDate(Name name) throws Exception { return this.getElementAsDate(name.toString()); }
    public Datetime getElementAsDate(String name) throws Exception
    {
        throw new Exception("Element doesn't support getting elements as Dates");
    }

    public Datetime getElementAsDatetime(Name name) throws Exception { return this.getElementAsDatetime(name.toString()); }
    public Datetime getElementAsDatetime(String name) throws Exception
    {
        throw new Exception("Element doesn't support getting elements as Datetimes");
    }

    public int getElementAsInt32(Name name) throws Exception { return this.getElementAsInt32(name.toString()); }
    public int getElementAsInt32(String name) throws Exception
    {
        throw new Exception("Element doesn't support getting elements as Int32");
    }

    public long getElementAsInt64(Name name) throws Exception { return this.getElementAsInt64(name.toString()); }
    public long getElementAsInt64(String name) throws Exception
    {
        throw new Exception("Element doesn't support getting elements as Int64");
    }

    public double getElementAsFloat64(Name name) throws Exception { return this.getElementAsFloat64(name.toString()); }
    public double getElementAsFloat64(String name) throws Exception
    {
        throw new Exception("Element doesn't support getting elements as Float64");
    }

    public boolean getElementAsBoolean(Name name) throws Exception { return this.getElementAsBool(name.toString()); }
    public boolean getElementAsBool(String name) throws Exception
    {
        throw new Exception("Element doesn't support getting elements as bool");
    }

    public float getElementAsFloat32(Name name) throws Exception { return this.getElementAsFloat32(name.toString()); }
    public float getElementAsFloat32(String name) throws Exception
    {
        throw new Exception("Element doesn't support getting elements as Float32");
    }

    public Element getValueAsElement() throws Exception { return this.getValueAsElement(0); }
    public Element getValueAsElement(int index) throws Exception
    {
        throw new Exception("Element doesn't support getting values as elements (index)");
    }

    public String getValueAsString(int i) throws Exception
    {
        throw new Exception("Element doesn't support getValueAsString by index");
    }

    public float getValueAsFloat32() throws Exception
    {
        throw new Exception("Element doesn't support getValueAsFloat32");
    }
    public float getValueAsFloat32(int index) throws Exception
    {
        throw new Exception("Element doesn't support getValueAsFloat32");
    }

    public double getValueAsFloat64() throws Exception
    {
        throw new Exception("Element doesn't support getValueAsFloat64");
    }

    public double getValueAsFloat64(int index) throws Exception
    {
        throw new Exception("Element doesn't support getValueAsFloat64");
    }

    public int getValueAsInt32() throws Exception
    {
        throw new Exception("Element doesn't support getValueAsInt32");
    }

    public int getValueAsInt32(int index) throws Exception
    {
        throw new Exception("Element doesn't support getValueAsInt32");
    }

    public long getValueAsInt64() throws Exception
    {
        throw new Exception("Element doesn't support getValueAsInt64");
    }

    public long getValueAsInt64(int index) throws Exception
    {
        throw new Exception("Element doesn't support getValueAsInt64");
    }

    public String getValueAsString() throws Exception
    {
        throw new Exception("Element doesn't support getValueAsString");
    }

    public Datetime getValueAsDatetime() throws Exception
    {
        throw new Exception("Element doesn't support getValueAsDatetime");
    }

    public Datetime getValueAsDatetime(int index) throws Exception
    {
        throw new Exception("Element doesn't support getValueAsDatetime");
    }

    public Datetime getValueAsDate() throws Exception
    {
        throw new Exception("Element doesn't support getValueAsDate");
    }

    public Datetime getValueAsDate(int index) throws Exception
    {
        throw new Exception("Element doesn't support getValueAsDate");
    }

    public Datetime getValueAsTime() throws Exception
    {
        throw new Exception("Element doesn't support getValueAsTime");
    }

    public Datetime getValueAsTime(int index) throws Exception
    {
        throw new Exception("Element doesn't support getValueAsTime");
    }
    

    public Element getElement(Name name) throws Exception
    {
        return this.getElement(name.toString());
    }

    public Element getElement(String name) throws Exception
    {
        throw new Exception("Element doesn't support getting elements by name");
    }

    public Element getElement(int index) throws Exception
    {
        throw new Exception("Element doesn't support getting elements by index");
    }

    public boolean hasElement(Name name) throws Exception
    {
        return this.hasElement(name.toString(), false);
    }

    public boolean hasElement(String name) throws Exception
    {
        throw new Exception("Element doesn't support HasElement");
    }

    public boolean hasElement(Name name, boolean excludeNullElements) throws Exception
    {
        return this.hasElement(name.toString(), excludeNullElements);
    }

    public boolean hasElement(String name, boolean excludeNullElements) throws Exception
    {
        throw new Exception("Element doesn't support HasElement");
    }

    public Element appendElement() throws Exception
    {
        throw new Exception("Element doesn't support AppendElement");
    }

    public void setElement(Name name, Object value) throws Exception
    {
        this.setElement(name.toString(), value);
    }

    public void setElement(String name, Object value) throws Exception
    {
        throw new Exception("Element doesn't support SetElement(Name name, string value)");
    }
}
