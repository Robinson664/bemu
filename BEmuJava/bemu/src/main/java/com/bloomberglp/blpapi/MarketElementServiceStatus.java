//------------------------------------------------------------------------------
// <copyright project="BEmu_maven" file="/BEmu_maven/bemu/src/main/java/com/bloomberglp/blpapi/MarketElementServiceStatus.java" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

package com.bloomberglp.blpapi;

import com.bloomberglp.blpapi.Element;
import com.bloomberglp.blpapi.Name;
import com.bloomberglp.blpapi.Schema;

public class MarketElementServiceStatus extends Element
{
    private final MarketElementString _serviceName;

    MarketElementServiceStatus(MarketMessageServiceStatus arg) throws Exception
    {
        this._serviceName = (MarketElementString)arg.getElement("serviceName");
    }
	
    public Name name() throws Exception
    {
    	return new Name("ServiceOpened");
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
    	return Schema.Datatype.SEQUENCE;
    }
    
    protected StringBuilder prettyPrint(int tabIndent) throws Exception
    {
        StringBuilder result = new StringBuilder();

        result.append(String.format("%s = {%s", this.name().toString(), System.getProperty("line.separator")));
        result.append(this._serviceName.prettyPrint(tabIndent + 1));
        result.append(String.format("}", System.getProperty("line.separator")));

        return result;
    }
    
}
