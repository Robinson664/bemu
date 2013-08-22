//------------------------------------------------------------------------------
// <copyright project="BEmuJava" file="BEmu.Types.Rules.java" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

package com.bemu.BEmu.types;

public class Rules
{
	public static boolean isSecurityError(String security)
	{
		if(security == null)
			return true;
		else 
			return security.startsWith("Z") || security.startsWith("z"); 
	}
	
	public static boolean isBadField(String field)
	{
		if(field == null)
			return true;
		else 
			return field.startsWith("Z") || field.startsWith("z"); 
	}
}
