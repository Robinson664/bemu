//------------------------------------------------------------------------------
// <copyright project="BEmu_maven" file="/BEmu_maven/bemu/src/main/java/com/bloomberglp/blpapi/HistoricMessage.java" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

package com.bloomberglp.blpapi;

import com.bloomberglp.blpapi.Element;
import com.bloomberglp.blpapi.Name;
import com.bloomberglp.blpapi.Message;
import com.bloomberglp.blpapi.CorrelationID;
import com.bloomberglp.blpapi.Datetime;
import java.util.Map;
import java.util.List;

public class HistoricMessage extends Message
{
    private final HistoricElementSecurityData _security;
    
    HistoricMessage(CorrelationID corr, String securityName, List<String> badFields, Map<Datetime, Map<String, Object>> fieldData, int sequenceNumber) throws Exception
    {
    	super(new Name("HistoricalDataResponse"), corr, null);
    	this._security = new HistoricElementSecurityData(securityName, badFields, fieldData, sequenceNumber);
    }
    
    HistoricElementSecurityData security()
    {
    	return this._security;
    }
    
	public Element getElement(String name) throws Exception
	{
		if(name.equals(this._security.name().toString()))
			return this._security;
		else
			throw new Exception("not implemented. case-sensitive.");
	}
    
    public String toString()
    {
        StringBuilder result = new StringBuilder();
        
        result.append("HistoricalDataResponse (choice) = {" + System.getProperty("line.separator"));
        try {
			result.append(this._security.prettyPrint(1));
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
        result.append("}");

        return result.toString();
    }
}
