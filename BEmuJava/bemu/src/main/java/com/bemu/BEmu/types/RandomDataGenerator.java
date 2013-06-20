//------------------------------------------------------------------------------
// <copyright project="BEmuJava" file="BEmu.Types.RandomDataGenerator.java" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

package com.bemu.BEmu.types;

import java.text.DecimalFormat;
import java.util.Calendar;
import java.util.HashMap;
import java.util.List;
import java.util.Random;
import java.text.SimpleDateFormat;
import java.text.DateFormat;

import com.bemu.BEmu.DateTimeTypeEnum;
import com.bemu.BEmu.Datetime;
import com.bemu.BEmu.Element;
import com.bemu.BEmu.ReferenceDataRequest.OptionalityEnum;
import com.bemu.BEmu.ReferenceDataRequest.ElementReferenceArrayChainTickers;

public class RandomDataGenerator
{
	private static Random _rand = new Random(100);
	
	public static Object referenceDataFromFieldName(String fieldName, String security, boolean isOption, com.bemu.BEmu.ReferenceDataRequest.RequestReference rreq) throws Exception
	{
        String upper = fieldName.toUpperCase();
        Object result;
        
        if(upper.equals("CHAIN_TICKERS"))
        {
        	if(isOption)
        	{
        		result = null;
        	}
        	else
        	{
                int numPoints = 1;
                String dtExp = null;
                OptionalityEnum optionality = OptionalityEnum.call;
        		
                if(rreq.hasElement("overrides"))
                {
                	Element overrides = rreq.getElement("overrides");
                	for (int i = 0; i < overrides.numValues(); i++)
                	{
                        Element element = overrides.getValueAsElement(i);

                        String fieldId = element.getElement("fieldId").getValueAsString();
                        String value = element.getElement("value").getValueAsString();

                        String fieldUpper = fieldId.toUpperCase();
                        if(fieldUpper.equals("CHAIN_POINTS_OVRD"))
                        {
                        	numPoints = Integer.parseInt(value);
                        }
                        else if(fieldUpper.equals("CHAIN_EXP_DT_OVRD"))
                        {
                        	dtExp = value;
                        }
                        else if(fieldUpper.equals("CHAIN_PUT_CALL_TYPE_OVRD"))
                        {
                            if (value.toUpperCase() == "P")
                                optionality = OptionalityEnum.put;
                        }
                	}
                }
                
                ElementReferenceArrayChainTickers chain = new ElementReferenceArrayChainTickers(security, numPoints, dtExp, optionality);
                result = chain;
        	}
        }
        else if(upper.equals("TICKER"))
        {
        	int space = security.indexOf(' ');
        	result = security.substring(0, space);
        }
        else if(upper.equals("OPT_EXPIRE_DT"))
        {
        	if(security.endsWith("COMDTY") || security.endsWith("INDEX"))
        	{
        		Datetime dtResult = new Datetime();
        		dtResult.calendar().add(Calendar.MONTH, 3);
        		result = dtResult;
        	}
        	else if(isOption)
        	{
            	int space = security.lastIndexOf(' ');
        		String strDate = security.substring(space - 15);
        		strDate = strDate.substring(0, 6);
        		
        		DateFormat formatter = new SimpleDateFormat("yyMMdd");
                result = formatter.parse(strDate);
        	}
        	else
        		result = null;
        }
        else if(upper.contains("TRADEABLE_DT"))
        {
    		Datetime dtResult = new Datetime();
    		dtResult.calendar().add(Calendar.MONTH, 3);
    		result = dtResult;
        }
        else
        {
        	result = RandomDataGenerator.randomDouble();
        }
        
        return result;
	}
	
	public static Object marketDataFromFieldName(String fieldName)
	{
		Object result;
		String upper = fieldName.toUpperCase();
		
		Calendar dtNow = Calendar.getInstance();

		if(upper.contains("TIME"))
		{
			dtNow.add(Calendar.MINUTE, (int) (-1 * RandomDataGenerator.randomDouble() * 100));
			result = new Datetime(dtNow, DateTimeTypeEnum.time);
		}
		else if(upper.contains("DATE"))
		{
			dtNow.add(Calendar.DAY_OF_MONTH, (int) (-1 * RandomDataGenerator.randomDouble() * 100));
			result = new Datetime(dtNow, DateTimeTypeEnum.date);
		}
		else
			result = RandomDataGenerator.randomDouble();
		
		return result;
	}
	
