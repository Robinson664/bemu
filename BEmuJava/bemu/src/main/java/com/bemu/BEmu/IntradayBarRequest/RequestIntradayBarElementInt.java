//------------------------------------------------------------------------------
// <copyright project="BEmuJava" file="BEmu.IntradayBarRequest.RequestIntradayBarElementInt.java" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

package com.bemu.BEmu.IntradayBarRequest;

public class RequestIntradayBarElementInt extends RequestIntradayBarElementString
{
    private final int _value;

    RequestIntradayBarElementInt(String elementName, int value)
    {
    	super(elementName, String.valueOf(value));
        this._value = value;
    }

    //I can't override GetElementAsInt32 here because the Bloomberg Request object stores ints as strings, not ints.  You can't convert the string to an int
    protected int getInt()
    {
    	return this._value;
    }
}
