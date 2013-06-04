//------------------------------------------------------------------------------
// <copyright project="BEmuJava" file="BEmu.IntradayBarRequest.ElementBarTickData.java" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

package com.bemu.BEmu.IntradayBarRequest;

import com.bemu.BEmu.Datetime;
import com.bemu.BEmu.Element;
import com.bemu.BEmu.Name;

public class ElementBarTickData extends Element
{	
    private final ElementIntradayBarDateTime _time;
    private final ElementIntradayBarDouble _open, _high, _low, _close, _value;
    private final ElementIntradayBarLong _volume;
    private final ElementIntradayBarInt _numEvents;
    
    ElementBarTickData(BarTickDataType arg)
    {
        this._time = new ElementIntradayBarDateTime(arg.getDtTime());
        this._open = new ElementIntradayBarDouble("open", arg.getOpen());
        this._high = new ElementIntradayBarDouble("high", arg.getHigh());
        this._low = new ElementIntradayBarDouble("low", arg.getLow());
        this._close = new ElementIntradayBarDouble("close", arg.getClose());
        this._volume = new ElementIntradayBarLong("volume", arg.getVolume());
        this._numEvents = new ElementIntradayBarInt("numEvents", arg.getNumEvents());
        this._value = new ElementIntradayBarDouble("value", arg.getValue());
    }
    
    public Name name()
    {
    	return new Name("barTickData");
    }
    
    public int numValues()
    {
    	return 0;
    }
    
    public int numElements()
    {
    	return 8;
    }
    
    public boolean isComplexType()
    {
    	return true;
    }
    
    public boolean isArray()
    {
    	return false;
    }
    
    public boolean isNull()
    {
    	return false;
    }
    
    public Element getElement(int index) throws Exception
    {
    	switch(index)
    	{
    		case 0: return this._time;
    		case 1: return this._open;
    		case 2: return this._high;
    		case 3: return this._low;
    		case 4: return this._close;
    		case 5: return this._volume;
    		case 6: return this._numEvents;
    		case 7: return this._value;
    		default: return super.getElement(index);
    	}
    }
    
    public Element getElement(String name) throws Exception
    {
    	String lower = name.toLowerCase();
    	if(lower.equals("time"))
    		return this._time;
    	else if(lower.equals("open"))
    		return this._open;
    	else if(lower.equals("high"))
    		return this._high;
    	else if(lower.equals("low"))
    		return this._low;
    	else if(lower.equals("close"))
    		return this._close;
    	else if(lower.equals("volume"))
    		return this._volume;
    	else if(lower.equals("numevents"))
    		return this._numEvents;
    	else if(lower.equals("value"))
    		return this._value;
    	else
    		return super.getElement(name);
    }
    
    public boolean hasElement(String name)
    {
    	String lower = name.toLowerCase();
    	return lower.equals("time") ||
    			lower.equals("open") ||
    			lower.equals("high") ||
    			lower.equals("low") ||
    			lower.equals("close") ||
    			lower.equals("volume") ||
    			lower.equals("numevents") ||
    			lower.equals("value");
    }
    
    public boolean hasElement(String name, boolean excludeNullElements)
    {
    	return this.hasElement(name);
    }
    
    public int getElementAsInt32(String name) throws Exception
    {
    	return this.getElement(name).getValueAsInt32();
    }

    public Datetime getElementAsDatetime(String name) throws Exception
    {
    	return this.getElement(name).getValueAsDatetime();
    }

    public Datetime getElementAsDate(String name) throws Exception
    {
    	return this.getElement(name).getValueAsDate();
    }

    public Datetime getElementAsTime(String name) throws Exception
    {
    	return this.getElement(name).getValueAsTime();
    }
    
    public double getElementAsFloat64(String name) throws Exception
    {
    	return this.getElement(name).getValueAsFloat64();
    }
    
    public long getElementAsInt64(String name) throws Exception
    {
    	return this.getElement(name).getValueAsInt64();
    }
    
    protected StringBuilder prettyPrint(int tabIndent)
    {
        String tabs = com.bemu.BEmu.types.IndentType.Indent(tabIndent);
        StringBuilder result = new StringBuilder();
        
        result.append(String.format("%s%s = {%s", tabs, this.name(), System.getProperty("line.separator")));

        result.append(this._time.prettyPrint(tabIndent + 1));
        result.append(this._open.prettyPrint(tabIndent + 1));
        result.append(this._high.prettyPrint(tabIndent + 1));
        result.append(this._low.prettyPrint(tabIndent + 1));
        result.append(this._close.prettyPrint(tabIndent + 1));
        result.append(this._volume.prettyPrint(tabIndent + 1));
        result.append(this._numEvents.prettyPrint(tabIndent + 1));
        result.append(this._value.prettyPrint(tabIndent + 1));

        result.append(String.format("%s}%s", tabs, System.getProperty("line.separator")));

        return result;
    }
}
