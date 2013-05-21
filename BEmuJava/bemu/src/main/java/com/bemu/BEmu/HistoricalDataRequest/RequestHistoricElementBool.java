package com.bemu.BEmu.HistoricalDataRequest;

public class RequestHistoricElementBool extends RequestHistoricElementString
{
    private final boolean _value;
    
    RequestHistoricElementBool(String elementName, boolean value)
    {
    	super(elementName, String.valueOf(value).toLowerCase());
        this._value = value;
    }

    //I can't override GetElementAsInt32 here because the Bloomberg Request object stores ints as strings, not ints.  You can't convert the string to an int
    boolean getBoolean()
    {
    	return this._value;
    }

}
