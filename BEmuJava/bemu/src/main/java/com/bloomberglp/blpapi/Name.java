//------------------------------------------------------------------------------
//	This code comes from blpapi-3.6.1-0.jar
//------------------------------------------------------------------------------

package com.bloomberglp.blpapi;

import java.util.HashMap;

public final class Name
{
	private static HashMap<String, Name> s_globalNameTable = new HashMap<String, Name>();
	private static final Object s_globalNameTableLock = new Object();
	private final String d_name;
	private final Name d_impl;

	public static final Name NullName = new Name(0);
	
	public Name()
	{
		this.d_name = NullName.d_name;
		this.d_impl = NullName.d_impl;
	}
	
	private Name(int zero)
	{
		assert (zero == 0);
		this.d_name = null;
		this.d_impl = this;
	}
	
	public Name(String nameString)
	{
		Name localName = getName(nameString);
		this.d_impl = localName;
		this.d_name = this.d_impl.d_name;
	}
	
	private Name(String nameString, boolean unUsed)
	{
		this.d_name = nameString;
		this.d_impl = this;
		s_globalNameTable.put(nameString, this);
	}
	
	public static Name getName(String nameString)
	{
		if (nameString == null) {
			return NullName;
		}
		synchronized (s_globalNameTableLock)
		{
			Name localName = (Name)s_globalNameTable.get(nameString);
			if (localName == null) {
				localName = new Name(nameString, true);
			}
			return localName;
		}
	}
	
	public static Name findName(String nameString)
	{
		if (nameString == null) {
			return NullName;
		}
		synchronized (s_globalNameTableLock)
		{
			return (Name)s_globalNameTable.get(nameString);
		}
	}
	
	public static boolean hasName(String nameString)
	{
		if (nameString == null) {
			return true;
		}
		synchronized (s_globalNameTableLock)
		{
			return s_globalNameTable.containsKey(nameString);
		}
	}
	
	public boolean equals(Object other)
	{
		if ((other instanceof String)) {
			return this.d_name.equals(other);
		}
		if ((other instanceof Name)) {
			return ((Name)other).d_impl == this.d_impl;
		}
		return false;
	}
	
	public int hashCode()
	{
		if (this == this.d_impl) {
			return super.hashCode();
		}
		return this.d_impl.hashCode();
	}
	
	public String toString()
	{
		return this.d_name;
	}
	
}
