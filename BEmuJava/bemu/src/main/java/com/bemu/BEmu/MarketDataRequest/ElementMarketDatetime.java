//------------------------------------------------------------------------------
// <copyright project="BEmuJava" file="BEmu.MarketDataRequest.ElementMarketDatetime.java" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

package com.bemu.BEmu.MarketDataRequest;

import com.bemu.BEmu.DateTimeTypeEnum;
import com.bemu.BEmu.Datetime;
import com.bemu.BEmu.Name;

public class ElementMarketDatetime extends ElementParent
{
	private final Datetime _date;
	private final String _name;
	
	ElementMarketDatetime(String name, Datetime date)
    {
        this._date = new Datetime(date, DateTimeTypeEnum.both);
        this._name = name;
    }
	
    public Name name()
    {
    	return new Name(this._name);
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

    public Datetime getValueAsDatetime()
    {
        return this._date;
    }

    public Datetime getValueAsDate() //note that this does not truncate the value to date-only, it still returns both the date and the time
    {
        return this._date;
    }

    public Datetime getValueAsTime() //note that this does not truncate the value to date-only, it still returns both the date and the time
    {
        return this._date;
    }

}
