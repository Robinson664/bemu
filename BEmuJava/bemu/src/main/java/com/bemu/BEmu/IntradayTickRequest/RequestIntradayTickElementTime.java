//------------------------------------------------------------------------------
// <copyright project="BEmuJava" file="BEmu.IntradayTickRequest.RequestIntradayTickElementTime.java" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

package com.bemu.BEmu.IntradayTickRequest;

import com.bemu.BEmu.Datetime;

public class RequestIntradayTickElementTime extends RequestIntradayTickElementString
{
    private final Datetime _instance;

    RequestIntradayTickElementTime(String elementName)
    {
    	super(elementName, "");
        this._instance = null;
    }

    RequestIntradayTickElementTime(String elementName, Datetime date)
    {
    	super(elementName, date.toString());
        this._instance = date;
    }

    //I can't override GetElementAsDatetime here because the Bloomberg Request object stores dates as strings, not Datetimes.  You can't convert the string to a Datetime
    Datetime getDate()
    {
    	return this._instance;
    }
}
