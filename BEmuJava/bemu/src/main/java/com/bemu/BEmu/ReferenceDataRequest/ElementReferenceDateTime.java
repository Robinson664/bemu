package com.bemu.BEmu.ReferenceDataRequest;

import com.bemu.BEmu.Datetime;
import com.bemu.BEmu.Name;

public class ElementReferenceDateTime extends ElementParent
{
	private final Datetime _value;
	private final String _name;
	
	ElementReferenceDateTime(String name, Datetime value)
    {
        this._value = new Datetime(value);
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
    	return super.prettyPrintHelper(tabIndent, this._value.toString());
    }
    
    public Object getValue()
    {
    	return this._value;
    }

    public Datetime getValueAsDate()
    {
        return this._value;
    }

    public Datetime getValueAsDatetime()
    {
        return this._value;
    }

    public Datetime getValueAsTime()
    {
        return this._value;
    }
}
