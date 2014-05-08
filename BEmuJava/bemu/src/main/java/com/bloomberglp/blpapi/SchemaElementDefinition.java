//------------------------------------------------------------------------------
// <copyright project="BEmu_maven" file="/BEmu_maven/bemu/src/main/java/com/bloomberglp/blpapi/SchemaElementDefinition.java" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

package com.bloomberglp.blpapi;

public class SchemaElementDefinition
{
	public static final int UNBOUNDED = -1;
	
	private SchemaElementDefinition() { }
	
	public void setUserData(Object arg0) throws Exception
	{
		throw new Exception("not implemented");
	}
	
	public Name name() throws Exception
	{
		throw new Exception("not implemented");
	}
	
	public int numAlternateNames() throws Exception
	{
		throw new Exception("not implemented");
	}
	
	public Name getAlternateName(int arg0) throws Exception
	{
		throw new Exception("not implemented");
	}
	
	public String description() throws Exception
	{
		throw new Exception("not implemented");
	}
	
	public Schema.Status status() throws Exception
	{
		throw new Exception("not implemented");
	}
	
	public SchemaTypeDefinition typeDefinition() throws Exception
	{
		throw new Exception("not implemented");
	}
	
	public int maxValues() throws Exception
	{
		throw new Exception("not implemented");
	}
	
	public ConstraintsList constraints() throws Exception
	{
		throw new Exception("not implemented");
	}
	
	public Object userData() throws Exception
	{
		throw new Exception("not implemented");
	}	
}
