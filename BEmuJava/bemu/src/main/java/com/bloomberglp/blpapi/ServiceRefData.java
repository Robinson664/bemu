//------------------------------------------------------------------------------
// <copyright project="BEmu_maven" file="/BEmu_maven/bemu/src/main/java/com/bloomberglp/blpapi/ServiceRefData.java" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

package com.bloomberglp.blpapi;

public class ServiceRefData extends Service
{
	public String name() { return "//blp/refdata"; }
	
	public Request createRequest(String operationName) throws Exception
	{
		if(operationName.equals("HistoricalDataRequest"))
			return new com.bloomberglp.blpapi.HistoricRequest();
		
		else if(operationName.equals("ReferenceDataRequest"))
			return new com.bloomberglp.blpapi.ReferenceRequest();
		
		else if(operationName.equals("IntradayBarRequest"))
			return new com.bloomberglp.blpapi.IntradayBarRequest(this);
		
		else if(operationName.equals("IntradayTickRequest"))
			return new com.bloomberglp.blpapi.IntradayTickRequest(this);
		
		else
			throw new Exception("not implemented. names are case-sensitive.");
	}
}
