package com.bemu.BEmu.ReferenceDataRequest;

import com.bemu.BEmu.Name;
import com.bemu.BEmu.Schema;

public class ElementReferenceString extends ElementParent
{
    private final String _name, _value;

    ElementReferenceString(String name, String value)
    {
        this._name = name;
        this._value = value;
    }
    
    public Name name() throws Exception
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
    
    protected StringBuilder prettyPrint(int tabIndent) throws Exception
    {
    	return super.prettyPrintHelper(tabIndent, this._value.toString());
    }
    
    public Object getValue()
    {
    	return this._value;
    }
    
    public String getValueAsString()
    {
    	return this._value;
    }
    
    public String getValueAsString(int index) throws Exception
    {
    	if(index == 0)
    		return this._value;
    	else
    		return super.getValueAsString(index);
    }
	
}
