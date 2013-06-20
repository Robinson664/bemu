//------------------------------------------------------------------------------
// <copyright project="BEmuJava" file="BEmu.HistoricalDataRequest.ElementHistoricSecurityData.java" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

package com.bemu.BEmu.HistoricalDataRequest;

import java.util.Map;
import com.bemu.BEmu.Datetime;
import com.bemu.BEmu.Name;
import com.bemu.BEmu.Element;

public class ElementHistoricSecurityData extends ElementParent
{
    private final ElementHistoricString _elmSecurityName;
    private final ElementHistoricFieldDataArray _elmFieldDataArray;
    private final ElementHistoricInt _elmSequenceNumber;

    ElementHistoricSecurityData(String securityName, Map<Datetime, Map<String, Object>> fieldData, int sequenceNumber)
    {
        this._elmSecurityName = new ElementHistoricString("security", securityName);
        this._elmFieldDataArray = new ElementHistoricFieldDataArray(fieldData);
        this._elmSequenceNumber = new ElementHistoricInt("sequenceNumber", sequenceNumber);
    }
    
    public Name name()
    {
    	return new Name("securityData");
    }
    
    public int numValues()
    {
    	return 1;
    }
    
    public int numElements()
    {
    	return 3;
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
    
    public Element getElement(String name) throws Exception
    {
    	String upper = name.toUpperCase();
    	if(upper.equals("FIELDDATA"))
    		return this._elmFieldDataArray;
    	else if(upper.equals("SECURITY"))
    		return this._elmSecurityName;
    	else if(upper.equals("SEQUENCENUMBER"))
    		return this._elmSequenceNumber;
    	
    	else
    		return super.getElement(name);
    }
    
    public String getElementAsString(String name) throws Exception
    {
    	if(name.toUpperCase() == this._elmSecurityName.name().toString().toUpperCase())
    		return this._elmSecurityName.getValueAsString();
    	else
    		return super.getElementAsString(name);
    }
    
    public int getElementAsInt32(String name) throws Exception
    {
    	if(name.toUpperCase() == this._elmSequenceNumber.name().toString().toUpperCase())
    		return this._elmSecurityName.getValueAsInt32();
    	else
    		return super.getElementAsInt32(name);
    }
    
    protected StringBuilder prettyPrint(int tabIndent)
    {
        String tabs = com.bemu.BEmu.types.IndentType.Indent(tabIndent);
        StringBuilder result = new StringBuilder();
        
        result.append(String.format("%s%s = {%s", tabs, this.name().toString(), System.getProperty("line.separator")));
        result.append(this._elmSecurityName.prettyPrint(tabIndent + 1));
        result.append(this._elmSequenceNumber.prettyPrint(tabIndent + 1));
        result.append(this._elmFieldDataArray.prettyPrint(tabIndent + 1));
        result.append(String.format("%s}%s", tabs, System.getProperty("line.separator")));

        return result;
    }
}
