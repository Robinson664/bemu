//------------------------------------------------------------------------------
// <copyright project="BEmu_maven" file="/BEmu_maven/bemu/src/main/java/com/bloomberglp/blpapi/HistoricElementFieldExceptionsArray.java" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

package com.bloomberglp.blpapi;

import java.util.List;
import java.util.ArrayList;

import com.bloomberglp.blpapi.Name;
import com.bloomberglp.blpapi.Element;
import com.bloomberglp.blpapi.SchemaTypeDefinition;

public class HistoricElementFieldExceptionsArray extends Element
{
    private final List<HistoricElementFieldExceptions> _exceptions;

    public HistoricElementFieldExceptionsArray(List<String> badFields)
    {
        this._exceptions = new ArrayList<HistoricElementFieldExceptions>(badFields.size());
        for(int i = 0; i < badFields.size(); i++)
        {
        	this._exceptions.add(new HistoricElementFieldExceptions(badFields.get(i)));
        }
    }
    
    public SchemaTypeDefinition typeDefinition() throws Exception
    {
    	return new SchemaTypeDefinition(this.datatype(), new Name("FieldException"));
    }
	
    public Name name() throws Exception
    {
    	return new Name("fieldExceptions");
    }
    
    public int numValues()
    {
    	return this._exceptions.size();
    }
    
    public int numElements()
    {
    	return 0;
    }
    
    public boolean isComplexType()
    {
    	return false;
    }
    
    public boolean isArray()
    {
    	return true;
    }
    
    public boolean isNull()
    {
    	return false;
    }

    public Object getValue(int index)
    {
        return this._exceptions.get(index);
    }

    public Element getValueAsElement(int index)
    {
        return this._exceptions.get(index);
    }
    
    protected StringBuilder prettyPrint(int tabIndent) throws Exception
    {
        String tabs = com.bloomberglp.blpapi.IndentType.Indent(tabIndent);
        StringBuilder result = new StringBuilder();

        result.append(String.format("%s%s[] = {%s", tabs, this.name().toString(), System.getProperty("line.separator")));
        
        for(int i = 0; i < this._exceptions.size(); i++)
        {
        	result.append(this._exceptions.get(i).prettyPrint(tabIndent + 1));
        }

        result.append(String.format("%s}%s", tabs, System.getProperty("line.separator")));
        return result;
    }

}
