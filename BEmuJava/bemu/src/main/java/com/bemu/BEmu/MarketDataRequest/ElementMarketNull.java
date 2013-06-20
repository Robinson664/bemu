//------------------------------------------------------------------------------
// <copyright project="BEmuJava" file="BEmu.MarketDataRequest.ElementMarketNull.java" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

package com.bemu.BEmu.MarketDataRequest;

import com.bemu.BEmu.Name;

public class ElementMarketNull extends ElementParent
{
	private final String _name;
	
	ElementMarketNull(String name)
	{
		this._name = name;
	}
	
    public Name name()
    {
    	return new Name(this._name);
    }
    
    public int numValues()
    {
    	return 0;
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
    	return true;
    }
    
    protected StringBuilder prettyPrint(int tabIndent)
    {
    	return new StringBuilder();
    }
}
