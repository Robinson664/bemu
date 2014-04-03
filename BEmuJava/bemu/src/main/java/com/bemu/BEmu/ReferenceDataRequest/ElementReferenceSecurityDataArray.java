package com.bemu.BEmu.ReferenceDataRequest;

import java.util.List;
import java.util.Map;
import java.util.ArrayList;

import com.bemu.BEmu.Name;
import com.bemu.BEmu.Element;
import com.bemu.BEmu.SchemaTypeDefinition;

public class ElementReferenceSecurityDataArray extends ElementParent
{
    private final List<ElementReferenceSecurityData> _securities;

    ElementReferenceSecurityDataArray(Map<String, Map<String, Object>> securities)
    {
        this._securities = new ArrayList<ElementReferenceSecurityData>();

        for (Map.Entry<String, Map<String, Object>> item : securities.entrySet())
        {
        	String key = item.getKey();
        	Map<String, Object> value = item.getValue();
        	
            ElementReferenceSecurityData secData = new ElementReferenceSecurityData(key, value, this._securities.size());
            this._securities.add(secData);
        }
    }
    
    ElementReferenceSecurityDataArray(ElementReferenceSecurityDataArray arg) //copy constructor
    {
        this._securities = new ArrayList<ElementReferenceSecurityData>();
        for(int i = 0; i < arg._securities.size(); i++)
        {
        	this._securities.add(arg._securities.get(i));
        }
    }
    
    public SchemaTypeDefinition typeDefinition() throws Exception
    {
    	return new SchemaTypeDefinition(this.datatype(), new Name("ReferenceSecurityData"));
    }
    
    public Name name() throws Exception
    {
    	return new Name("securityData");
    }
    
    public int numValues()
    {
    	return this._securities.size();
    }
    
    public int numElements()
    {
    	return 0;
    }
    
    public boolean hasElement(String name) throws Exception
    {
    	for(int i = 0; i < this._securities.size(); i++)
    	{
    		ElementReferenceSecurityData item = this._securities.get(i);
            if (item.name().toString().equals(name))
                return true;
    	}
        return false;
    }
    
    public Element getValueAsElement(int index)
    {
        return this._securities.get(index);
    }
    
    protected StringBuilder prettyPrint(int tabIndent) throws Exception
    {
        String tabs = com.bemu.BEmu.types.IndentType.Indent(tabIndent);
        StringBuilder result = new StringBuilder();

        result.append(String.format("%s%s[] = {%s", tabs, this.name().toString(), System.getProperty("line.separator")));
        
        for(int i = 0; i < this._securities.size(); i++)
        {
        	result.append(this._securities.get(i).prettyPrint(tabIndent + 1));
        }

        result.append(String.format("%s}%s", tabs, System.getProperty("line.separator")));
        return result;
    }
}
