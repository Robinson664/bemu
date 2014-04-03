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
    	if(name.equals("fieldId"))
            this._fieldId = new ElementReferenceString(name, value.toString());
    	
    	else if(name.equals("value"))
    		this._value = new ElementReferenceObject(name, value);
    	
    	else
    		super.setElement(name, value);
    }
    
    public Element getElement(String name) throws Exception
    {
    	if(name.equals("fieldId"))
            return this._fieldId;
    	
    	else if(name.equals("value"))
    		return this._value;
    	
    	else
    		return super.getElement(name);
    }
    
    public Name name() throws Exception
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
    
    protected StringBuilder prettyPrint(int tabIndent) throws Exception
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
