//------------------------------------------------------------------------------
// <copyright project="BEmu_maven" file="/BEmu_maven/bemu/src/main/java/com/bloomberglp/blpapi/HistoricElementFieldExceptions.java" company="Jordan Robinson">
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

public class HistoricElementFieldExceptions extends Element
{
    private final HistoricElementString _fieldId;
    private final HistoricElementErrorInfo _errorInfo;

    public HistoricElementFieldExceptions(String badField)
    {
        this._fieldId = new HistoricElementString("fieldId", badField);
        this._errorInfo = new HistoricElementErrorInfo();
    }
    
    public SchemaTypeDefinition typeDefinition() throws Exception
    {
    	return new SchemaTypeDefinition(this.datatype(), new Name("FieldException"));
    }
	
    public Name name() throws Exception
    {
    	return new Name("errorInfo");
    }
    
    public int numValues()
    {
    	return 1;
    }
    
    public int numElements()
    {
    	return 2;
    }
    
    public String getElementAsString(String name) throws Exception
    {
    	return this.getElement(name).getValueAsString();
    }
    
    public int getElementAsInt32(String name) throws Exception
    {
    	return this.getElement(name).getValueAsInt32();
    }
    
    public Element getElement(String name) throws Exception
    {
    	if(name.equals("fieldId"))
    		return this._fieldId;
    	
    	else if(name.equals("errorInfo"))
    		return this._errorInfo;
    	
    	else
    		return super.getElement(name);
    }
    
    public boolean hasElement(String name)
    {
    	return name.equals("fieldId") || name.equals("errorInfo");
    }

    protected StringBuilder prettyPrint(int tabIndent) throws Exception
    {
        String tabs = com.bloomberglp.blpapi.IndentType.Indent(tabIndent);
        StringBuilder result = new StringBuilder();
        
        result.append(String.format("%s%s = {%s", tabs, this.name().toString(), System.getProperty("line.separator")));
        result.append(this._fieldId.prettyPrint(tabIndent + 1));
        result.append(this._errorInfo.prettyPrint(tabIndent + 1));
        result.append(String.format("%s}%s", tabs, System.getProperty("line.separator")));

        return result;
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
    
    
}
