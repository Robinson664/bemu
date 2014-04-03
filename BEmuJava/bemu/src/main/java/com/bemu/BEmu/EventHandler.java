//------------------------------------------------------------------------------
// <copyright project="BEmuJava" file="BEmu.EventHandler.java" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

package com.bemu.BEmu;

public interface EventHandler
{
	public abstract void processEvent(Event evt, Session session);
}
