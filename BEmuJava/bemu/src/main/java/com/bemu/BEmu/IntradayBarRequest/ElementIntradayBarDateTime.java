//------------------------------------------------------------------------------
// <copyright project="BEmuJava" file="BEmu.IntradayBarRequest.ElementIntradayBarDateTime.java" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

package com.bemu.BEmu.IntradayBarRequest;

import com.bemu.BEmu.Element;
import com.bemu.BEmu.Name;
import com.bemu.BEmu.Datetime;
import java.text.SimpleDateFormat;
import java.lang.StringBuilder;

public class ElementIntradayBarDateTime extends Element
{
    private final Datetime _date;
    
    ElementIntradayBarDateTime(Datetime date)
    {
    	this._date = date;
    }
    
    public Name name()
    {
    	return new Name("time");
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
    
    public boolean hasElement(String name)
    {
    	return false;
    }
    
    public boolean hasElement(String name, boolean excludeNullElements)
    {
    	return false;
    }
    
    protected StringBuilder prettyPrint(int tabIndent)
    {
    	return super.prettyPrintHelper(tabIndent, this.getValueAsString());
    }
    
    public Object getValue()
    {
    	return this._date;
    }
    
    public Object getValue(int index) throws Exception
    {
    	if(index == 0)
    		return this.getValue();
    	else
    		return super.getValue();
    }
    
    public Datetime getValueAsDate()
    {
        return this._date;
    }

    public Datetime getValueAsDate(int index) throws Exception
    {
        if (index == 0)
            return this.getValueAsDate();
        else
            return super.getValueAsDate(index);
    }

    public Datetime getValueAsDatetime(int index) throws Exception
    {
        if (index == 0)
            return this.getValueAsDatetime();
        else
            return super.getValueAsDatetime(index);
    }

    public Datetime getValueAsDatetime()
    {
        return this._date;
    }

    public Datetime getValueAsTime()
    {
        return this._date;
    }

    public Datetime getValueAsTime(int i) throws Exception
    {
        if (i == 0)
            return this.getValueAsTime();
        else
            return super.getValueAsTime(i);
    }

    public String getValueAsString()
    {
    	SimpleDateFormat df = new SimpleDateFormat();
    	df.applyPattern("yyyy-MM-dd'T'HH:mm:ss.SSS");
    	String strDate = df.format(this._date.calendar().getTime());
    	return strDate;
    }

    public String getValueAsString(int i) throws Exception
    {
        if (i == 0)
            return this.getValueAsString();
        else
            return super.getValueAsString(i);
    }
}
