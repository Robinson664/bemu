//------------------------------------------------------------------------------
// <copyright project="BEmu_maven" file="/BEmu_maven/bemu/src/main/java/com/bloomberglp/blpapi/ReferenceMessage.java" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

package com.bloomberglp.blpapi;

import com.bloomberglp.blpapi.Name;
import com.bloomberglp.blpapi.Element;
import com.bloomberglp.blpapi.Message;
import com.bloomberglp.blpapi.CorrelationID;

import java.util.Map;
import java.util.List;
import java.util.ArrayList;

public class ReferenceMessage extends Message
{
    private final ReferenceElementSecurityDataArray _securities;

    ReferenceMessage(CorrelationID corr, Map<String, Map<String, Object>> fieldData) throws Exception
    {
    	super(new Name("ReferenceDataResponse"), corr, null);
        this._securities = new ReferenceElementSecurityDataArray(fieldData);
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
    	if(name.equals(this._securities.name().toString()))
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
    	return new ReferenceElementData(this);
    }
    
    protected StringBuilder prettyPrint(int tabIndent) throws Exception
    {
        StringBuilder result = new StringBuilder();

        result.append(String.format("fieldData[] = {%s", System.getProperty("line.separator")));
        result.append(this._securities.prettyPrint(1));
        result.append(String.format("}%s", System.getProperty("line.separator")));
        
        return result;
    }
    
}
