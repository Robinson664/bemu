//------------------------------------------------------------------------------
// <copyright project="BEmu_maven" file="/BEmu_maven/bemu/src/main/java/com/bloomberglp/blpapi/SchemaTypeDefinition.java" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

package com.bloomberglp.blpapi;

public class SchemaTypeDefinition
{
	public SchemaTypeDefinition(Schema.Datatype datatype) throws Exception
	{
	    this._datatype = datatype;
	    this._name = new Name(this._datatype.toString());
	}
	
	public SchemaTypeDefinition(Schema.Datatype datatype, Name name)
	{
	    this._datatype = datatype;
	    this._name = name;
	}
	
	private final Schema.Datatype _datatype;
	private final Name _name;
	
	public Name name()
	{
		return this._name;
	}
	
	public String ToString()
	{
	    return String.format("Type %s{1}", this._datatype.toString(), System.getProperty("line.separator"));
	}
}
