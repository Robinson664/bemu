package com.bemu.BEmu.ReferenceDataRequest;

import com.bemu.BEmu.Name;

public class ElementReferenceDouble extends ElementParent
{
	private final double _value;
	private final String _name;
	
	ElementReferenceDouble(String name, double value)
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
    
    public double getValueAsFloat64()
    {
    	return this._value;
    }
    
    public int getValueAsInt32()
    {
        return (int)this._value;
    }
    
    public long getValueAsInt64()
    {
        return (long)this._value;
    }
}
