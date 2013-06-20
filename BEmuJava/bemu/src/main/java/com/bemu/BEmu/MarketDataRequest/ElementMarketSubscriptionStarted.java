//------------------------------------------------------------------------------
// <copyright project="BEmuJava" file="BEmu.MarketDataRequest.ElementMarketSubscriptionStarted.java" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

package com.bemu.BEmu.MarketDataRequest;


import com.bemu.BEmu.Name;

public class ElementMarketSubscriptionStarted extends ElementParent
{
	@SuppressWarnings("unused")
	private final ElementMarketNull _exceptions;
	
	ElementMarketSubscriptionStarted(MessageMarketSubscriptionStarted arg) throws Exception
    {
		this._exceptions = (ElementMarketNull)arg.getElement("exceptions");
    }
	
    public Name name()
    {
    	return new Name("SubscriptionStarted");
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
    	return new StringBuilder();
    }

    public String toString()
    {
    	return String.format("SubscriptionStarted = {%s}%s", System.getProperty("line.separator"), System.getProperty("line.separator"));
    }
}
