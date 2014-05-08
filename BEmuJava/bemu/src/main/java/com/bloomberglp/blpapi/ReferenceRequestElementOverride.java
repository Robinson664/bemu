//------------------------------------------------------------------------------
// <copyright project="BEmu_maven" file="/BEmu_maven/bemu/src/main/java/com/bloomberglp/blpapi/ReferenceRequestElementOverride.java" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

package com.bloomberglp.blpapi;

import com.bloomberglp.blpapi.Name;
import com.bloomberglp.blpapi.Element;

public class ReferenceRequestElementOverride extends Element
{
    private ReferenceElementString _fieldId;
    private ReferenceElementObject _value;
    
    ReferenceRequestElementOverride()
    {
        this._fieldId = new ReferenceElementString("fieldId", "");
        this._value = new ReferenceElementObject("value", "");
    }
    
    public void setElement(String name, Object value) throws Exception
    {
    	if(name.equals("fieldId"))
            this._fieldId = new ReferenceElementString(name, value.toString());
    	
    	else if(name.equals("value"))
    		this._value = new ReferenceElementObject(name, value);
    	
    	else
    		super.setElement(name, value);
    }
    
    public Element getElement(String name) throws Exception
    {
    	if(name.equals("fieldId"))
            return this._fieldId;
    	
    	else if(name.equals("value"))
    		return this._value;
    	
    	else
    		return super.getElement(name);
    }
    
    public Name name() throws Exception
    {
    	return new Name("overrides");
    }
    
    public int numValues()
    {
    	return 1;
    }
    
    public int numElements()
    {
    	return 2;
    }
    
    protected StringBuilder prettyPrint(int tabIndent) throws Exception
    {
        String tabs = com.bloomberglp.blpapi.IndentType.Indent(tabIndent);
        StringBuilder result = new StringBuilder();

        result.append(String.format("%s%s = {%s", tabs, this.name().toString(), System.getProperty("line.separator")));
        result.append(this._fieldId.prettyPrint(tabIndent + 1));
        result.append(this._value.prettyPrint(tabIndent + 1));
        result.append(String.format("%s}%s", tabs, System.getProperty("line.separator")));
        
        return result;
    }

}
