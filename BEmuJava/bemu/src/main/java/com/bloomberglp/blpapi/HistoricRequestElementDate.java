//------------------------------------------------------------------------------
// <copyright project="BEmu_maven" file="/BEmu_maven/bemu/src/main/java/com/bloomberglp/blpapi/HistoricRequestElementDate.java" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

package com.bloomberglp.blpapi;

import com.bloomberglp.blpapi.Datetime;
import com.bloomberglp.blpapi.Schema;

public class HistoricRequestElementDate extends HistoricRequestElementString
{
    private final Datetime _instance;

    HistoricRequestElementDate(String elementName)
    {
    	super(elementName, "");
        this._instance = null;
    }

    HistoricRequestElementDate(String elementName, Datetime date)
    {
    	super(elementName, date.toString());
        this._instance = date;
    }

    //I can't override GetElementAsDatetime here because the Bloomberg Request object stores dates as strings, not Datetimes.  You can't convert the string to a Datetime
    Datetime getDate()
    {
    	return this._instance;
    }
    
    public Schema.Datatype datatype()
    {
    	return Schema.Datatype.DATE;
    }
}
