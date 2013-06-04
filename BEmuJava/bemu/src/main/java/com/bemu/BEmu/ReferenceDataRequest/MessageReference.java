package com.bemu.BEmu.ReferenceDataRequest;

import com.bemu.BEmu.Name;
import com.bemu.BEmu.Element;
import com.bemu.BEmu.Message;
import com.bemu.BEmu.CorrelationID;

import java.util.Map;
import java.util.List;
import java.util.ArrayList;

public class MessageReference extends Message
{
    private final ElementReferenceSecurityDataArray _securities;

    MessageReference(CorrelationID corr, Map<String, Map<String, Object>> fieldData)
    {
    	super(new Name("ReferenceDataResponse"), corr, null);
        this._securities = new ElementReferenceSecurityDataArray(fieldData);
    }
    
    public int numElements()
    {
    	return 1;
    }
    
    List<Element> elements()
    {
    	List<Element> result = new ArrayList<Element>();
    	result.add(this._securities);
    	return result;
    }
    
    public Element getElement(String name) throws Exception
    {
    	if(name.toUpperCase().equals(this._securities.name().toString().toUpperCase()))
    		return this._securities;
    	
    	else
    		return super.getElement(name);
    }
    
    public String topicName()
    {
    	return "";
    }
    
    public Element asElement()
    {
    	return new ElementReference(this);
    }
    
    protected StringBuilder prettyPrint(int tabIndent)
    {
        StringBuilder result = new StringBuilder();

        result.append(String.format("fieldData[] = {%s", System.getProperty("line.separator")));
        result.append(this._securities.prettyPrint(1));
        result.append(String.format("}%s", System.getProperty("line.separator")));
        
        return result;
    }
    
}
