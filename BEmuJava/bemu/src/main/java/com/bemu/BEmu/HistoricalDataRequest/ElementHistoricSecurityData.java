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
import java.util.List;
import com.bemu.BEmu.Datetime;
import com.bemu.BEmu.Name;
import com.bemu.BEmu.Element;
import com.bemu.BEmu.SchemaTypeDefinition;
import com.bemu.BEmu.types.Rules;

public class ElementHistoricSecurityData extends ElementParent
{
    private final ElementHistoricString _elmSecurityName;
    private final ElementHistoricFieldDataArray _elmFieldDataArray;
    private final ElementHistoricInt _elmSequenceNumber;
    private final ElementHistoricFieldExceptionsArray _elmFieldExceptions;
    private final ElementHistoricSecurityError _elmSecError;
    private final boolean _isSecurityError;
    private final int _numElements;

    ElementHistoricSecurityData(String securityName, List<String> badFields, Map<Datetime, Map<String, Object>> fieldData, int sequenceNumber) throws Exception
    {
        this._isSecurityError = Rules.isSecurityError(securityName);

        //remove bad field names from the dictionary
        if (badFields.size() == 0)
            this._elmFieldExceptions = null;
        else
            this._elmFieldExceptions = new ElementHistoricFieldExceptionsArray(badFields);
        
        this._elmSecurityName = new ElementHistoricString("security", securityName);
        this._elmSequenceNumber = new ElementHistoricInt("sequenceNumber", sequenceNumber);
        
        if (this._isSecurityError)
        {
            this._elmSecError = new ElementHistoricSecurityError(securityName);
            this._elmFieldDataArray = null;
        }
        else
        {
            this._elmSecError = null;
            this._elmFieldDataArray = new ElementHistoricFieldDataArray(fieldData);
        }
        
        this._numElements = this._elmFieldExceptions == null ? 3 : 4;
    }
    
    public SchemaTypeDefinition typeDefinition() throws Exception
    {
    	return new SchemaTypeDefinition(this.datatype(), new Name("HistoricalDataTable"));
    }
    
    public Name name() throws Exception
    {
    	return new Name("securityData");
    }
    
    public int numValues()
    {
    	return 1;
    }
    
    public int numElements()
    {
    	return this._numElements;
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
    	if(name.equals("fieldData") && !this._isSecurityError)
    		return this._elmFieldDataArray;
    	
    	else if(name.equals("security"))
    		return this._elmSecurityName;
    	
    	else if(name.equals("sequenceNumber"))
    		return this._elmSequenceNumber;
    	
    	else if(name.equals("fieldExceptions") && this._elmFieldExceptions != null)
    		return this._elmFieldExceptions;
    	
    	else if(name.equals("securityError") && this._isSecurityError) //this element doesn't exist if the security exists
    		return this._elmSecError;
    	
    	else
    		return super.getElement(name);
    }
    
    public boolean hasElement(String name)
    {
    	return this.hasElement(name, false);
    }
    
    public boolean hasElement(String name, boolean excludeNullElements)
    {
    	return 
    			(name.equals("fieldData") && !this._isSecurityError) ||
    			name.equals("security") ||
    			name.equals("sequenceNumber") ||
    			(name.equals("fieldExceptions") && this._elmFieldExceptions != null) ||
    			(name.equals("securityError") && this._isSecurityError);
    }
    
    public String getElementAsString(String name) throws Exception
    {
    	if(name == this._elmSecurityName.name().toString())
    		return this._elmSecurityName.getValueAsString();
    	else
    		return super.getElementAsString(name);
    }
    
    public int getElementAsInt32(String name) throws Exception
    {
    	if(name == this._elmSequenceNumber.name().toString())
    		return this._elmSecurityName.getValueAsInt32();
    	else
    		return super.getElementAsInt32(name);
    }
    
    protected StringBuilder prettyPrint(int tabIndent) throws Exception
    {
        String tabs = com.bemu.BEmu.types.IndentType.Indent(tabIndent);
        StringBuilder result = new StringBuilder();
        
        result.append(String.format("%s%s = {%s", tabs, this.name().toString(), System.getProperty("line.separator")));
        result.append(this._elmSecurityName.prettyPrint(tabIndent + 1));
        result.append(this._elmSequenceNumber.prettyPrint(tabIndent + 1));

        if (this._elmFieldExceptions != null)
            result.append(this._elmFieldExceptions.prettyPrint(tabIndent + 1));

        if (this._isSecurityError)
            result.append(this._elmSecError.prettyPrint(tabIndent + 1));
        else
            result.append(this._elmFieldDataArray.prettyPrint(tabIndent + 1));
        
        result.append(String.format("%s}%s", tabs, System.getProperty("line.separator")));

        return result;
    }
}
