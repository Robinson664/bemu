//------------------------------------------------------------------------------
// <copyright project="BEmu_maven" file="/BEmu_maven/bemu/src/main/java/com/bloomberglp/blpapi/IntradayTickRequestElementBool.java" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

package com.bloomberglp.blpapi;

import com.bloomberglp.blpapi.Schema;

public class IntradayTickRequestElementBool extends IntradayTickRequestElementString
{
    private final boolean _value;

    IntradayTickRequestElementBool(String elementName, boolean value)
    {
    	super(elementName, String.valueOf(value));
        this._value = value;
    }

    //I can't override GetElementAsBool here because the Bloomberg Request object stores bools as strings, not bools.  You can't convert the string to a bool
    boolean getBoolean()
    {
		return this._value; 
    } 

    public Schema.Datatype datatype()
    {
    	return Schema.Datatype.BOOL;
    }
}
