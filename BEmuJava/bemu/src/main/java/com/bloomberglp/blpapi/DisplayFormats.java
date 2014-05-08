//------------------------------------------------------------------------------
// <copyright project="BEmu_maven" file="/BEmu_maven/bemu/src/main/java/com/bloomberglp/blpapi/DisplayFormats.java" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

package com.bloomberglp.blpapi;
import com.bloomberglp.blpapi.Datetime;

import java.text.DateFormat;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Calendar;
import java.util.Date;

public class DisplayFormats
{
	public static String FormatNumberNoSeparators(double dbl, int numDecimals)
	{
		String result = String.format("%." + numDecimals + "f", dbl);
		return result;
	}

	public static String FormatNumberNoSeparators(double dbl)
	{
		String result = DisplayFormats.FormatNumberNoSeparators(dbl, 0);
		return result;
	}
	
	public static String FormatDate(Datetime date) //default date
	{
		SimpleDateFormat s = new SimpleDateFormat("yyyy-MM-dd"); //mkt data has time zone information, but the other requests don't
		String result = s.format(date.calendar().getTime());
		return result;
	}
	
	public static String FormatTimeZone(Datetime time) //default time
	{
		SimpleDateFormat s = new SimpleDateFormat("HH:mm:ss.SSSZ");
		String result = s.format(time.calendar().getTime());
		return result;
	}
	
	public static String FormatDatetimeZone(Datetime datetime) //default time
	{
		SimpleDateFormat s = new SimpleDateFormat("yyyy-MM-dd'T'HH:mm:ss.SSSZ");
		String result = s.format(datetime.calendar().getTime());
		return result;
	}
	
	public static String MarketDataRequests_FormatDateZone(Datetime date)
	{
		SimpleDateFormat s = new SimpleDateFormat("yyyy-MM-ddZ"); //mkt data has time zone information, but the other requests don't
		String result = s.format(date.calendar().getTime());
		return result;
	}
	
	public static String HistRef_FormatDate(Datetime date)
	{
		SimpleDateFormat s = new SimpleDateFormat("yyyy-MM-dd"); //mkt data has time zone information, but the other requests don't
		String result = s.format(date.calendar().getTime());
		return result;
	}
	
	public static Datetime HistRef_TryParseInput(String str) //if the parse fails, the return is null
	{
		DateFormat df = new SimpleDateFormat("yyyyMMdd");

		try
		{
			Date date = df.parse(str);
			Calendar c = Calendar.getInstance();
			c.setTime(date);
			Datetime result = new Datetime(c);
			return result;
		}
		catch (ParseException e)
		{
			return null;
		}
	}
	
	public static String Intraday_FormatDatetime(Datetime datetime) //IntradayBar, IntradayTick
	{
		SimpleDateFormat s = new SimpleDateFormat("yyyy-MM-dd'T'HH:mm:ss.SSS");
		String result = s.format(datetime.calendar().getTime());
		return result;
	}
}
