package com.bemu.BEmu.ReferenceDataRequest;

import java.util.Map;

import com.bemu.BEmu.Name;
import com.bemu.BEmu.Element;

public class ElementReferenceSecurityData extends ElementParent
{
    private final ElementReferenceString _elmSecurityName;
    private final ElementReferenceInt _elmSequenceNumber;
    private final ElementReferenceFieldData _elmFieldData;

    ElementReferenceSecurityData(String securityName, Map<String, Object> fieldData, int sequenceNumber)
    {
        this._elmSecurityName = new ElementReferenceString("security", securityName);
        this._elmSequenceNumber = new ElementReferenceInt("sequenceNumber", sequenceNumber);
        this._elmFieldData = new ElementReferenceFieldData(fieldData);
    }
    
    public Name name()
    {
    	return new Name("securityData");
    }
    
    public int numValues()
    {
    	return 0;
    }
    
    public int numElements()
    {
    	return 3;
    }

    public String getElementAsString(String name) throws Exception
    {
    	if(this._elmSecurityName.name().toString().toUpperCase().equals(name.toUpperCase()))
    		return this._elmSecurityName.getValueAsString();
    	
    	else
    		return super.getElementAsString(name);
    }
    
    public Element getElement(String name) throws Exception
    {
    	String upper = name.toUpperCase();
    	
    	if(upper.equals("FIELDDATA"))
    		return this._elmFieldData;
    	
    	else if(upper.equals("SECURITY"))
    		return this._elmSecurityName;
    	
    	else if(upper.equals("SEQUENCENUMBER"))
    		return this._elmSequenceNumber;
    	
    	return super.getElement(name);
    }
    
    protected StringBuilder prettyPrint(int tabIndent)
    {
        String tabs = com.bemu.BEmu.types.IndentType.Indent(tabIndent);
        StringBuilder result = new StringBuilder();

        result.append(String.format("%s%s = {%s", tabs, this.name().toString(), System.getProperty("line.separator")));
        result.append(this._elmSecurityName.prettyPrint(tabIndent + 1));
        result.append(this._elmSequenceNumber.prettyPrint(tabIndent + 1));
        result.append(this._elmFieldData.prettyPrint(tabIndent + 1));
        result.append(String.format("%s}%s", tabs, System.getProperty("line.separator")));
        
        return result;
    }
    
}
