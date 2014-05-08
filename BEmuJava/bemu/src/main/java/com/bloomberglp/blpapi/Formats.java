//------------------------------------------------------------------------------
// <copyright project="BEmu_maven" file="/BEmu_maven/bemu/src/main/java/com/bloomberglp/blpapi/Formats.java" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

package com.bloomberglp.blpapi;

import java.text.DecimalFormat;

public class Formats
{
	private static DecimalFormat _dec2NoCommas = new DecimalFormat("#.##");
	
	public static String formatDouble2NoCommas(double arg)
	{
		return Formats._dec2NoCommas.format(arg); 
	}
}
