//------------------------------------------------------------------------------
// <copyright project="BEmu_maven" file="/BEmu_maven/bemu/src/main/java/com/bloomberglp/blpapi/Request.java" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

package com.bloomberglp.blpapi;

import com.bloomberglp.blpapi.CorrelationID;
import com.bloomberglp.blpapi.Element;

public abstract class Request 
{
	protected Request()
	{
		this._operation = new Operation();
	}
	
	private CorrelationID _correlationId;
	private final Operation _operation;
	
	public Operation operation()
	{
		return this._operation;
	}
	
	public Element asElement() throws Exception
	{
		throw new Exception("not implemented");
	}
	
	public CorrelationID correlationId()
	{
		return this._correlationId;
	}
	
	void correlationId(CorrelationID corr)
	{
		this._correlationId = corr;
	}

    public void append(String name, String elementValue) throws Exception
    {
        throw new Exception("BEmu.Request.Append: Append is not implemented");
    }
    
    public void set(String name, String elementValue) throws Exception
    {
        throw new Exception("BEmu.Request.Set: string is not implemented");
    }
    
    public void set(String name, boolean elementValue) throws Exception
    {
        throw new Exception("BEmu.Request.Set: bool is not implemented");
    }

    public void set(String name, int elementValue) throws Exception
    {
        throw new Exception("BEmu.Request.Set: int is not implemented");
    }

    public void set(String name, Datetime elementValue) throws Exception
    {
        throw new Exception("BEmu.Request.Set: Datetime is not implemented");
    }

    public void set(Name name, String elementValue) throws Exception
    {
        this.set(name.toString(), elementValue);
    }

    public void set(Name name, boolean elementValue) throws Exception
    {
        this.set(name.toString(), elementValue);
    }

    public void set(Name name, int elementValue) throws Exception
    {
        this.set(name.toString(), elementValue);
    }

    public void set(Name name, Datetime elementValue) throws Exception
    {
        this.set(name.toString(), elementValue);
    }

    public Element getElement(Name name) throws Exception
    {
        return this.getElement(name.toString());
    }

    public Element getElement(String name) throws Exception
    {
    	throw new Exception("BEmu.Request.this[]: by string is not implemented");
    }

    public boolean hasElement(String name) throws Exception
    {
        throw new Exception("BEmu.Request.HasElement: string is not implemented");
    }
}
