//------------------------------------------------------------------------------
// <copyright project="BEmu_maven" file="/BEmu_maven/bemu/src/main/java/com/bloomberglp/blpapi/IntradayBarRequestElementInt.java" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

package com.bloomberglp.blpapi;

import com.bloomberglp.blpapi.Schema;

public class IntradayBarRequestElementInt extends IntradayBarRequestElementString
{
    private final int _value;

    IntradayBarRequestElementInt(String elementName, int value)
    {
    	super(elementName, String.valueOf(value));
        this._value = value;
    }

    //I can't override GetElementAsInt32 here because the Bloomberg Request object stores ints as strings, not ints.  You can't convert the string to an int
    protected int getInt()
    {
    	return this._value;
    }

    public Schema.Datatype datatype()
    {
    	return Schema.Datatype.INT32;
    }
}
