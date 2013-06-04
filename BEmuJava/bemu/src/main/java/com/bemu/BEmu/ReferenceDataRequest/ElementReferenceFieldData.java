package com.bemu.BEmu.ReferenceDataRequest;

import java.util.List;
import java.util.ArrayList;
import java.util.Map;

import com.bemu.BEmu.Name;
import com.bemu.BEmu.Element;
import com.bemu.BEmu.Datetime;

public class ElementReferenceFieldData extends ElementParent
{
    private final List<ElementParent> _fields;

    ElementReferenceFieldData(Map<String, Object> values)
    {
        this._fields = new ArrayList<ElementParent>();
        for(Map.Entry<String, Object> item : values.entrySet())
        {
        	String itemKey = item.getKey();
        	Object itemValue = item.getValue();
        	
        	if(itemValue instanceof Double)
        	{
        		ElementParent elmDouble = new ElementReferenceDouble(itemKey.toUpperCase(), (Double)itemValue);
        		this._fields.add(elmDouble);
        	}
        	else if(itemValue instanceof Integer)
        	{
        		ElementParent elmInt = new ElementReferenceInt(itemKey.toUpperCase(), (Integer)itemValue);
                this._fields.add(elmInt);
        	}
        	else if(itemValue instanceof Datetime)
        	{
        		ElementParent elmDatetime = new ElementReferenceDateTime(itemKey.toUpperCase(), (Datetime)itemValue);
                this._fields.add(elmDatetime);
        	}
        	else if(itemValue instanceof String)
        	{
        		ElementParent elmString = new ElementReferenceString(itemKey.toUpperCase(), (String)itemValue);
                this._fields.add(elmString);
        	}
        	else if(itemValue instanceof ElementReferenceArrayChainTickers)
                this._fields.add((ElementReferenceArrayChainTickers)itemValue);
        	
        }
    }
    
    public Name name()
    {
    	return new Name("fieldData");
    }
    
    public int numValues()
    {
    	return 1;
    }
    
    public int numElements()
    {
    	return this._fields.size();
    }
    
    public Element getElement(int index)
    {
    	return this._fields.get(index);
    }
    
    public Element getElement(String name) throws Exception
    {
    	String upper = name.toUpperCase();
    	for(int i = 0; i < this._fields.size(); i++)
    	{
    		Element item = this._fields.get(i);
    		if(item.name().toString().toUpperCase().equals(upper))
    		{
    			return item;
    		}
    	}
    	return super.getElement(name);
    }
    
    protected StringBuilder prettyPrint(int tabIndent)
    {
        String tabs = com.bemu.BEmu.types.IndentType.Indent(tabIndent);
        StringBuilder result = new StringBuilder();

        result.append(String.format("%sfieldData[] = {%s", tabs, System.getProperty("line.separator")));
        
        for(int i = 0; i < this._fields.size(); i++)
        {
        	result.append(this._fields.get(i).prettyPrint(tabIndent + 1));
        }

        result.append(String.format("%s}%s", tabs, System.getProperty("line.separator")));
        return result;
    }
    
    public boolean hasElement(String name, boolean excludeNullElements)
    {
    	String upper = name.toUpperCase();
    	for(int i = 0; i < this._fields.size(); i++)
    	{
    		if(this._fields.get(i).name().toString().toUpperCase().equals(upper))
    			return true;
    	}
    	return false;
    }
    
    public double getElementAsFloat64(String name) throws Exception
    {
    	return this.getElement(name).getValueAsFloat64();
    }
    
    public int getElementAsInt32(String name) throws Exception
    {
    	return this.getElement(name).getValueAsInt32();
    }
    
    public long getElementAsInt64(String name) throws Exception
    {
    	return this.getElement(name).getValueAsInt64();
    }
    
    public String getElementAsString(String name) throws Exception
    {
    	return this.getElement(name).getValueAsString();
    }
    
    
    
}
