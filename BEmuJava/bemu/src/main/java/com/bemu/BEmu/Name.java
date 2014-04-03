//------------------------------------------------------------------------------
// <copyright project="BEmuJava" file="BEmu.Name.java" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

package com.bemu.BEmu;
import java.util.HashMap;
import java.util.Map;

public class Name
{	
	//private final boolean _isNull;
	private final String _name;
	private final static Map<String, Name> _globalNameTable = new HashMap<String, Name>();
	
	public static final Name NullName = new Name();
	
	public Name()
	{
	    this._name = null;
	    //this._isNull = true;
	}
	
	public Name(String nameString) throws Exception
	{
		if(nameString == null)
			throw new Exception("nameString can't be null");
		
		this._name = nameString;
		//this._isNull = false;
		
		if(!Name._globalNameTable.containsKey(nameString))
			Name._globalNameTable.put(nameString, this);
	}
	
	public static Name findName(String nameString)
	{
	    if(Name._globalNameTable.containsKey(nameString))
	    	return Name._globalNameTable.get(nameString);
	    else
	    	return null;
	}
	
	public static Name getName(String nameString) throws Exception
	{
	    if(Name._globalNameTable.containsKey(nameString))
	    	return Name._globalNameTable.get(nameString);
	    else
	    	return new Name(nameString);
	}
	
    public static boolean hasName(String nameString)
    {
        return Name._globalNameTable.containsKey(nameString);
    }
    
	public String toString()
	{
		return this._name;
	}
	
	public boolean equals(Object obj)
	{
		if(obj.getClass() == this.getClass())
			return ((Name)obj)._name.equals(this._name);
		else if(obj.getClass() == String.class)
			return this._name.equals((String)obj);
		else
			return false;
	}
}
