package com.bemu.BEmu;

public interface EventHandler
{
	public abstract void processEvent(Event evt, Session session);
}
