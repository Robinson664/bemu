//------------------------------------------------------------------------------
// <copyright project="BEmu_maven" file="/BEmu_maven/bemu/src/main/java/com/bloomberglp/blpapi/IntradayTickElementDouble.java" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

package com.bloomberglp.blpapi;

import com.bloomberglp.blpapi.Name;
import com.bloomberglp.blpapi.Schema;

import java.lang.StringBuilder;

public class IntradayTickElementDouble extends Element
{
    private final double _value;
    private final String _name;
    private static final String VALUE_FORMAT = "%d";

    IntradayTickElementDouble(String name, double value)
    {
        this._name = name;
        this._value = value;
    }
    
    public Name name() throws Exception
    {
    	return new Name(this._name);
    }
    
    public int numValues()
    {
    	return 1;
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

    public Schema.Datatype datatype()
    {
    	return Schema.Datatype.FLOAT64;
    }
    
    public boolean hasElement(String name)
    {
    	return false;
    }
    
    public boolean hasElement(String name, boolean excludeNullElements)
    {
    	return false;
    }
    
    protected StringBuilder prettyPrint(int tabIndent) throws Exception
    {
    	return super.prettyPrintHelper(tabIndent, com.bloomberglp.blpapi.Formats.formatDouble2NoCommas(this._value));
    }
    
    public Object getValue()
    {
    	return this._value;
    }
    
    public Object getValue(int index) throws Exception
    {
    	if(index == 0)
    		return this.getValue();
    	else
    		return super.getValue();
    }
    
    public double getValueAsFloat64()
    {
        return this._value;
    }

    public double getValueAsFloat64(int index) throws Exception
    {
        if (index == 0)
            return this.getValueAsFloat64();
        else
            return super.getValueAsFloat64(index);
    }
    
    public int getValueAsInt32()
    {
        return (int)this._value;
    }

    public int getValueAsInt32(int index) throws Exception
    {
        if (index == 0)
            return this.getValueAsInt32();
        else
            return super.getValueAsInt32(index);
    }

    public long getValueAsInt64()
    {
        return (long)this._value;
    }

    public long getValueAsInt64(int index) throws Exception
    {
        if (index == 0)
            return this.getValueAsInt64();
        else
            return super.getValueAsInt64(index);
    }
    
    public String getValueAsString()
    {
        return String.format(IntradayTickElementDouble.VALUE_FORMAT, this._value);
    }

    public String getValueAsString(int i) throws Exception
    {
        if (i == 0)
            return this.getValueAsString();
        else
            return super.getValueAsString(i);
    }
}
