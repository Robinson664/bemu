package com.bemu.BEmu.ReferenceDataRequest;

import com.bemu.BEmu.Name;
import com.bemu.BEmu.Schema;

public class ElementReferenceInt extends ElementParent
{
	private final int _value;
	private final String _name;
	
	ElementReferenceInt(String name, int value)
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
    	return Schema.Datatype.INT32;
    }
    
    protected StringBuilder prettyPrint(int tabIndent)
    {
    	return super.prettyPrintHelper(tabIndent, String.valueOf(this._value));
    }
    
    public Object getValue()
    {
    	return this._value;
    }
    
    public int getValueAsInt32()
    {
        return this._value;
    }
    
    public long getValueAsInt64()
    {
        return this._value;
    }

}
