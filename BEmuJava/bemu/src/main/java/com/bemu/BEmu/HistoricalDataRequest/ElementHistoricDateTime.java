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

public class ElementHistoricDateTime extends ElementParent
{
	private final Datetime _date;
	
	ElementHistoricDateTime(Datetime date)
    {
        this._date = new Datetime(date);
    }
	
    public Name name()
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
    
    protected StringBuilder prettyPrint(int tabIndent)
    {
    	return super.prettyPrintHelper(tabIndent, this._date.toString());
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
        return this._date.toString();
    }
}
