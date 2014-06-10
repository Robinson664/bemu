//------------------------------------------------------------------------------
// <copyright project="BEmu_maven" file="/BEmu_maven/bemu/src/main/java/com/bloomberglp/blpapi/HistoricRequest.java" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

package com.bloomberglp.blpapi;

import com.bloomberglp.blpapi.Request;
import com.bloomberglp.blpapi.Datetime;

import java.util.Calendar;
import java.util.List;
import java.util.ArrayList;

public class HistoricRequest extends Request
{
    private final HistoricRequestElementStringArray _securities, _fields;
    private HistoricRequestElementDate _dtStart, _dtEnd;

    private HistoricRequestElementBool _adjustmentNormalElement, _adjustmentAbnormalElement, _adjustmentSplitElement;

    private HistoricRequestElementInt _maxDataPointElement;

    private HistoricRequestElementString _periodicityAdjustmentElement, _periodicityElement, _overrideOptionsElement, _pricingOptionElement;

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
    
    public HistoricRequest()
    {
        this._dtStart = new HistoricRequestElementDate("startDate");
        this._dtEnd = new HistoricRequestElementDate("endDate");
        this._securities = new HistoricRequestElementStringArray("securities");
        this._fields = new HistoricRequestElementStringArray("fields");
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

        Element[] elms = { this._dtStart, this._dtEnd, this._periodicityAdjustmentElement, this._periodicityElement, 
        		this._overrideOptionsElement, this._pricingOptionElement, this._maxDataPointElement, this._adjustmentNormalElement, 
        		this._adjustmentAbnormalElement, this._adjustmentSplitElement };
        
        for (int i = 0; i < elms.length; i++)
        {
            Element current = elms[i];

            if (current != null)
            {
				try { result.append(current.prettyPrint(1)); }
            	catch (Exception e) { }
            }
        }
        
        result.append("}" + System.getProperty("line.separator"));
        return result.toString();
    }

    public void append(String name, String elementValue) throws Exception
    {
    	if(name.equals("securities"))
    		this._securities.appendValue(elementValue);
    	
    	else if(name.equals("fields"))
    		this._fields.appendValue(elementValue);
    	
    	else
    		throw new Exception("not implemented. names are case-sensitive");
    }
    
    public void set(String name, String elementValue) throws Exception
    {
    	if(name.equals("startDate"))
    	{
    		Datetime dtStart = com.bloomberglp.blpapi.DisplayFormats.HistRef_TryParseInput(elementValue);
    		if(dtStart == null)
    			throw new Exception("startDate must be in the format yyyyMMdd");
    		else
    			this._dtStart = new HistoricRequestElementDate("startDate", dtStart);
    	}
    	else if(name.equals("endDate"))
    	{
    		Datetime dtEnd = com.bloomberglp.blpapi.DisplayFormats.HistRef_TryParseInput(elementValue);
    		if(dtEnd == null)
    			throw new Exception("endDate must be in the format yyyyMMdd");
    		else
    			this._dtEnd = new HistoricRequestElementDate("endDate", dtEnd);
    	}
    	else if(name.equals("periodicityAdjustment"))
    	{
    		if(elementValue.equals("CALENDAR"))
    			this._periodicityAdjustment = HistDataPeriodicityAdjustment.calendar;
    		
    		else if(elementValue.equals("FISCAL"))
    			this._periodicityAdjustment = HistDataPeriodicityAdjustment.fiscal;
    		
    		else if(elementValue.equals("ACTUAL"))
    			this._periodicityAdjustment = HistDataPeriodicityAdjustment.actual;
    		
    		else
    			throw new Exception("periodicityadjustment must be CALENDAR, FISCAL, or ACTUAL. Values are case-sensitive.");

            this._periodicityAdjustmentElement = new HistoricRequestElementString("periodicityAdjustment", elementValue);
    	}
    	else if(name.equals("periodicitySelection"))
    	{
    		if(elementValue.equals("WEEKLY"))
    			this._periodicity = HistDataPeriodicity.weekly;
    		
    		else if(elementValue.equals("MONTHLY"))
    			this._periodicity = HistDataPeriodicity.monthly;
    		
    		else if(elementValue.equals("QUARTERLY"))
    			this._periodicity = HistDataPeriodicity.quarterly;
    		
    		else if(elementValue.equals("SEMI_ANNUALLY"))
    			this._periodicity = HistDataPeriodicity.semi_annually;
    		
    		else if(elementValue.equals("YEARLY"))
    			this._periodicity = HistDataPeriodicity.yearly;
    		
    		else if(elementValue.equals("DAILY"))
    			this._periodicity = HistDataPeriodicity.daily;
    		
    		else
    			throw new Exception("periodicityselection must be DAILY, WEEKLY, MONTHLY, QUARTERLY, SEMI_ANNUALLY, or YEARLY. Values are case-sensitive.");

            this._periodicityElement = new HistoricRequestElementString("periodicitySelection", elementValue);
    	}
    	else if(name.equals("pricingOption"))
    	{
    		if(elementValue.equals("PRICING_OPTION_YIELD"))
    			this._pricingOption = PricingOption.yield;

    		else if(elementValue.equals("PRICING_OPTION_PRICE"))
    			this._pricingOption = PricingOption.price;
    		
    		else
    			throw new Exception("pricingoption must be either PRICING_OPTION_YIELD or PRICING_OPTION_PRICE. Values are case-sensitive.");

            this._pricingOptionElement = new HistoricRequestElementString("pricingOption", elementValue);
    	}
    	else if(name.equals("overrideOption"))
    	{
    		if(elementValue.equals("OVERRIDE_OPTION_GPA"))
                this._overrideOptions = OverrideOptions.averagePrice;
    		
    		else if(elementValue.equals("OVERRIDE_OPTION_CLOSE"))
                this._overrideOptions = OverrideOptions.closingPrice;
    		
    		else
    			throw new Exception("overrideoption must be either OVERRIDE_OPTION_GPA or OVERRIDE_OPTION_CLOSE. Values are case-sensitive.");

            this._overrideOptionsElement = new HistoricRequestElementString("overrideOption", elementValue);
    	}    	
    }
    
    public void set(String name, boolean elementValue) throws Exception
    {
    	if(name.equals("adjustmentNormal"))
            this._adjustmentNormalElement = new HistoricRequestElementBool("adjustmentNormal", elementValue);
    	
    	else if(name.equals("adjustmentAbnormal"))
            this._adjustmentAbnormalElement = new HistoricRequestElementBool("adjustmentAbnormal", elementValue);

    	else if(name.equals("adjustmentSplit"))
            this._adjustmentSplitElement = new HistoricRequestElementBool("adjustmentSplit", elementValue);
		
		else
			throw new Exception("not implemented. Names are case-sensitive.");    	
    }
    
    public void set(String name, int elementValue) throws Exception
    {
    	if(name.equals("maxDataPoints"))
            this._maxDataPointElement = new HistoricRequestElementInt("maxDataPoints", elementValue);

		else
			throw new Exception("not implemented. names are case-sensitive");
    }
    
    
    
}
