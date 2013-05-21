//------------------------------------------------------------------------------
// <copyright project="BEmuJava" file="BEmu.Service.java" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

package com.bemu.BEmu;

import com.bemu.BEmu.Request;

public abstract class Service
{
	public abstract Request createRequest(String operationName) throws Exception;
	public abstract String name();
}
