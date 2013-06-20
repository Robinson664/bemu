//------------------------------------------------------------------------------
// <copyright project="BEmuJava" file="BEmu.HistoricalDataRequest.RequestHistoric.java" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

package com.bemu.BEmu.HistoricalDataRequest;

import com.bemu.BEmu.Request;
import com.bemu.BEmu.Datetime;

import java.util.Calendar;
import java.util.Date;
import java.util.List;
import java.util.ArrayList;
import java.text.SimpleDateFormat;
import java.text.ParseException;

public class RequestHistoric extends Request
{
    private final RequestHistoricElementStringArray _securities, _fields;
    private RequestHistoricElementDate _dtStart, _dtEnd;

    private RequestHistoricElementBool _adjustmentNormalElement, _adjustmentAbnormalElement, _adjustmentSplitElement;

    private RequestHistoricElementInt _maxDataPointElement;

    private RequestHistoricElementString _periodicityAdjustmentElement, _periodicityElement, _overrideOptionsElement, _pricingOptionElement;

    private enum HistDataPeriodicityAdjustment { actual, calendar, fiscal }
    private HistDataPeriodicityAdjustment _periodicityAdjustment = HistDataPeriodicityAdjustment.actual;

    public enum HistDataPeriodicity { daily, weekly, monthly, quarterly, semi_annually, yearly }
    private HistDataPeriodicity _periodicity = HistDataPeriodicity.daily;

    public enum PricingOption { price, yield }
    @SuppressWarnings("unused")
	private PricingOption _pricingOption = PricingOption.price;

    public enum OverrideOptions { closingPrice, averagePrice }
    @SuppressWarnings("unused")
	private OverrideOptions _overrideOptions = OverrideOptions.closingPrice;
    
    public RequestHistoric()
    {
        this._dtStart = new RequestHistoricElementDate("startDate");
        this._dtEnd = new RequestHistoricElementDate("endDate");
        this._securities = new RequestHistoricElementStringArray("securities");
        this._fields = new RequestHistoricElementStringArray("fields");
    }
    
    List<String> securities()
    {
    	return this._securities.values();
    }
    
    List<String> fields()
    {
    	return this._fields.values();
    }
    
    Datetime dtStart()
    {
    	return this._dtStart.getDate();
    }
    
    Datetime dtEnd()
    {
    	return this._dtEnd.getDate();
    }
    
    List<Datetime> getDates()
    {
    	List<Datetime> result = this.getDatesBeforeMaxPoints();
    	List<Datetime> truncatedResult = new ArrayList<Datetime>();
    	
    	if(this._maxDataPointElement == null)
    		truncatedResult = result;
    	else
    	{
    		if(result.size() > this._maxDataPointElement.getInt())
    		{
    			for(int i = result.size() - this._maxDataPointElement.getInt(); i < result.size(); i++)
    			{
    				truncatedResult.add(result.get(i));
    			}
    		}
    		else
    			truncatedResult = result;
    	}
    	
    	return truncatedResult;
    }
    
