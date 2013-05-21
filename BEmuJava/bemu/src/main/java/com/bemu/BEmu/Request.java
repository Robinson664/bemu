//------------------------------------------------------------------------------
// <copyright project="BEmuJava" file="BEmu.Request.java" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

package com.bemu.BEmu;

import com.bemu.BEmu.CorrelationID;
import com.bemu.BEmu.Element;

public abstract class Request 
{
	private CorrelationID _correlationId;
	
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
