//------------------------------------------------------------------------------
// <copyright project="BEmuJava" file="BEmu.IntradayTickRequest.MessageIntradayTick.java" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

package BEmu.IntradayTickRequest;

import BEmu.Element;
import BEmu.Message;
import BEmu.Service;
import BEmu.Name;
import BEmu.Datetime;
import BEmu.CorrelationID;

import java.util.Map;

public class MessageIntradayTick extends Message
{
	private final ElementIntradayTickDataParent _parent;
	
    MessageIntradayTick(CorrelationID corr, Map<Datetime, Tuple3<String, Double, Integer>> ticks, boolean includeConditionCodes, Service service)
    {
    	super(new Name("IntradayTickResponse"), corr, service);
        this._parent = new ElementIntradayTickDataParent(ticks, includeConditionCodes);
    }
    
	public Element getElement(String name) throws Exception
	{
		if(name.toLowerCase().equals(this._parent.name().toString().toLowerCase()))
			return this._parent;
		else
			throw new Exception("not implemented");
	}
	
	ElementIntradayTickDataParent firstElement()
	{
		return this._parent;
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
        result.append("IntradayTickResponse (choice) = {" + System.getProperty("line.separator"));
        result.append(this._parent.prettyPrint(1));
        result.append("}");

        return result.toString();
    }
}
