//------------------------------------------------------------------------------
// <copyright project="BEmu_maven" file="/BEmu_maven/bemu/src/main/java/com/bloomberglp/blpapi/MarketElementSubscriptionStarted.java" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

package com.bloomberglp.blpapi;


import com.bloomberglp.blpapi.Name;
import com.bloomberglp.blpapi.Schema;

public class MarketElementSubscriptionStarted extends Element
{
	@SuppressWarnings("unused")
	private final MarketElementNull _exceptions;
	
	MarketElementSubscriptionStarted(MarketMessageSubscriptionStarted arg) throws Exception
    {
		this._exceptions = (MarketElementNull)arg.getElement("exceptions");
    }
	
    public Name name() throws Exception
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

    public Schema.Datatype datatype()
    {
    	return Schema.Datatype.SEQUENCE;
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
