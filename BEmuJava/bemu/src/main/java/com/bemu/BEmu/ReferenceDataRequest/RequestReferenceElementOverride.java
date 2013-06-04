package com.bemu.BEmu.ReferenceDataRequest;

import com.bemu.BEmu.Name;
import com.bemu.BEmu.Element;

public class RequestReferenceElementOverride extends ElementParent
{
    private ElementReferenceString _fieldId;
    private ElementReferenceObject _value;
    
    RequestReferenceElementOverride()
    {
        this._fieldId = new ElementReferenceString("fieldId", "");
        this._value = new ElementReferenceObject("value", "");
    }
    
    public void setElement(String name, Object value) throws Exception
    {
    	String upper = name.toUpperCase();
    	
    	if(upper.equals("FIELDID"))
            this._fieldId = new ElementReferenceString(upper, value.toString());
    	
    	else if(upper.equals("VALUE"))
    		this._value = new ElementReferenceObject(upper, value);
    	
    	else
    		super.setElement(name, value);
    }
    
    public Element getElement(String name) throws Exception
    {
    	String upper = name.toUpperCase();
    	
    	if(upper.equals("FIELDID"))
            return this._fieldId;
    	
    	else if(upper.equals("VALUE"))
    		return this._value;
    	
    	else
    		return super.getElement(name);
    }
    
    public Name name()
    {
    	return new Name("overrides");
    }
    
    public int numValues()
    {
    	return 1;
    }
    
    public int numElements()
    {
    	return 2;
    }
    
    protected StringBuilder prettyPrint(int tabIndent)
    {
        String tabs = com.bemu.BEmu.types.IndentType.Indent(tabIndent);
        StringBuilder result = new StringBuilder();

        result.append(String.format("%s%s = {%s", tabs, this.name().toString(), System.getProperty("line.separator")));
        result.append(this._fieldId.prettyPrint(tabIndent + 1));
        result.append(this._value.prettyPrint(tabIndent + 1));
        result.append(String.format("%s}%s", tabs, System.getProperty("line.separator")));
        
        return result;
    }

}
