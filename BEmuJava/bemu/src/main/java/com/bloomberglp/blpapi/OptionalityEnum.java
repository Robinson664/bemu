//------------------------------------------------------------------------------
// <copyright project="BEmu_maven" file="/BEmu_maven/bemu/src/main/java/com/bloomberglp/blpapi/OptionalityEnum.java" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

package com.bloomberglp.blpapi;

public enum OptionalityEnum
{
	put('p'), call('c');
	
	private final char _putCall;
	
	OptionalityEnum(char ch)
	{
		this._putCall = ch;
	}
	
	public String toString()
	{
		return String.valueOf(this._putCall);
	}
}
