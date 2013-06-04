package com.bemu.BEmu.ReferenceDataRequest;

import com.bemu.BEmu.Request;
import com.bemu.BEmu.Element;
import java.util.List;

public class RequestReference extends Request
{
    private final RequestReferenceElementStringArray _securities, _fields;
    private final RequestReferenceElementOverrideArray _overrides;

    public RequestReference()
    {
        this._securities = new RequestReferenceElementStringArray("securities");
        this._fields = new RequestReferenceElementStringArray("fields");
        this._overrides = new RequestReferenceElementOverrideArray();
    }
    
    List<String> securities()
    {
    	return this._securities.values();
    }
    
    List<String> fields()
    {
    	return this._fields.values();
    }
    
    public Element getElement(String name) throws Exception
    {
        String strName = name.toUpperCase();

        if (this._securities.name().toString().toUpperCase().equals(strName))
            return this._securities;
        
        else if (this._fields.name().toString().toUpperCase().equals(strName))
            return this._fields;
        
        else if (this._overrides.name().toString().toUpperCase().equals(strName))
            return this._overrides;
            
        else
            return super.getElement(name);
    }
    
    public boolean hasElement(String name)
    {
        String strName = name.toUpperCase();

        if (this._securities.name().toString().toUpperCase().equals(strName))
            return this._securities.values().size() > 0;
        
        else if (this._fields.name().toString().toUpperCase().equals(strName))
            return this._fields.values().size() > 0;
        
        else if (this._overrides.name().toString().toUpperCase().equals(strName))
            return this._overrides.numValues() > 0;
            
        else
            return false;
    }
    
    public void append(String name, String elementValue) throws Exception
    {
    	String lower = name.toLowerCase();
    	
    	if(lower.equals("securities"))
    		this._securities.addValue(elementValue);
    	
    	else if(lower.equals("fields"))
    		this._fields.addValue(elementValue);
    	
    	else
    		throw new Exception(String.format("BEmu.RequestReference.Append: Element name %s not supported", name));
    }
    
    public String toString()
    {
        StringBuilder result = new StringBuilder();
        result.append(String.format("ReferenceDataRequest = {%s", System.getProperty("line.separator")));

        if (this._securities.numValues() > 0)
            result.append(this._securities.prettyPrint(1));

        if (this._fields.numValues() > 0)
            result.append(this._fields.prettyPrint(1));

        if (this._overrides.numValues() > 0)
            result.append(this._overrides.prettyPrint(1));

        result.append("}");

        return result.toString();
    }
    
}
