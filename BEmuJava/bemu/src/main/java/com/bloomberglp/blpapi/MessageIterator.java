//------------------------------------------------------------------------------
// <copyright project="BEmu_maven" file="/BEmu_maven/bemu/src/main/java/com/bloomberglp/blpapi/MessageIterator.java" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

package com.bloomberglp.blpapi;

import java.util.List;
import java.util.Iterator;

public class MessageIterator implements Iterator<Message> {

	private Iterator<Message> _iter;
	
	public MessageIterator(List<Message> list)
	{
		this._iter = list.iterator();
	}
	
	public boolean hasNext()
	{
		return this._iter.hasNext();
	}
	
	public Message next()
	{
		return this._iter.next();
	}
	
	public void remove()
	{
		this._iter.remove();
	}
}
