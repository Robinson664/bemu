package com.bemu.BEmu.ReferenceDataRequest;

import com.bemu.BEmu.Element;
import com.bemu.BEmu.Name;

public class ElementReference extends Element
{
    private final ElementReferenceSecurityDataArray _securities;

    ElementReference(MessageReference arg)
    {
        this._securities = new ElementReferenceSecurityDataArray((ElementReferenceSecurityDataArray)arg.elements().get(0));
    }
    
    public Name name()
    {
    	return new Name("securityData");
    }
    
    public int numValues()
    {
    	return 1;
    }
    
    public int numElements()
    {
    	return 1;
    }
    
    public boolean isComplexType()
    {
    	return true;
    }
    
    public boolean isArray()
    {
    	return false;
    }
    
    public boolean isNull()
    {
    	return false;
    }

    public Element getElement(String name) throws Exception
    {
        if (name.toUpperCase().equals(this._securities.name().toString().toUpperCase()))
            return this._securities;
        
        else
            return super.getElement(name);
    }
    
    protected StringBuilder prettyPrint(int tabIndent)
    {
        StringBuilder result = new StringBuilder();

        result.append(String.format("ReferenceDataResponse (choice) = {%s", System.getProperty("line.separator")));
        result.append(this._securities.prettyPrint(1));
        result.append(String.format("}%s", System.getProperty("line.separator")));
        
        return result;
    }
    
}
