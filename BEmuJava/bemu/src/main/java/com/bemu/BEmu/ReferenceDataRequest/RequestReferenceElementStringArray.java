package com.bemu.BEmu.ReferenceDataRequest;

import java.util.ArrayList;
import java.util.List;

import com.bemu.BEmu.Name;

public class RequestReferenceElementStringArray extends ElementParent
{
    private final String _elementName;
    private final List<String> _values;

    RequestReferenceElementStringArray(String elementName)
    {
        this._elementName = elementName;
        this._values = new ArrayList<String>();
    }
    
    public Name name()
    {
    	return new Name(this._elementName);
    }
    
    public int numValues()
    {
    	return this._values.size();
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
    	return true;
    }
    
    public boolean isNull()
    {
    	return false;
    }
    
    void addValue(String value)
    {
    	this._values.add(value);
    }
    
    List<String> values()
    {
    	return this._values;
    }
    
    protected StringBuilder prettyPrint(int tabIndent)
    {
        String tabs = com.bemu.BEmu.types.IndentType.Indent(tabIndent);
        StringBuilder result = new StringBuilder();

        result.append(String.format("%s%s[] = {%s", tabs, this._elementName, System.getProperty("line.separator")));

        StringBuilder secs = new StringBuilder();
        for(int i = 0; i < this._values.size(); i++)
        {
        	secs.append(this._values.get(i));
        	if(i < this._values.size() - 1)
        		secs.append(",");
        }
        result.append(String.format("%s%s%s%s", tabs, com.bemu.BEmu.types.IndentType.TAB, secs.toString(), System.getProperty("line.separator")));
        
        result.append(String.format("%s}%s", tabs, System.getProperty("line.separator")));

        return result;
    }
}
