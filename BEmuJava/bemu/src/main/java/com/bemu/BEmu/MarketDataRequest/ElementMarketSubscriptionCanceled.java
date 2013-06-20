//------------------------------------------------------------------------------
// <copyright project="BEmuJava" file="BEmu.MarketDataRequest.ElementMarketSubscriptionCanceled.java" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

package com.bemu.BEmu.MarketDataRequest;

import com.bemu.BEmu.Name;

public class ElementMarketSubscriptionCanceled extends ElementParent
{
    private final ElementMarketSubscriptionCancelReason _reason;

    ElementMarketSubscriptionCanceled(MessageMarketSubscriptionCanceled arg) throws Exception
    {
        this._reason = (ElementMarketSubscriptionCancelReason)arg.getElement("reason");
    }
	
    public Name name()
    {
    	return new Name("SubscriptionTerminated");
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
        String tabs = com.bemu.BEmu.types.IndentType.Indent(tabIndent);
        StringBuilder result = new StringBuilder();

        result.append(String.format("%s%s = {%s", tabs, this.name().toString(), System.getProperty("line.separator")));
        result.append(this._reason.prettyPrint(tabIndent + 1));
        result.append(String.format("%s}%s", tabs, System.getProperty("line.separator")));

        return result;
    }
    
    
    
    
}