    public static int intradayTickIntervalInMinutes()
    {
    	return RandomDataGenerator.randomInt(30 + 1); //between 1 and 30 minutes
    }
    
    public static com.bemu.BEmu.IntradayBarRequest.BarTickDataType generateBarData(Datetime date)
    {
        double first = RandomDataGenerator.randomDouble();
        double second = RandomDataGenerator.randomDouble();
        
        double high = Math.max(first, second);
        double low = Math.min(first, second);
        double open = RandomDataGenerator.randomDouble(low, high);
        double close = RandomDataGenerator.randomDouble(low, high);

        com.bemu.BEmu.IntradayBarRequest.BarTickDataType result = new com.bemu.BEmu.IntradayBarRequest.BarTickDataType();
        result.setDtTime(date);
        result.setVolume(RandomDataGenerator.randomInt(1000000));
        result.setValue(RandomDataGenerator.randomInt(1000000000));
        result.setNumEvents(RandomDataGenerator.randomInt(10000));
        result.setHigh(high);
        result.setLow(low);
        result.setOpen(open);
        result.setClose(close);

        return result;
    }
	
	public static HashMap<String, Object> getMarketDataFields(List<String> requestedFields)
	{
		HashMap<String, Object> result = new HashMap<String, Object>();
		while(result.size() == 0)
		{
			for(int i = 0; i < requestedFields.size(); i++)
			{				
				if(RandomDataGenerator.randomDouble(0, 1) < 0.25)
					result.put(requestedFields.get(i), RandomDataGenerator.marketDataFromFieldName(requestedFields.get(i)));
			}
		}
		
        //Market data responses contain extraneous data fields.  The user will not have requested them.
        //  To make this emulator more realistic, I'll add some extraneous fields of different types below.
        String[] extraDoubleFields = { "PREV_SES_LAST_PRICE", "PREV_CLOSE_VALUE_REALTIME", "PRICE_PREVIOUS_CLOSE_RT", "LOW", "LOW_TDY", "PRICE_LOW_RT" };
        String[] extraIntFields = { "PX_DISPLAY_FMT_MIN_#_DECIMALS_RT", "PX_DISPLAY_FMT_MAX_#_DECIMALS_RT", "NEWS_HEAT_STORY_FLOW_RT", "BID_SIZE_TDY", "BID_SIZE", "ASK_SIZE_TDY" };
        String[] extraTimeFields = { "SES_START", "LAST_UPDATE_BID_RT", "LAST_UPDATE_ASK_RT", "BID_ASK_TIME", "LAST_TRADE_RECEIVED_TIME_RT" };
        String[] extraDateFields = { "PRICE_52_WEEK_HIGH_DATE_RT", "PRICE_52_WEEK_LOW_DATE_RT", "PREV_TRADING_DT_REALTIME", "TRADING_DT_REALTIME" };
        String[] extraDateTimeFields = { "TRADE_UPDATE_STAMP_RT" };
        String[] extraStringFields = { "MKTDATA_EVENT_TYPE", "LAST_PX_LOCAL_EXCH_SOURCE_RT", "CLOSE_LOCAL_SOURCE_RT", "BID_PX_LOCAL_EXCH_SOURCE_RT", "HIGH_LOCAL_SOURCE_RT" };
        String[] extraBoolFields = { "IND_BID_FLAG", "IND_ASK_FLAG", "SHORT_SALE_THRESHOLD_REALTIME", "NO_SHORT_SELL_REALTIME", "RT_EXCH_TRADE_STATUS" };
		
        for(int i = 0; i < extraDoubleFields.length; i++) //random double fields
        {
        	if(!result.containsKey(extraDoubleFields[i]))
        		result.put(extraDoubleFields[i], RandomDataGenerator.randomDouble());
        }
        
        for(int i = 0; i < extraIntFields.length; i++) //random int fields
        {
        	if(!result.containsKey(extraIntFields[i]))
        		result.put(extraIntFields[i], RandomDataGenerator.randomInt(100));
        }
        
        for(int i = 0; i < extraTimeFields.length; i++) //random time fields
        {
        	if(!result.containsKey(extraTimeFields[i]))
        		result.put(extraTimeFields[i], RandomDataGenerator.randomTime());
        }
        
        for(int i = 0; i < extraDateFields.length; i++) //random date fields
        {
        	if(!result.containsKey(extraDateFields[i]))
        		result.put(extraDateFields[i], RandomDataGenerator.randomDate());
        }
        
        for(int i = 0; i < extraDateTimeFields.length; i++) //random datetime fields
        {
        	if(!result.containsKey(extraDateTimeFields[i]))
        		result.put(extraDateTimeFields[i], RandomDataGenerator.randomDatetime());
        }
        
        for(int i = 0; i < extraStringFields.length; i++) //random string fields
        {
        	if(!result.containsKey(extraStringFields[i]))
        		result.put(extraStringFields[i], RandomDataGenerator.randomString());
        }
        
        for(int i = 0; i < extraBoolFields.length; i++) //random boolean fields
        {
        	if(!result.containsKey(extraBoolFields[i]))
        		result.put(extraBoolFields[i], RandomDataGenerator.randomBoolean());
        }
        
		return result;
	}

