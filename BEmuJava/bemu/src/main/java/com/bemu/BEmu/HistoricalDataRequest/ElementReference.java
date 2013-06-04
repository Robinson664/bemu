package com.bemu.BEmu.HistoricalDataRequest;

import com.bemu.BEmu.Name;

public class ElementReference extends ElementParent
{
    private final ElementHistoricSecurityData _security;

    ElementReference(MessageHistoric msg)
    {
    	this._security = msg.security();
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
    
    protected StringBuilder prettyPrint(int tabIndent)
    {
        String tabs = com.bemu.BEmu.types.IndentType.Indent(tabIndent);
        StringBuilder result = new StringBuilder();

        result.append(String.format("HistoricalDataResponse (choice) = {%s", System.getProperty("line.separator")));        
    	result.append(this._security.prettyPrint(1));
        result.append(String.format("%s}%s", tabs, System.getProperty("line.separator")));
        return result;
    }
}
