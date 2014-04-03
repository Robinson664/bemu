//------------------------------------------------------------------------------
// <copyright project="BEmuJava" file="BEmu.IntradayBarRequest.RequestIntradayBarElementString.java" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

package com.bemu.BEmu.IntradayBarRequest;

import com.bemu.BEmu.Element;
import com.bemu.BEmu.Name;
import com.bemu.BEmu.Schema;

import java.lang.StringBuilder;

public class RequestIntradayBarElementString extends Element
{
    private final String _elementName, _value;

    public RequestIntradayBarElementString(String elementName, String value)
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
        String tabs = com.bemu.BEmu.types.IndentType.Indent(tabIndent);
        StringBuilder result = new StringBuilder();

        result.append(String.format("%s%s = %s%s", tabs, this._elementName, this._value, System.getProperty("line.separator")));

        return result;
    }

}
