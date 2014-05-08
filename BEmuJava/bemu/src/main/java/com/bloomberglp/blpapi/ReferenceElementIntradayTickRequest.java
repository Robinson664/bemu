//------------------------------------------------------------------------------
// <copyright project="BEmu_maven" file="/BEmu_maven/bemu/src/main/java/com/bloomberglp/blpapi/ReferenceElementIntradayTickRequest.java" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

package com.bloomberglp.blpapi;

public class ReferenceElementIntradayTickRequest extends Element
{
    private final IntradayTickElementDataParent _parent;

    ReferenceElementIntradayTickRequest(IntradayTickMessage msg)
    {
        this._parent = msg.firstElement();
    }
    
    public Name name() throws Exception
    {
    	return new Name("IntradayTickRequest");
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
    
    protected StringBuilder prettyPrint(int tabIndent) throws Exception
    {
        StringBuilder result = new StringBuilder();

        result.append(String.format("IntradayTickRequest = {%s", System.getProperty("line.separator")));
    	result.append(this._parent.prettyPrint(1));
        result.append(String.format("}%s", System.getProperty("line.separator")));
        
        return result;
    }
}
