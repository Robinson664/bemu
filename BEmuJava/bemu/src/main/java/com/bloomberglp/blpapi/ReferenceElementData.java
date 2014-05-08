//------------------------------------------------------------------------------
// <copyright project="BEmu_maven" file="/BEmu_maven/bemu/src/main/java/com/bloomberglp/blpapi/ReferenceElementData.java" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

package com.bloomberglp.blpapi;

public class ReferenceElementData extends Element
{
    private final ReferenceElementSecurityDataArray _securities;

    ReferenceElementData(ReferenceMessage arg)
    {
        this._securities = new ReferenceElementSecurityDataArray((ReferenceElementSecurityDataArray)arg.elements().get(0));
    }
    
    public Name name() throws Exception
    {
    	return new Name("securityData");
    }
    
    public int numValues()
    {
    	return 1;
    }
    
    public int numElements()
    {
    	return 1;
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

    public Schema.Datatype datatype()
    {
    	return Schema.Datatype.CHOICE;
    }

    public Element getElement(String name) throws Exception
    {
        if (name.equals(this._securities.name().toString()))
            return this._securities;
        
        else
            return super.getElement(name);
    }
    
    protected StringBuilder prettyPrint(int tabIndent) throws Exception
    {
        StringBuilder result = new StringBuilder();

        result.append(String.format("ReferenceDataResponse (choice) = {%s", System.getProperty("line.separator")));
        result.append(this._securities.prettyPrint(1));
        result.append(String.format("}%s", System.getProperty("line.separator")));
        
        return result;
    }
    
}
