//------------------------------------------------------------------------------
// <copyright project="BEmu_maven" file="/BEmu_maven/bemu/src/main/java/com/bloomberglp/blpapi/IntradayBarRequestElementString.java" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

package com.bloomberglp.blpapi;

import com.bloomberglp.blpapi.Element;
import com.bloomberglp.blpapi.Name;
import com.bloomberglp.blpapi.Schema;

import java.lang.StringBuilder;

public class IntradayBarRequestElementString extends Element
{
    private final String _elementName, _value;

    public IntradayBarRequestElementString(String elementName, String value)
    {
        this._elementName = elementName;
        this._value = value;
    }
    
    public Name name() throws Exception
    {
    	return new Name(this._elementName);
    }
    
    public int numValues()
    {
    	return 1;
    }
    
    public int numElements()
    {
    	return 0;
    }

    public Schema.Datatype datatype()
    {
    	return Schema.Datatype.STRING;
    }
    
    protected String getSecurity()
    {
    	return this._value;
    }
    
    public Object getValue()
    {
        return this._value;
    }
    
    public String getValueAsString()
    {
        return this._value;
    }
    
    public String getValueAsString(int index) throws Exception
    {
        if (index == 0)
            return this._value;
        else
            return super.getValueAsString(index);
    }
    
    protected StringBuilder prettyPrint(int tabIndent)
    {
        String tabs = com.bloomberglp.blpapi.IndentType.Indent(tabIndent);
        StringBuilder result = new StringBuilder();

        result.append(String.format("%s%s = %s%s", tabs, this._elementName, this._value, System.getProperty("line.separator")));

        return result;
    }

}
