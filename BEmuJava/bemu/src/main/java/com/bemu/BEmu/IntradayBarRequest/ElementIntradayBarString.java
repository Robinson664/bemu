package com.bemu.BEmu.IntradayBarRequest;

import com.bemu.BEmu.Name;
import com.bemu.BEmu.Schema;
import com.bemu.BEmu.Element;

public class ElementIntradayBarString extends Element
{
    private final String _value;
    private final String _name;

    ElementIntradayBarString(String name, String value)
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
    
    public Schema.Datatype datatype()
    {
    	return Schema.Datatype.STRING;
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
