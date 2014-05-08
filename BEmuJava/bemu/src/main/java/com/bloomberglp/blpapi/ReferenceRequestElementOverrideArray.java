//------------------------------------------------------------------------------
// <copyright project="BEmu_maven" file="/BEmu_maven/bemu/src/main/java/com/bloomberglp/blpapi/ReferenceRequestElementOverrideArray.java" company="Jordan Robinson">
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

public class ReferenceRequestElementOverrideArray extends Element
{
    private final List<ReferenceRequestElementOverride> _overrides;

    ReferenceRequestElementOverrideArray()
    {
        this._overrides = new ArrayList<ReferenceRequestElementOverride>();
    }
    
    public Name name() throws Exception
    {
    	return new Name("overrides");
    }
    
    public int numValues()
    {
    	return this._overrides.size();
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
    
    public Object getValue()
    {
    	return this.getValue(0);
    }
    
    public Object getValue(int index)
    {
    	return this._overrides.get(index);
    }

    public Element getValueAsElement() throws Exception
    {
        return this.getValueAsElement(0);
    }
    
    public Element getValueAsElement(int index)
    {
    	return (Element)this._overrides.get(index);
    }
    
    public Element appendElement()
    {
        ReferenceRequestElementOverride result = new ReferenceRequestElementOverride();
        this._overrides.add(result);
        return result;
    }
    
    protected StringBuilder prettyPrint(int tabIndent) throws Exception
    {
        String tabs = com.bloomberglp.blpapi.IndentType.Indent(tabIndent);
        StringBuilder result = new StringBuilder();

        result.append(String.format("%s%s[] = {%s", tabs, this.name().toString(), System.getProperty("line.separator")));
        
        for(int i = 0; i < this._overrides.size(); i++)
        {
        	result.append(this._overrides.get(i).prettyPrint(tabIndent + 1));
        }

        result.append(String.format("%s}%s", tabs, System.getProperty("line.separator")));
        return result;
    }
}
