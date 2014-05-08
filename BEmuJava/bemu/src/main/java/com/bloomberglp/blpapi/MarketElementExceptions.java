//------------------------------------------------------------------------------
// <copyright project="BEmu_maven" file="/BEmu_maven/bemu/src/main/java/com/bloomberglp/blpapi/MarketElementExceptions.java" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

package com.bloomberglp.blpapi;

import com.bloomberglp.blpapi.Element;
import com.bloomberglp.blpapi.Name;
import com.bloomberglp.blpapi.SchemaTypeDefinition;

public class MarketElementExceptions extends Element
{
    private final MarketElementString _fieldId;
    private final MarketElementReason _reason;

    public MarketElementExceptions(String badField)
    {
        this._fieldId = new MarketElementString("fieldId", badField);
        this._reason = new MarketElementReason(MarketElementReason.ReasonTypeEnum.badField);
    }
    
    public SchemaTypeDefinition typeDefinition() throws Exception
    {
    	return new SchemaTypeDefinition(this.datatype(), new Name("SubscriptionException"));
    }
	
    public Name name() throws Exception
    {
    	return new Name("exceptions");
    }
    
    public int numValues()
    {
    	return 1;
    }
    
    public int numElements()
    {
    	return 2;
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
    
    public boolean hasElement(String name, boolean excludeNullElements)
    {
    	return this.hasElement(name);
    }
    
    public boolean hasElement(String name)
    {
    	return name.equals("fieldId") || name.equals("reason");
    }

    public String getElementAsString(String name) throws Exception
    {
        return this.getElement(name).getValueAsString();
    }
    
    public Element getElement(String name) throws Exception
    {
    	if(name.equals("fieldId"))
    		return this._fieldId;
    	
    	else if(name.equals("reason"))
    		return this._reason;
    	
    	else
    		throw new Exception("name not recognized. names are case-sensitive.");
    }
    
    protected StringBuilder prettyPrint(int tabIndent) throws Exception
    {
        String tabs = com.bloomberglp.blpapi.IndentType.Indent(tabIndent);
        StringBuilder result = new StringBuilder();
        
        result.append(String.format("%s%s = {%s", tabs, this.name().toString(), System.getProperty("line.separator")));
        result.append(this._fieldId.prettyPrint(tabIndent + 1));
        result.append(this._reason.prettyPrint(tabIndent + 1));
        result.append(String.format("%s}%s", tabs, System.getProperty("line.separator")));

        return result;
    }

}
