//------------------------------------------------------------------------------
// <copyright project="BEmuJava" file="BEmu.HistoricalDataRequest.ElementHistoricDateTime.java" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

package com.bemu.BEmu.HistoricalDataRequest;

import com.bemu.BEmu.Datetime;
import com.bemu.BEmu.Name;
import com.bemu.BEmu.Schema;

public class ElementHistoricDateTime extends ElementParent
{
	private final Datetime _date;
	
	ElementHistoricDateTime(Datetime date)
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
    	String strDate = com.bemu.BEmu.types.DisplayFormats.HistRef_FormatDate(this._date);
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
    	String strDate = com.bemu.BEmu.types.DisplayFormats.HistRef_FormatDate(this._date);
        return strDate;
    }
}