    private List<Datetime> getDatesBeforeMaxPoints()
    {
        List<Datetime> result = new ArrayList<Datetime>();
        
        Datetime dtToday = new Datetime();
        
        Datetime dtStart;
        if(this._dtStart.getDate() == null)
        {
        	dtStart = new Datetime();
        	dtStart.calendar().add(Calendar.YEAR, -1); //com.bemu.Session.SendRequest assures that dtStart is not null
        }
        else
        	dtStart = new Datetime(this._dtStart.getDate());

        
        Datetime dtEnd;
        if(this._dtEnd.getDate() == null)
        {
        	dtEnd = new Datetime();
        	dtEnd.calendar().add(Calendar.DAY_OF_MONTH, -1);
        }
        else
        	dtEnd = new Datetime(this._dtEnd.getDate());
        
        if (this._periodicityAdjustment == HistDataPeriodicityAdjustment.fiscal)
        {
        	dtStart.calendar().set(Calendar.DAY_OF_MONTH, 0);
        }
        
        Datetime dtCurrent = dtStart;
        do
        {
        	result.add(new Datetime(dtCurrent));
        	
        	switch(this._periodicity)
        	{
	        	case daily:
	        		dtCurrent.calendar().add(Calendar.DAY_OF_MONTH, 1);
	        		break;
	        	case weekly:
	        		dtCurrent.calendar().add(Calendar.DAY_OF_MONTH, 7);
	        		break;
	        	case monthly:
	        		dtCurrent.calendar().add(Calendar.MONTH, 1);
	        		break;
	        	case quarterly:
	        		dtCurrent.calendar().add(Calendar.MONTH, 3);
	        		break;
	        	case semi_annually:
	        		dtCurrent.calendar().add(Calendar.MONTH, 6);
	        		break;
	        	case yearly:
	        		dtCurrent.calendar().add(Calendar.YEAR, 1);
	        		break;
        	}

        	if(dtCurrent.calendar().get(Calendar.DAY_OF_WEEK) == Calendar.SATURDAY)
        		dtCurrent.calendar().add(Calendar.DAY_OF_MONTH, 2);
        	else if(dtCurrent.calendar().get(Calendar.DAY_OF_WEEK) == Calendar.SUNDAY)
        		dtCurrent.calendar().add(Calendar.DAY_OF_MONTH, 1);
        	
        } while (dtCurrent.calendar().getTimeInMillis() <= dtEnd.calendar().getTimeInMillis() && dtCurrent.calendar().getTimeInMillis() <= dtToday.calendar().getTimeInMillis());
        
        return result;
    }
    
    public String toString()
    {
    	StringBuilder result = new StringBuilder();
    	result.append("HistoricalDataRequest = {" + System.getProperty("line.separator"));

    	if(this._securities.numValues() > 0)
    		result.append(this._securities.prettyPrint(1));

        if (this._fields.numValues() > 0)
            result.append(this._fields.prettyPrint(1));

        result.append(this._dtStart.prettyPrint(1));
        result.append(this._dtEnd.prettyPrint(1));
    	
        if (this._periodicityAdjustmentElement != null)
            result.append(this._periodicityAdjustmentElement.prettyPrint(1));

        if (this._periodicityElement != null)
            result.append(this._periodicityElement.prettyPrint(1));

        if (this._overrideOptionsElement != null)
            result.append(this._overrideOptionsElement.prettyPrint(1));

        if (this._pricingOptionElement != null)
            result.append(this._pricingOptionElement.prettyPrint(1));

        if (this._maxDataPointElement != null)
            result.append(this._maxDataPointElement.prettyPrint(1));

        if (this._adjustmentNormalElement != null)
            result.append(this._adjustmentNormalElement.prettyPrint(1));

        if (this._adjustmentAbnormalElement != null)
            result.append(this._adjustmentAbnormalElement.prettyPrint(1));

        if (this._adjustmentSplitElement != null)
            result.append(this._adjustmentSplitElement.prettyPrint(1));
        
        result.append("}");
        
        return result.toString();
    }

    public void append(String name, String elementValue) throws Exception
    {
    	String lower = name.toLowerCase();
    	if(lower.equals("securities"))
    		this._securities.addValue(elementValue);
    	
    	else if(lower.equals("fields"))
    		this._fields.addValue(elementValue);
    	
    	else
    		throw new Exception("not implemented");
    }
    
