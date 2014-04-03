//------------------------------------------------------------------------------
// <copyright project="BEmuJava" file="BEmu.HistoricalDataRequest.ElementHistoricFieldExceptionsArray.java" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

package com.bemu.BEmu.HistoricalDataRequest;

import java.util.List;
import java.util.ArrayList;

import com.bemu.BEmu.Name;
import com.bemu.BEmu.Element;
import com.bemu.BEmu.SchemaTypeDefinition;

public class ElementHistoricFieldExceptionsArray extends ElementParent
{
    private final List<ElementHistoricFieldExceptions> _exceptions;

    public ElementHistoricFieldExceptionsArray(List<String> badFields)
    {
        this._exceptions = new ArrayList<ElementHistoricFieldExceptions>(badFields.size());
        for(int i = 0; i < badFields.size(); i++)
        {
        	this._exceptions.add(new ElementHistoricFieldExceptions(badFields.get(i)));
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
        String tabs = com.bemu.BEmu.types.IndentType.Indent(tabIndent);
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
