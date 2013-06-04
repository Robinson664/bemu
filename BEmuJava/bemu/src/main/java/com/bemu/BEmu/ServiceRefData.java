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
		String lower = operationName.toLowerCase();
		
		if(lower.equals("historicaldatarequest"))
			return new com.bemu.BEmu.HistoricalDataRequest.RequestHistoric();
		
		else if(lower.equals("referencedatarequest"))
			return new com.bemu.BEmu.ReferenceDataRequest.RequestReference();
		
		else if(lower.equals("intradaybarrequest"))
			return new com.bemu.BEmu.IntradayBarRequest.RequestIntradayBar(this);
		
		else if(lower.equals("intradaytickrequest"))
			return new com.bemu.BEmu.IntradayTickRequest.RequestIntradayTick(this);
		
		else
			throw new Exception("not implemented");
	}
}
