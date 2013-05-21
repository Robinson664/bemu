//------------------------------------------------------------------------------
// <copyright project="BEmuJava" file="BEmu.IntradayTickRequest.RequestIntradayTickElementBool.java" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

package com.bemu.BEmu.IntradayTickRequest;

public class RequestIntradayTickElementBool extends RequestIntradayTickElementString
{
    private final boolean _value;

    RequestIntradayTickElementBool(String elementName, boolean value)
    {
    	super(elementName, String.valueOf(value).toLowerCase());
        this._value = value;
    }

    //I can't override GetElementAsBool here because the Bloomberg Request object stores bools as strings, not bools.  You can't convert the string to a bool
    boolean getBoolean()
    {
		return this._value; 
    } 
}
