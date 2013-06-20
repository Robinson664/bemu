//------------------------------------------------------------------------------
// <copyright project="BEmuJava" file="BEmu.MarketDataRequest.ElementMarketSubscriptionCancelReason.java" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

package com.bemu.BEmu.MarketDataRequest;

import com.bemu.BEmu.Name;
import com.bemu.BEmu.Element;

import java.util.List;
import java.util.LinkedList;

public class ElementMarketSubscriptionCancelReason extends ElementParent
{
    private final ElementMarketString _source, _category, _description, _subCategory;
    private final ElementMarketInt _errorCode;

    ElementMarketSubscriptionCancelReason()
    {
        this._source = new ElementMarketString("source", "Session");
        this._errorCode = new ElementMarketInt("errorCode", 0);
        this._category = new ElementMarketString("category", "CANCELED");
        this._description = new ElementMarketString("description", "Subscription canceled");
        this._subCategory = new ElementMarketString("subcategory", "");
    }

    public Name name()
    {
    	return new Name("reason");
    }
    
    public int numValues()
    {
    	return 1;
    }
    
    public int numElements()
    {
    	return 5;
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
    
    private List<Element> Elements()
    {
    	List<Element> result = new LinkedList<Element>();
    	result.add(this._source);
    	result.add(this._errorCode);
    	result.add(this._category);
    	result.add(this._description);
    	result.add(this._subCategory);
    	return result;
    }
    
    protected StringBuilder prettyPrint(int tabIndent)
    {
        String tabs = com.bemu.BEmu.types.IndentType.Indent(tabIndent);
        StringBuilder result = new StringBuilder();

        List<Element> elements = this.Elements(); 
        result.append(String.format("%sreason = {%s", tabs, System.getProperty("line.separator")));
        for(int i = 0; i < elements.size(); i++)
        {
        	ElementParent elm = (ElementParent)elements.get(i);
        	result.append(elm.prettyPrint(tabIndent + 1));
        }
        result.append(String.format("%s}%s", tabs, System.getProperty("line.separator")));

        return result;
    }
    
}
