//------------------------------------------------------------------------------
// <copyright project="BEmu_maven" file="/BEmu_maven/bemu/src/main/java/com/bloomberglp/blpapi/ReferenceElementSecurityDataArray.java" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

package com.bloomberglp.blpapi;

import java.util.List;
import java.util.Map;
import java.util.ArrayList;

import com.bloomberglp.blpapi.Name;
import com.bloomberglp.blpapi.Element;
import com.bloomberglp.blpapi.SchemaTypeDefinition;

public class ReferenceElementSecurityDataArray extends Element
{
    private final List<ReferenceElementSecurityData> _securities;

    ReferenceElementSecurityDataArray(Map<String, Map<String, Object>> securities)
    {
        this._securities = new ArrayList<ReferenceElementSecurityData>();

        for (Map.Entry<String, Map<String, Object>> item : securities.entrySet())
        {
        	String key = item.getKey();
        	Map<String, Object> value = item.getValue();
        	
            ReferenceElementSecurityData secData = new ReferenceElementSecurityData(key, value, this._securities.size());
            this._securities.add(secData);
        }
    }
    
    ReferenceElementSecurityDataArray(ReferenceElementSecurityDataArray arg) //copy constructor
    {
        this._securities = new ArrayList<ReferenceElementSecurityData>();
        for(int i = 0; i < arg._securities.size(); i++)
        {
        	this._securities.add(arg._securities.get(i));
        }
    }
    
    public SchemaTypeDefinition typeDefinition() throws Exception
    {
    	return new SchemaTypeDefinition(this.datatype(), new Name("ReferenceSecurityData"));
    }
    
    public Name name() throws Exception
    {
    	return new Name("securityData");
    }
    
    public int numValues()
    {
    	return this._securities.size();
    }
    
    public int numElements()
    {
    	return 0;
    }
    
    public boolean hasElement(String name) throws Exception
    {
    	for(int i = 0; i < this._securities.size(); i++)
    	{
    		ReferenceElementSecurityData item = this._securities.get(i);
            if (item.name().toString().equals(name))
                return true;
    	}
        return false;
    }
    
    public Element getValueAsElement(int index)
    {
        return this._securities.get(index);
    }
    
    protected StringBuilder prettyPrint(int tabIndent) throws Exception
    {
        String tabs = com.bloomberglp.blpapi.IndentType.Indent(tabIndent);
        StringBuilder result = new StringBuilder();

        result.append(String.format("%s%s[] = {%s", tabs, this.name().toString(), System.getProperty("line.separator")));
        
        for(int i = 0; i < this._securities.size(); i++)
        {
        	result.append(this._securities.get(i).prettyPrint(tabIndent + 1));
        }

        result.append(String.format("%s}%s", tabs, System.getProperty("line.separator")));
        return result;
    }
}
