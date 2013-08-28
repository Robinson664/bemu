//------------------------------------------------------------------------------
// <copyright project="BEmuJava" file="BEmu.HistoricalDataRequest.ElementHistoricFieldExceptions.java" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

package com.bemu.BEmu.HistoricalDataRequest;

import com.bemu.BEmu.Element;
import com.bemu.BEmu.Name;

public class ElementHistoricFieldExceptions extends ElementParent
{
    private final ElementHistoricString _fieldId;
    private final ElementHistoricErrorInfo _errorInfo;

    public ElementHistoricFieldExceptions(String badField)
    {
        this._fieldId = new ElementHistoricString("fieldId", badField);
        this._errorInfo = new ElementHistoricErrorInfo();
    }
	
    public Name name()
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

    protected StringBuilder prettyPrint(int tabIndent)
    {
        String tabs = com.bemu.BEmu.types.IndentType.Indent(tabIndent);
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
