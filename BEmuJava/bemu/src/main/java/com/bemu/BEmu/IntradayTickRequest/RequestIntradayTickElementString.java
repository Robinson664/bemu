//------------------------------------------------------------------------------
// <copyright project="BEmuJava" file="BEmu.IntradayTickRequest.RequestIntradayTickElementString.java" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

package com.bemu.BEmu.IntradayTickRequest;

import com.bemu.BEmu.Element;
import com.bemu.BEmu.Name;
import java.lang.StringBuilder;

public class RequestIntradayTickElementString extends Element
{
    private final String _elementName, _value;

    RequestIntradayTickElementString(String elementName, String value)
    {
        this._elementName = elementName;
        this._value = value;
    }
    
    public Name name()
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
    
    String security()
    {
    	return this._value;
    }
    
    protected StringBuilder prettyPrint(int tabIndent)
    {
        String tabs = com.bemu.BEmu.types.IndentType.Indent(tabIndent);
        StringBuilder result = new StringBuilder();

        result.append(String.format("%s%s = %s%s", tabs, this._elementName, this._value, System.getProperty("line.separator")));
        
        return result;
    }

}
