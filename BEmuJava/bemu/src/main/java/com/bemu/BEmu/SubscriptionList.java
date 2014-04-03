//------------------------------------------------------------------------------
// <copyright project="BEmuJava" file="BEmu.SubscriptionList.java" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

package com.bemu.BEmu;

import java.util.ArrayList;
import java.util.List;

public class SubscriptionList
{
	private final List<Subscription> _subscriptions;
	
	public SubscriptionList()
	{
		this._subscriptions = new ArrayList<Subscription>();
	}
	
	public void add(Subscription sub)
	{
		this._subscriptions.add(sub);
	}
	
	List<Subscription> list()
	{
		return this._subscriptions;
	}
	
	public Subscription remove(int index)
	{
		Subscription result = this._subscriptions.get(index);
		this._subscriptions.remove(index);
		return result;
	}
	
	public int size()
	{
		return this._subscriptions.size();
	}
	
	public Subscription get(int index)
	{
		return this._subscriptions.get(index);
	}
}
