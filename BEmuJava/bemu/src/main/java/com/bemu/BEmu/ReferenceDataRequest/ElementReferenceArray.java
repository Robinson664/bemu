//------------------------------------------------------------------------------
// <copyright project="BEmuJava" file="BEmu.ReferenceDataRequest.ElementReferenceArray.java" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

package com.bemu.BEmu.ReferenceDataRequest;

import java.util.List;

import com.bemu.BEmu.Element;
import com.bemu.BEmu.Name;

public class ElementReferenceArray extends ElementParent
{
	protected final List<ElementParent> _values;
	private final String _name;
	
	ElementReferenceArray(String name, List<ElementParent> elements)
    {
        this._name = name;
        this._values = elements;
    }
	
    public Name name() throws Exception
    {
    	return new Name(this._name);
    }
    
    public int numValues()
    {
    	return this._values.size();
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
    	return this._values.get(index);
    }
    
    public Element getValueAsElement(int index)
    {
    	return this._values.get(index);
    }
    
    protected StringBuilder prettyPrint(int tabIndent) throws Exception
    {
        String tabs = com.bemu.BEmu.types.IndentType.Indent(tabIndent);
        StringBuilder result = new StringBuilder();

        result.append(String.format("%s%s[] = {%s", tabs, this.name().toString(), System.getProperty("line.separator")));
        
        for(int i = 0; i < this._values.size(); i++)
        {
        	result.append(this._values.get(i).prettyPrint(tabIndent + 1));
        }

        result.append(String.format("%s}%s", tabs, System.getProperty("line.separator")));
        return result;
    }
}
