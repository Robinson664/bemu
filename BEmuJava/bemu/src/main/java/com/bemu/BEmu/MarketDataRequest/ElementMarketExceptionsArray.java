package com.bemu.BEmu.MarketDataRequest;

import java.util.List;
import java.util.ArrayList;
import com.bemu.BEmu.Element;
import com.bemu.BEmu.Name;

public class ElementMarketExceptionsArray extends ElementParent
{
    private final List<ElementMarketExceptions> _exceptions;

    public ElementMarketExceptionsArray(List<String> badFields)
    {
        this._exceptions = new ArrayList<ElementMarketExceptions>();
        
        for(int i = 0; i < badFields.size(); i++)
        {
        	String item = badFields.get(i);
        	this._exceptions.add(new ElementMarketExceptions(item));
        }
    }
	
	public Element getValueAsElement(int index)
	{
		return this._exceptions.get(index);
	}
	
    public Name name()
    {
    	return new Name("exceptions");
    }
    
    public int numValues()
    {
    	return this._exceptions.size();
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
	
    public Object getValue(int index)
    {
    	return this._exceptions.get(index);
    }
    
    protected StringBuilder prettyPrint(int tabIndent)
    {
        String tabs = com.bemu.BEmu.types.IndentType.Indent(tabIndent);
        StringBuilder result = new StringBuilder();

        result.append(String.format("%s%s[] = {%s", tabs, this.name().toString(), System.getProperty("line.separator")));
        
        for(int i = 0; i < this._exceptions.size(); i++)
        {
        	result.append(this._exceptions.get(i).prettyPrint(tabIndent + 1));
        }

        result.append(String.format("%s}%s", tabs, System.getProperty("line.separator")));
        return result;
    }
	
	
}