	//I made it so that there is a 70% chance that a market data event will include a specific security
    public static boolean shouldIncludeQuote()
    {
        return RandomDataGenerator.randomDouble(0, 1) < 0.7;
    }
	
	public static long millisecondsBetweenMarketDataEvents()
	{
		return (long)(RandomDataGenerator.randomDouble(0, 1) * 2000 + 1000);
	}
	
    public static int intradayTickTradeSize()
    {
        return RandomDataGenerator.randomInt(5) * 100;
    }
	
    public static int strike()
    {
        return RandomDataGenerator.randomInt(20) * 5;
    }
	
    public static double randomDouble()
    {
        return RandomDataGenerator.randomDouble(0, 1) * 100d;
    }
	
	public static double randomDouble(double low, double high)
	{
		DecimalFormat twoDForm = new DecimalFormat("#.####");
		double result = RandomDataGenerator._rand.nextDouble() * (high - low) + low; 
		return Double.valueOf(twoDForm.format(result));
	}
	
	private static int randomInt(int max)
	{
		return RandomDataGenerator._rand.nextInt(max);
	}
	
    private static Datetime randomTime()
    {
    	Calendar calendar = Calendar.getInstance();
    	calendar.add(Calendar.SECOND, RandomDataGenerator._rand.nextInt(100));
    	Datetime result = new Datetime(calendar, DateTimeTypeEnum.date);
    	return result;
    }
	
    private static Datetime randomDate()
    {
    	Calendar calendar = Calendar.getInstance();
    	calendar.add(Calendar.DATE, RandomDataGenerator._rand.nextInt(100));
    	Datetime result = new Datetime(calendar, DateTimeTypeEnum.date);
    	return result;
    }
    
    private static Datetime randomDatetime()
    {
    	Calendar calendar = Calendar.getInstance();
    	calendar.add(Calendar.DATE, RandomDataGenerator._rand.nextInt(100));
    	calendar.add(Calendar.SECOND, RandomDataGenerator._rand.nextInt(100));
    	Datetime result = new Datetime(calendar, DateTimeTypeEnum.both);
    	return result;
    }
	
    private static boolean randomBoolean()
    {
        return RandomDataGenerator._rand.nextBoolean();
    }
	
    private static char randomChar()
    {
        return (char)('A' + RandomDataGenerator._rand.nextInt(24) - 1);
    }
    
    private static String randomString()
    {
        int length = RandomDataGenerator._rand.nextInt(10);
        StringBuilder result = new StringBuilder(length);
        for (int i = 0; i < length; i++)
        {
            result.append(RandomDataGenerator.randomChar());
        }
        return result.toString();
    }
    
}
