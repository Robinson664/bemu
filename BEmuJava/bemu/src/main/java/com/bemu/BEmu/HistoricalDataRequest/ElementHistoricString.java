package com.bemu.BEmu.HistoricalDataRequest;

import com.bemu.BEmu.Name;

public class ElementHistoricString extends ElementParent
{
	private final String _value;
	private final String _name;
	
	ElementHistoricString(String name, String value)
    {
        this._name = name;
        this._value = value;
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
    	return super.prettyPrintHelper(tabIndent, String.valueOf(this._value));
    }
    
    public Object getValue()
    {
    	return this._value;
    }
    
    public String getValueAsString()
    {
    	return this._value;
    }
}
