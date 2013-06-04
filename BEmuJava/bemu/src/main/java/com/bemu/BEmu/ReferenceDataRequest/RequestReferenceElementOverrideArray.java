package com.bemu.BEmu.ReferenceDataRequest;

import java.util.List;
import java.util.ArrayList;

import com.bemu.BEmu.Name;
import com.bemu.BEmu.Element;

public class RequestReferenceElementOverrideArray extends ElementParent
{
    private final List<RequestReferenceElementOverride> _overrides;

    RequestReferenceElementOverrideArray()
    {
        this._overrides = new ArrayList<RequestReferenceElementOverride>();
    }
    
    public Name name()
    {
    	return new Name("overrides");
    }
    
    public int numValues()
    {
    	return this._overrides.size();
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
    
    public Object getValue()
    {
    	return this.getValue(0);
    }
    
    public Object getValue(int index)
    {
    	return this._overrides.get(index);
    }

    public Element getValueAsElement() throws Exception
    {
        return this.getValueAsElement(0);
    }
    
    public Element getValueAsElement(int index)
    {
    	return (Element)this._overrides.get(index);
    }
    
    public Element appendElement()
    {
        RequestReferenceElementOverride result = new RequestReferenceElementOverride();
        this._overrides.add(result);
        return result;
    }
    
    protected StringBuilder prettyPrint(int tabIndent)
    {
        String tabs = com.bemu.BEmu.types.IndentType.Indent(tabIndent);
        StringBuilder result = new StringBuilder();

        result.append(String.format("%s%s[] = {%s", tabs, this.name().toString(), System.getProperty("line.separator")));
        
        for(int i = 0; i < this._overrides.size(); i++)
        {
        	result.append(this._overrides.get(i).prettyPrint(tabIndent + 1));
        }

        result.append(String.format("%s}%s", tabs, System.getProperty("line.separator")));
        return result;
    }
}
