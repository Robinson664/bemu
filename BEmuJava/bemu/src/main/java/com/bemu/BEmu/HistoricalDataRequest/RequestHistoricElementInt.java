package com.bemu.BEmu.HistoricalDataRequest;

public class RequestHistoricElementInt extends RequestHistoricElementString
{
    private final int _value;

    RequestHistoricElementInt(String elementName, int value)
    {
    	super(elementName, String.valueOf(value).toLowerCase());
        this._value = value;
    }

    //I can't override GetElementAsInt32 here because the Bloomberg Request object stores ints as strings, not ints.  You can't convert the string to an int
    int getInt()
    {
		return this._value; 
    } 
}
