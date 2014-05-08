//------------------------------------------------------------------------------
// <copyright project="BEmu_maven" file="/BEmu_maven/bemu/src/main/java/com/bloomberglp/blpapi/IntradayBarElementTickData.java" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

package com.bloomberglp.blpapi;

import com.bloomberglp.blpapi.Datetime;
import com.bloomberglp.blpapi.Element;
import com.bloomberglp.blpapi.Name;
import com.bloomberglp.blpapi.SchemaTypeDefinition;

public class IntradayBarElementTickData extends Element
{	
    private final IntradayBarElementDateTime _time;
    private final IntradayBarElementDouble _open, _high, _low, _close, _value;
    private final IntradayBarElementLong _volume;
    private final IntradayBarElementInt _numEvents;
    
    IntradayBarElementTickData(IntradayBarTickDataType arg)
    {
        this._time = new IntradayBarElementDateTime(arg.getDtTime());
        this._open = new IntradayBarElementDouble("open", arg.getOpen());
        this._high = new IntradayBarElementDouble("high", arg.getHigh());
        this._low = new IntradayBarElementDouble("low", arg.getLow());
        this._close = new IntradayBarElementDouble("close", arg.getClose());
        this._volume = new IntradayBarElementLong("volume", arg.getVolume());
        this._numEvents = new IntradayBarElementInt("numEvents", arg.getNumEvents());
        this._value = new IntradayBarElementDouble("value", arg.getValue());
    }
    
    public SchemaTypeDefinition typeDefinition() throws Exception
    {
    	return new SchemaTypeDefinition(this.datatype(), new Name("IntradayBarTickData"));
    }
    
    public Name name() throws Exception
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
    	if(name.equals("time"))
    		return this._time;
    	else if(name.equals("open"))
    		return this._open;
    	else if(name.equals("high"))
    		return this._high;
    	else if(name.equals("low"))
    		return this._low;
    	else if(name.equals("close"))
    		return this._close;
    	else if(name.equals("volume"))
    		return this._volume;
    	else if(name.equals("numEvents"))
    		return this._numEvents;
    	else if(name.equals("value"))
    		return this._value;
    	else
    		return super.getElement(name);
    }
    
    public boolean hasElement(String name)
    {
    	return name.equals("time") ||
    			name.equals("open") ||
    			name.equals("high") ||
    			name.equals("low") ||
    			name.equals("close") ||
    			name.equals("volume") ||
    			name.equals("numEvents") ||
    			name.equals("value");
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
    
    protected StringBuilder prettyPrint(int tabIndent) throws Exception
    {
        String tabs = com.bloomberglp.blpapi.IndentType.Indent(tabIndent);
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
