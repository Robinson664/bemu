//------------------------------------------------------------------------------
// <copyright project="BEmu_maven" file="/BEmu_maven/bemu/src/main/java/com/bloomberglp/blpapi/MarketElementSubscriptionCancelReason.java" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

package com.bloomberglp.blpapi;

import com.bloomberglp.blpapi.Name;
import com.bloomberglp.blpapi.Element;

import java.util.List;
import java.util.LinkedList;

public class MarketElementSubscriptionCancelReason extends Element
{
    private final MarketElementString _source, _category, _description, _subCategory;
    private final MarketElementInt _errorCode;

    MarketElementSubscriptionCancelReason()
    {
        this._source = new MarketElementString("source", "Session");
        this._errorCode = new MarketElementInt("errorCode", 0);
        this._category = new MarketElementString("category", "CANCELED");
        this._description = new MarketElementString("description", "Subscription canceled");
        this._subCategory = new MarketElementString("subcategory", "");
    }

    public Name name() throws Exception
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
    
    protected StringBuilder prettyPrint(int tabIndent) throws Exception
    {
        String tabs = com.bloomberglp.blpapi.IndentType.Indent(tabIndent);
        StringBuilder result = new StringBuilder();

        List<Element> elements = this.Elements(); 
        result.append(String.format("%sreason = {%s", tabs, System.getProperty("line.separator")));
        for(int i = 0; i < elements.size(); i++)
        {
        	Element elm = elements.get(i);
        	result.append(elm.prettyPrint(tabIndent + 1));
        }
        result.append(String.format("%s}%s", tabs, System.getProperty("line.separator")));

        return result;
    }
    
}