    public void set(String name, String elementValue) throws Exception
    {
    	SimpleDateFormat dateParse = new SimpleDateFormat("yyyyMMdd");
    	String lower = name.toLowerCase();

    	if(lower.equals("startdate"))
    	{
    		Datetime dtStart = RequestHistoric.TryParse(elementValue, dateParse);
    		if(dtStart == null)
    			throw new Exception("startDate must be in the format yyyyMMdd");
    		else
    			this._dtStart = new RequestHistoricElementDate("startDate", dtStart);
    	}
    	else if(lower.equals("enddate"))
    	{
    		Datetime dtEnd = RequestHistoric.TryParse(elementValue, dateParse);
    		if(dtEnd == null)
    			throw new Exception("endDate must be in the format yyyyMMdd");
    		else
    			this._dtEnd = new RequestHistoricElementDate("endDate", dtEnd);
    	}
    	else if(lower.equals("periodicityadjustment"))
    	{
    		String upper = elementValue.toUpperCase();
    		
    		if(upper.equals("CALENDAR"))
    			this._periodicityAdjustment = HistDataPeriodicityAdjustment.calendar;
    		
    		else if(upper.equals("FISCAL"))
    			this._periodicityAdjustment = HistDataPeriodicityAdjustment.fiscal;
    		
    		else if(upper.equals("ACTUAL"))
    			this._periodicityAdjustment = HistDataPeriodicityAdjustment.actual;
    		
    		else
    			throw new Exception("periodicityadjustment must be CALENDAR, FISCAL, or ACTUAL");

            this._periodicityAdjustmentElement = new RequestHistoricElementString("periodicityAdjustment", upper);
    	}
    	else if(lower.equals("periodicityselection"))
    	{
    		String upper = elementValue.toUpperCase();
    		
    		if(upper.equals("WEEKLY"))
    			this._periodicity = HistDataPeriodicity.weekly;
    		
    		else if(upper.equals("MONTHLY"))
    			this._periodicity = HistDataPeriodicity.monthly;
    		
    		else if(upper.equals("QUARTERLY"))
    			this._periodicity = HistDataPeriodicity.quarterly;
    		
    		else if(upper.equals("SEMI_ANNUALLY"))
    			this._periodicity = HistDataPeriodicity.semi_annually;
    		
    		else if(upper.equals("YEARLY"))
    			this._periodicity = HistDataPeriodicity.yearly;
    		
    		else if(upper.equals("DAILY"))
    			this._periodicity = HistDataPeriodicity.daily;
    		
    		else
    			throw new Exception("periodicityselection must be DAILY, WEEKLY, MONTHLY, QUARTERLY, SEMI_ANNUALLY, or YEARLY");

            this._periodicityElement = new RequestHistoricElementString("periodicitySelection", upper);
    	}
    	else if(lower.equals("pricingoption"))
    	{
    		String upper = elementValue.toUpperCase();

    		if(upper.equals("PRICING_OPTION_YIELD"))
    			this._pricingOption = PricingOption.yield;

    		else if(upper.equals("PRICING_OPTION_PRICE"))
    			this._pricingOption = PricingOption.price;
    		
    		else
    			throw new Exception("pricingoption must be either PRICING_OPTION_YIELD or PRICING_OPTION_PRICE");

            this._pricingOptionElement = new RequestHistoricElementString("pricingOption", upper);
    	}
    	else if(lower.equals("overrideoption"))
    	{
    		String upper = elementValue.toUpperCase();
    		
    		if(upper.equals("OVERRIDE_OPTION_GPA"))
                this._overrideOptions = OverrideOptions.averagePrice;
    		
    		else if(upper.equals("OVERRIDE_OPTION_CLOSE"))
                this._overrideOptions = OverrideOptions.closingPrice;
    		
    		else
    			throw new Exception("overrideoption must be either OVERRIDE_OPTION_GPA or OVERRIDE_OPTION_CLOSE");

            this._overrideOptionsElement = new RequestHistoricElementString("overrideOption", upper);
    	}    	
    }
    
    public void set(String name, boolean elementValue) throws Exception
    {
    	String lower = name.toLowerCase();

    	if(lower.equals("adjustmentnormal"))
            this._adjustmentNormalElement = new RequestHistoricElementBool("adjustmentNormal", elementValue);
    	
    	else if(lower.equals("adjustmentabnormal"))
            this._adjustmentAbnormalElement = new RequestHistoricElementBool("adjustmentAbnormal", elementValue);

    	else if(lower.equals("adjustmentsplit"))
            this._adjustmentSplitElement = new RequestHistoricElementBool("adjustmentSplit", elementValue);
		
		else
			throw new Exception("not implemented");    	
    }
    
    public void set(String name, int elementValue) throws Exception
    {
    	String lower = name.toLowerCase();

    	if(lower.equals("maxdatapoints"))
            this._maxDataPointElement = new RequestHistoricElementInt("maxDataPoints", elementValue);

		else
			throw new Exception("not implemented");
    }
    
    
    //either returns a date, or null if the string is not parse-able
    private static Datetime TryParse(String arg, SimpleDateFormat dateParse)
    {
    	try
    	{
    		Date date = dateParse.parse(arg);
    		Calendar cal = Calendar.getInstance();
    		cal.setTime(date);
    		Datetime result = new Datetime(cal);
    		return result;
    	}
    	catch(ParseException e)
    	{
    		return null;
    	}
    }
    
    
    
}
