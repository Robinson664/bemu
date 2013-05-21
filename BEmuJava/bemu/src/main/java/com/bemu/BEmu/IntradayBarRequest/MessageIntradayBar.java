//------------------------------------------------------------------------------
// <copyright project="BEmuJava" file="BEmu.IntradayBarRequest.MessageIntradayBar.java" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

package com.bemu.BEmu.IntradayBarRequest;

import com.bemu.BEmu.Element;
import com.bemu.BEmu.Name;
import com.bemu.BEmu.Service;
import com.bemu.BEmu.Message;
import com.bemu.BEmu.CorrelationID;
import java.lang.StringBuilder;
import java.util.List;

public class MessageIntradayBar extends Message
{
	private final ElementBarData _parent;
	
	public MessageIntradayBar(CorrelationID corr, List<BarTickDataType> bars, Service service)
	{
		super(new Name("IntradayBarResponse"), corr, service);
		this._parent = new ElementBarData(bars);
	}
	
	public Element getElement(String name) throws Exception
	{
		if(name.toLowerCase().equals(this._parent.name().toString().toLowerCase()))
			return this._parent;
		else
			throw new Exception("not implemented");
	}
	
	public String topicName()
	{
		return "";
	}
	
	public int numElements()
	{
		return 1;
	}
	
    public String toString()
    {
        StringBuilder result = new StringBuilder();
        result.append("IntradayBarResponse (choice) = {" + System.getProperty("line.separator"));
        result.append(this._parent.prettyPrint(1));
        result.append("}");

        return result.toString();
    }
	
}
