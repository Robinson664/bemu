//------------------------------------------------------------------------------
// <copyright project="BEmuJava" file="BEmu.Name.java" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

package BEmu;

public class Name {
	private String _name;
	
	public Name(String nameString)
	{
		this._name = nameString;
	}
	
	public String toString()
	{
		return this._name;
	}
	
	public boolean Equals(Object obj)
	{
		if(obj.getClass() == this.getClass())
			return ((Name)obj)._name.equals(this._name);
		else
			return false;
	}
}
