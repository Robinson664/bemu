//------------------------------------------------------------------------------
// <copyright project="BEmuJava" file="BEmu.MarketDataRequest.MessageMarketServiceStatus.java" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

package com.bemu.BEmu.MarketDataRequest;

import com.bemu.BEmu.Message;
import com.bemu.BEmu.CorrelationID;
import com.bemu.BEmu.Name;
import com.bemu.BEmu.Element;

public class MessageMarketServiceStatus extends Message
{
    private final ElementMarketString _serviceName;

    MessageMarketServiceStatus(CorrelationID corr) throws Exception
    {
    	super(new Name("ServiceOpened"), corr, null);
    	
        this._serviceName = new ElementMarketString("serviceName", "//blp/mktdata");
    }
    
	public int numElements()
	{
		return 1;
	}
    
	public String topicName()
	{
		return "";
	}
	
	public boolean hasElement(String name, boolean excludeNullElements) throws Exception
	{
		return this._serviceName.name().toString().equals(name);
	}
	
	public Element getElement(String name) throws Exception
	{
		if(name.equals(this._serviceName.name().toString()))
			return this._serviceName;
		
		else
			return super.getElement(name);
	}
	
    public String toString()
    {
        StringBuilder result = new StringBuilder();
        result.append(String.format("%s = {%s", this.messageType().toString(), System.getProperty("line.separator")));
        try
        {
			result.append(this._serviceName.prettyPrint(1));
		}
        catch (Exception e) { }
        result.append("}" + System.getProperty("line.separator"));

        return result.toString();
    }

}
