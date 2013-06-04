package com.bemu.BEmu.ReferenceDataRequest;

import com.bemu.BEmu.Name;

public class ElementReferenceObject extends ElementParent
{
	private final Object _value;
	private final String _name;
	
	ElementReferenceObject(String name, Object value)
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
    	return String.valueOf(this._value);
    }

    public String getValueAsString(int index) throws Exception
    {
        if (index == 0)
            return this.getValueAsString();
        else
            return super.getValueAsString(index);
    }

}
