//------------------------------------------------------------------------------
// <copyright project="BEmuJava" file="BEmu.SessionOptions.java" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

package com.bemu.BEmu;

public class SessionOptions {
	@SuppressWarnings("unused")
	private String _serverhost;
	public void setServerHost(String host)
	{
		this._serverhost = host;
	}
	
	@SuppressWarnings("unused")
	private int _serverPort;
	public void setServerPort(int port)
	{
		this._serverPort = port;
	}
}
