//------------------------------------------------------------------------------
// <copyright project="BEmuJava" file="BEmu.MarketDataRequest.ElementMarketServiceStatus.java" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

package com.bemu.BEmu.MarketDataRequest;

import com.bemu.BEmu.Element;
import com.bemu.BEmu.Name;

public class ElementMarketServiceStatus extends Element
{
    private final ElementMarketString _serviceName;

    ElementMarketServiceStatus(MessageMarketServiceStatus arg) throws Exception
    {
        this._serviceName = (ElementMarketString)arg.getElement("serviceName");
    }
	
    public Name name()
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
    
    protected StringBuilder prettyPrint(int tabIndent)
    {
        StringBuilder result = new StringBuilder();

        result.append(String.format("%s = {%s", this.name().toString(), System.getProperty("line.separator")));
        result.append(this._serviceName.prettyPrint(tabIndent + 1));
        result.append(String.format("}", System.getProperty("line.separator")));

        return result;
    }
    
}
