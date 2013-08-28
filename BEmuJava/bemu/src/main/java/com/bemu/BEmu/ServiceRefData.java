//------------------------------------------------------------------------------
// <copyright project="BEmuJava" file="BEmu.ServiceRefData.java" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

package com.bemu.BEmu;

public class ServiceRefData extends Service
{
	public String name() { return "//blp/refdata"; }
	
	public Request createRequest(String operationName) throws Exception
	{
		if(operationName.equals("HistoricalDataRequest"))
			return new com.bemu.BEmu.HistoricalDataRequest.RequestHistoric();
		
		else if(operationName.equals("ReferenceDataRequest"))
			return new com.bemu.BEmu.ReferenceDataRequest.RequestReference();
		
		else if(operationName.equals("IntradayBarRequest"))
			return new com.bemu.BEmu.IntradayBarRequest.RequestIntradayBar(this);
		
		else if(operationName.equals("IntradayTickRequest"))
			return new com.bemu.BEmu.IntradayTickRequest.RequestIntradayTick(this);
		
		else
			throw new Exception("not implemented. names are case-sensitive.");
	}
}
