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
}
