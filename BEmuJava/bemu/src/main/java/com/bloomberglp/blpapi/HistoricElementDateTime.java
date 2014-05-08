//------------------------------------------------------------------------------
// <copyright project="BEmu_maven" file="/BEmu_maven/bemu/src/main/java/com/bloomberglp/blpapi/HistoricElementDateTime.java" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

package com.bloomberglp.blpapi;

import com.bloomberglp.blpapi.Datetime;
import com.bloomberglp.blpapi.Name;
import com.bloomberglp.blpapi.Schema;

public class HistoricElementDateTime extends Element
{
	private final Datetime _date;
	
	HistoricElementDateTime(Datetime date)
    {
        this._date = new Datetime(date);
    }
	
    public Name name() throws Exception
    {
    	return new Name("date");
    }
    
    public int numValues()
    {
    	return 1;
    }
    
    public int numElements()
    {
    	return 0;
    }
    
    public boolean isComplexType()
    {
    	return false;
    }
    
    public boolean isArray()
    {
    	return false;
    }
    
    public boolean isNull()
    {
    	return false;
    }
    
    public Schema.Datatype datatype()
    {
    	return Schema.Datatype.DATE;
    }
    
    protected StringBuilder prettyPrint(int tabIndent) throws Exception
    {
    	String strDate = com.bloomberglp.blpapi.DisplayFormats.HistRef_FormatDate(this._date);
    	return super.prettyPrintHelper(tabIndent, strDate);
    }
    
    public Object getValue()
    {
    	return this._date;
    }

    public Datetime getValueAsDate()
    {
        return this._date;
    }

    public Datetime getValueAsDatetime()
    {
        return this._date;
    }

    public Datetime getValueAsTime()
    {
        return this._date;
    }

    public String getValueAsString()
    {
    	String strDate = com.bloomberglp.blpapi.DisplayFormats.HistRef_FormatDate(this._date);
        return strDate;
    }
}
