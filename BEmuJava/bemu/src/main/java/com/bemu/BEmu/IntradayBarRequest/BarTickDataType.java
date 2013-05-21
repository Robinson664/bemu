//------------------------------------------------------------------------------
// <copyright project="BEmuJava" file="BEmu.IntradayBarRequest.BarTickDataType.java" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

package com.bemu.BEmu.IntradayBarRequest;

import com.bemu.BEmu.Datetime;

public class BarTickDataType
{	
	private Datetime _dtTime;
	public Datetime getDtTime() { return this._dtTime; }
	public void setDtTime(Datetime arg) { this._dtTime = arg; }

	private double _open;
	public double getOpen() { return this._open; }
	public void setOpen(double arg) { this._open = arg; }

	private double _high;
	public double getHigh() { return this._high; }
	public void setHigh(double arg) { this._high = arg; }

	private double _low;
	public double getLow() { return this._low; }
	public void setLow(double arg) { this._low = arg; }

	private double _close;
	public double getClose() { return this._close; }
	public void setClose(double arg) { this._close = arg; }

	private long _volume;
	public long getVolume() { return this._volume; }
	public void setVolume(long arg) { this._volume = arg; }

	private int _numEvents;
	public int getNumEvents() { return this._numEvents; }
	public void setNumEvents(int arg) { this._numEvents = arg; }
	
	private double _value;
	public double getValue() { return this._value; }
	public void setValue(double arg) { this._value = arg; }
}
