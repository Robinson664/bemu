//------------------------------------------------------------------------------
// <copyright project="BEmuJava" file="BEmu.IntradayTickRequest.ElementReference.java" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

package com.bemu.BEmu.IntradayTickRequest;

import com.bemu.BEmu.Element;
import com.bemu.BEmu.Name;

public class ElementReference extends Element
{
    private final ElementIntradayTickDataParent _parent;

    ElementReference(MessageIntradayTick msg)
    {
        this._parent = msg.firstElement();
    }
    
    public Name name()
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
    
    protected StringBuilder prettyPrint(int tabIndent)
    {
        StringBuilder result = new StringBuilder();

        result.append(String.format("IntradayTickRequest = {%s", System.getProperty("line.separator")));
    	result.append(this._parent.prettyPrint(1));
        result.append(String.format("}%s", System.getProperty("line.separator")));
        
        return result;
    }
}
