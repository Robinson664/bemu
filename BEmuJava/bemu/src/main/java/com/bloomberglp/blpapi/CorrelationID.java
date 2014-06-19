//------------------------------------------------------------------------------
//  This code comes from blpapi-3.6.1-0.jar
//------------------------------------------------------------------------------

package com.bloomberglp.blpapi;

import java.util.concurrent.atomic.AtomicLong;

public final class CorrelationID
{
	private long bg;
	private Object bh;
	private static final AtomicLong bi = new AtomicLong(0L);
	private int bj;
	
	public CorrelationID(long paramLong)
	{
		this.bj = 3;
		this.bg = paramLong;
		this.bh = null;
	}
	
	public CorrelationID(Object paramObject)
	{
		if (paramObject == null)
		{
			throw new IllegalArgumentException("Null value");
		}
		this.bj = 7;
		this.bg = 0L;
		this.bh = paramObject;
	}
	
	public CorrelationID()
	{
		this.bj = 1;
		this.bg = bi.incrementAndGet();
		this.bh = null;
	}
	
	public CorrelationID(CorrelationID paramCorrelationID)
	{
		this.bj = paramCorrelationID.bj;
		this.bg = paramCorrelationID.bg;
		this.bh = paramCorrelationID.bh;
	}
	
	public long value()
	{
		if ((this.bj & 0x4) == 0)
		{
			return this.bg;
		}
		throw new IllegalStateException();
	}
	
	public Object object()
	{
		if ((this.bj & 0x4) != 0)
		{
			return this.bh;
		}
		throw new IllegalStateException();
	}
	
	public boolean isInternal()
	{
		return (this.bj & 0x2) == 0;
	}
	
	public boolean isObject()
	{
		return (this.bj & 0x4) != 0;
	}
	
	public boolean isValue()
	{
		return (this.bj & 0x4) == 0;
	}
	
	public boolean equals(Object paramObject)
	{
		if (this == paramObject)
		{
			return true;
		}
		if ((paramObject instanceof CorrelationID))
		{
			CorrelationID localCorrelationID = (CorrelationID)paramObject;
			if (this.bj != localCorrelationID.bj)
			{
				return false;
			}
			return this.bg == localCorrelationID.bg ? true : isObject() ? this.bh.equals(localCorrelationID.bh) : false;
		}
		return false;
	}
	
	public int hashCode()
	{
		return isValue() ? (int)(this.bg ^ this.bg >>> 32) : this.bh.hashCode();
	}
	
	public String toString()
	{
		switch (this.bj)
		{
			case 0: return "Uninitialized";
			case 1: return "Internal: " + this.bg;
			case 3: return "User: " + this.bg;
		}
		return "User: " + this.bh.toString();
	}
}