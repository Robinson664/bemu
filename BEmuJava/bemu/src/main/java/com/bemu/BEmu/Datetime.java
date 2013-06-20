//------------------------------------------------------------------------------
// <copyright project="BEmuJava" file="BEmu.Datetime.java" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

package com.bemu.BEmu;

import java.util.Calendar;
import java.text.SimpleDateFormat;

public class Datetime {
	
	private Calendar _instance;
	private DateTimeTypeEnum _dateTimeType;
	
	public Datetime()
	{
		this._instance = Calendar.getInstance();
		this._dateTimeType = DateTimeTypeEnum.neither;
	}
	
	public Datetime(Datetime arg)
	{
		this(arg._instance); //call Datetime(Calendar arg)	
		this._dateTimeType = arg._dateTimeType;
	}
	
	public Datetime(Calendar arg)
	{
		this._instance = Calendar.getInstance();

		this._instance.set(Calendar.YEAR, arg.get(Calendar.YEAR));
		this._instance.set(Calendar.MONTH, arg.get(Calendar.MONTH));
		this._instance.set(Calendar.DAY_OF_MONTH, arg.get(Calendar.DAY_OF_MONTH));
		this._instance.set(Calendar.HOUR_OF_DAY, arg.get(Calendar.HOUR_OF_DAY));
		this._instance.set(Calendar.MINUTE, arg.get(Calendar.MINUTE));
		this._instance.set(Calendar.SECOND, arg.get(Calendar.SECOND));
		this._instance.set(Calendar.MILLISECOND, arg.get(Calendar.MILLISECOND));
		
		this._dateTimeType = DateTimeTypeEnum.both;
	}
	
	public Datetime(Calendar arg, DateTimeTypeEnum dt)
	{
		this(arg);
		this._dateTimeType = dt;
	}
	
	public Datetime(Datetime arg, DateTimeTypeEnum dt)
	{
		this(arg._instance); //call Datetime(Calendar arg)	
		this._dateTimeType = dt;
	}
	
	public Datetime(int year, int month, int dayOfMonth)
	{
		this.setDate(year, month, dayOfMonth);
	}
	
	public Datetime(int hour, int minute, int second, int milliSecond)
	{
		this.setTime(hour, minute, second, milliSecond);
	}
	
	public Datetime(int year, int month, int dayOfMonth, int hour, int minute, int second, int milliSecond)
	{
		this.setDatetime(year, month, dayOfMonth, hour, minute, second, milliSecond);
	}
	
	//Don't use this.  It's not in the actual Bloomberg code.
	public DateTimeTypeEnum DateTimeType()
	{
		return this._dateTimeType;
	}
	
	public int dayOfMonth()
	{
		return this._instance.get(Calendar.DAY_OF_MONTH);
	}
	
	public int hour()
	{
		return this._instance.get(Calendar.HOUR_OF_DAY);
	}
	
	public int millisecond()
	{
		return this._instance.get(Calendar.MILLISECOND);
	}
	
	public int minute()
	{
		return this._instance.get(Calendar.MINUTE);
	}
	
	public int month()
	{
		return this._instance.get(Calendar.MONTH) + 1; //Java months are 0-based whereas BB months are 1-based
	}
	
	public int second()
	{
		return this._instance.get(Calendar.SECOND);
	}
	
	public int year()
	{
		return this._instance.get(Calendar.YEAR);
	}
	
	public Calendar calendar()
	{
		return this._instance;
	}
	
	public void setDayOfMonth(int dayOfMonth)
	{
		this._instance.set(Calendar.DAY_OF_MONTH, dayOfMonth);
	}
	
	public void setHour(int hour)
	{
		this._instance.set(Calendar.HOUR_OF_DAY, hour);
	}
	
	public void setMillisecond(int milliSecond)
	{
		this._instance.set(Calendar.MILLISECOND, milliSecond);
	}
	
	public void setMinute(int minute)
	{
		this._instance.set(Calendar.MINUTE, minute);
	}
	
	public void setMonth(int month)
	{
		this._instance.set(Calendar.MONTH, month - 1); //Java months are 0-based whereas BB months are 1-based
	}
	
	public void setSecond(int second)
	{
		this._instance.set(Calendar.SECOND, second);
	}
	
	public void setYear(int year)
	{
		this._instance.set(Calendar.YEAR, year);
	}
	
	public void setDate(int year, int month, int dayOfMonth)
	{
		this._instance = Calendar.getInstance();
		this._instance.set(year, month - 1, dayOfMonth); //Java months are 0-based whereas BB months are 1-based
		this._dateTimeType = DateTimeTypeEnum.date;
	}
	
	public void setDatetime(int year, int month, int dayOfMonth, int hour, int minute, int second, int milliSecond)
	{
		this._instance = Calendar.getInstance();

		this._instance.set(Calendar.YEAR, year);
		this._instance.set(Calendar.MONTH, month - 1); //Java months are 0-based whereas BB months are 1-based
		this._instance.set(Calendar.DAY_OF_MONTH, dayOfMonth);
		this._instance.set(Calendar.HOUR_OF_DAY, hour);
		this._instance.set(Calendar.MINUTE, minute);
		this._instance.set(Calendar.SECOND, second);
		this._instance.set(Calendar.MILLISECOND, milliSecond);
		
		this._dateTimeType = DateTimeTypeEnum.both;
	}
	
	public void setTime(int hour, int minute, int second, int milliSecond)
	{
		this._instance = Calendar.getInstance();
		
		this._instance.set(Calendar.HOUR_OF_DAY, hour);
		this._instance.set(Calendar.MINUTE, minute);
		this._instance.set(Calendar.SECOND, second);
		this._instance.set(Calendar.MILLISECOND, milliSecond);
		
		this._dateTimeType = DateTimeTypeEnum.time;
	}
	
	public boolean equals(Object oarg)
	{
		if(oarg.getClass() == this.getClass())
		{
			Datetime arg = (Datetime)oarg;
			return this._instance.getTimeInMillis() == arg._instance.getTimeInMillis() 
					&& this._dateTimeType == arg._dateTimeType;
		}
		else
			return false;
	}
	
	public String toString()
	{
		SimpleDateFormat s;
		switch(this._dateTimeType)
		{
			case date:
				s = new SimpleDateFormat("yyyy-MM-dd");
				return s.format(this._instance.getTime());
			case time:
				s = new SimpleDateFormat("hh:mm:ss.SSS");
				return s.format(this._instance.getTime());
			case both:
				s = new SimpleDateFormat("yyyy-MM-dd'T'hh:mm:ss.SSS");
				return s.format(this._instance.getTime());
			case neither:
			default:
				return "Datetime._neither not supported";
		}
	}
}

