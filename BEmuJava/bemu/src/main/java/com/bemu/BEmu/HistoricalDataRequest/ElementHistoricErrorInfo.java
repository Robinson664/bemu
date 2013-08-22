//------------------------------------------------------------------------------
// <copyright project="BEmuJava" file="BEmu.HistoricalDataRequest.ElementHistoricErrorInfo.java" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

package com.bemu.BEmu.HistoricalDataRequest;

import com.bemu.BEmu.Element;
import com.bemu.BEmu.Name;
import com.bemu.BEmu.types.RandomDataGenerator;

public class ElementHistoricErrorInfo extends ElementParent
{
    private final ElementHistoricString _source, _category, _message, _subCategory;
    private final ElementHistoricInt _code;

    ElementHistoricErrorInfo()
    {
        String sourceGibberish = RandomDataGenerator.randomString(5).toLowerCase();
        
        this._source = new ElementHistoricString("source", String.format("%s::%s%s", RandomDataGenerator.randomInt(999), sourceGibberish, RandomDataGenerator.randomInt(99)));
        this._code = new ElementHistoricInt("code", RandomDataGenerator.randomInt(99));
        this._category = new ElementHistoricString("category", "BAD_FLD");
        this._message = new ElementHistoricString("message", "Invalid field");
        this._subCategory = new ElementHistoricString("subcategory", "NOT_APPLICABLE_TO_HIST_DATA");
    }
	
    public Name name()
    {
    	return new Name("errorInfo");
    }
    
    public int numValues()
    {
    	return 1;
    }
    
    public int numElements()
    {
    	return 5;
    }
    
    public String getElementAsString(String name) throws Exception
    {
    	return this.getElement(name).getValueAsString();
    }
    
    public int getElementAsInt32(String name) throws Exception
    {
    	return this.getElement(name).getValueAsInt32();
    }
    
    public Element getElement(String name) throws Exception
    {
    	String upper = name.toUpperCase();
    	if(upper.equals("SOURCE"))
    		return this._source;
    	
    	else if(upper.equals("CODE"))
    		return this._code;
    	
    	else if(upper.equals("CATEGORY"))
    		return this._category;
    	
    	else if(upper.equals("MESSAGE"))
    		return this._message;
    	
    	else if(upper.equals("SUBCATEGORY"))
    		return this._subCategory;
    	
    	else
    		return super.getElement(name);
    }
    
    public boolean hasElement(String name)
    {
    	return this.hasElement(name, false);
    }
    
    public boolean hasElement(String name, boolean excludeNullElements)
    {
    	String upper = name.toUpperCase();
    	return upper.equals("SOURCE") ||
    			upper.equals("CODE") ||
    			upper.equals("CATEGORY") ||
    			upper.equals("MESSAGE") ||
    			upper.equals("SUBCATEGORY");
    }    
    
    protected StringBuilder prettyPrint(int tabIndent)
    {
        String tabs = com.bemu.BEmu.types.IndentType.Indent(tabIndent);
        StringBuilder result = new StringBuilder();
        
        result.append(String.format("%s%s = {%s", tabs, this.name().toString(), System.getProperty("line.separator")));
        result.append(this._source.prettyPrint(tabIndent + 1));
        result.append(this._code.prettyPrint(tabIndent + 1));
        result.append(this._category.prettyPrint(tabIndent + 1));
        result.append(this._message.prettyPrint(tabIndent + 1));
        result.append(this._subCategory.prettyPrint(tabIndent + 1));
        result.append(String.format("%s}%s", tabs, System.getProperty("line.separator")));

        return result;
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

}
