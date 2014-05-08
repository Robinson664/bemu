//------------------------------------------------------------------------------
// <copyright project="BEmu_maven" file="/BEmu_maven/bemu/src/main/java/com/bloomberglp/blpapi/SessionOptions.java" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

package com.bloomberglp.blpapi;

public class SessionOptions
{
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
