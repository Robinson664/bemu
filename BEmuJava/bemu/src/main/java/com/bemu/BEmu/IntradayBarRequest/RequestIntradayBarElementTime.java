//------------------------------------------------------------------------------
// <copyright project="BEmuJava" file="BEmu.IntradayBarRequest.RequestIntradayBarElementTime.java" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

package com.bemu.BEmu.IntradayBarRequest;

import com.bemu.BEmu.Datetime;

public class RequestIntradayBarElementTime extends RequestIntradayBarElementString
{
    private final Datetime _instance;

    RequestIntradayBarElementTime(String elementName)
    {
    	super(elementName, "");
        this._instance = null;
    }

    RequestIntradayBarElementTime(String elementName, Datetime date)
    {
    	super(elementName, date.toString());
        this._instance = date;
    }

    //I can't override GetElementAsDatetime here because the Bloomberg Request object stores dates as strings, not Datetimes.  You can't convert the string to a Datetime
    protected Datetime getDate()
    {
    	return this._instance;
    }
}
