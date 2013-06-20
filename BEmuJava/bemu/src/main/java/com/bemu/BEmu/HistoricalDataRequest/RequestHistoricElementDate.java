//------------------------------------------------------------------------------
// <copyright project="BEmuJava" file="BEmu.HistoricalDataRequest.RequestHistoricElementDate.java" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

package com.bemu.BEmu.HistoricalDataRequest;

import com.bemu.BEmu.Datetime;

public class RequestHistoricElementDate extends RequestHistoricElementString
{
    private final Datetime _instance;

    RequestHistoricElementDate(String elementName)
    {
    	super(elementName, "");
        this._instance = null;
    }

    RequestHistoricElementDate(String elementName, Datetime date)
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
