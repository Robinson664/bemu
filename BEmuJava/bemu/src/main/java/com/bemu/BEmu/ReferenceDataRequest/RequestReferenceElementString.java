package com.bemu.BEmu.ReferenceDataRequest;

import com.bemu.BEmu.Name;

public class RequestReferenceElementString extends ElementParent
{
    private final String _elementName, _value;

    RequestReferenceElementString(String elementName, String value)
    {
        this._elementName = elementName;
        this._value = value;
    }
    
    public Name name()
    {
    	return new Name(this._elementName);
    }
    
    public int numValues()
    {
    	return 1;
    }
    
    public int numElements()
    {
    	return 0;
    }
    
    protected StringBuilder prettyPrint(int tabIndent)
    {
        String tabs = com.bemu.BEmu.types.IndentType.Indent(tabIndent);
        StringBuilder result = new StringBuilder();

        result.append(String.format("%s%s = %s%s", tabs, this._elementName, this._value, System.getProperty("line.separator")));

        return result;
    }
}
