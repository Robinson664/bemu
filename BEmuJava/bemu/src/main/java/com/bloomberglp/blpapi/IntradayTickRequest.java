//------------------------------------------------------------------------------
// <copyright project="BEmu_maven" file="/BEmu_maven/bemu/src/main/java/com/bloomberglp/blpapi/IntradayTickRequest.java" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

package com.bloomberglp.blpapi;

import com.bloomberglp.blpapi.Service;
import com.bloomberglp.blpapi.Request;
import com.bloomberglp.blpapi.Datetime;

import java.util.List;
import java.util.ArrayList;
import java.util.Calendar;

public class IntradayTickRequest extends Request
{
    private IntradayTickRequestElementString _security;
    private final IntradayTickRequestElementStringArray _eventTypes;
    private IntradayTickRequestElementTime _timeStart, _timeEnd;

    private IntradayTickRequestElementBool _includeConditionCodes, _includeNonPlottableEvents, _includeExchangeCodes, _returnEids,
        _includeBrokerCodes, _includeRpsCodes, _includeBicMicCodes;

    private final Service _service;
    Service getService()
    {
    	return this._service;
    }
    
    public IntradayTickRequest(Service service)
    {
    	this._includeConditionCodes = new IntradayTickRequestElementBool("includeConditionCodes", false);
        this._eventTypes = new IntradayTickRequestElementStringArray("eventTypes");
        this._service = service;
    }
    
    List<Datetime> getDates()
    {
    	List<Datetime> result = new ArrayList<Datetime>();
    	
        Datetime dtStart = this._timeStart.getDate();
        if(dtStart == null)
        {
        	Calendar c = Calendar.getInstance();
        	c.set(Calendar.HOUR, 0);
        	c.set(Calendar.MINUTE, 0);
        	c.set(Calendar.SECOND, 0);
        	c.set(Calendar.MILLISECOND, 0);
        	c.add(Calendar.DAY_OF_MONTH, -1);
        	
        	dtStart = new Datetime(c); //yestarday at start-of-day
        }
        
        Datetime dtOldest;
        { //intraday tick data is stored only for 140 days (documentation section 7.2.3)
        	Calendar c = Calendar.getInstance();
        	c.set(Calendar.HOUR, 0);
        	c.set(Calendar.MINUTE, 0);
        	c.set(Calendar.SECOND, 0);
        	c.set(Calendar.MILLISECOND, 0);
        	c.add(Calendar.DAY_OF_MONTH, -140);
        	
        	dtOldest = new Datetime(c);
        }
        
        if(dtStart.calendar().getTimeInMillis() < dtOldest.calendar().getTimeInMillis())
        	dtStart = dtOldest;
        
        Datetime dtEnd = this._timeEnd.getDate();
        if(dtEnd == null)
        	dtEnd = new Datetime();
        
        while(dtStart.calendar().getTimeInMillis() < dtEnd.calendar().getTimeInMillis())
        {
        	result.add(new Datetime(dtStart));
        	int minutes = com.bloomberglp.blpapi.RandomDataGenerator.intradayTickIntervalInMinutes();
        	
        	dtStart.calendar().add(Calendar.MINUTE, minutes);
        }
        
        return result;
    }
    
    boolean includeConditionCodes()
    {
    	return this._includeConditionCodes.getBoolean();
    }
    
    String security()
    {
    	return this._security.security();
    }
    
    Datetime dtStart()
    {
    	return this._timeStart.getDate();
    }
    
    Datetime dtEnd()
    {
    	return this._timeEnd.getDate();
    }
    
    public String toString()
    {
    	StringBuilder result = new StringBuilder();
    	result.append("IntradayTickRequest = {" + System.getProperty("line.separator"));

        Element[] elms = { this._security, this._eventTypes, this._timeStart, this._timeEnd, this._includeConditionCodes, 
        		this._includeNonPlottableEvents, this._includeExchangeCodes, this._returnEids, this._includeBrokerCodes, 
        		this._includeRpsCodes, this._includeBicMicCodes};
        
    	for(int i = 0; i < elms.length; i++)
    	{
    		Element current = elms[i];
    		
    		if(current != null)
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
    	if(name.equals("eventTypes"))
    		this._eventTypes.addValue(elementValue);
    	else
    		throw new Exception("com.bemu.RequestIntradayTick.Append: Element name not supported (case-sensitive): " + name);
    }
    
    public void set(String name, String elementValue) throws Exception
    {
    	if(name.equals("security"))
    		this._security = new IntradayTickRequestElementString(name, elementValue);
    	else
    		throw new Exception("name not recognized.  names are case-sensitive.");
    }
    
    public void set(String name, Datetime elementValue) throws Exception
    {
    	if(name.equals("startDateTime"))
    		this._timeStart = new IntradayTickRequestElementTime(name, elementValue);
    	else if(name.equals("endDateTime"))
    		this._timeEnd = new IntradayTickRequestElementTime(name, elementValue);
    	else
    		throw new Exception("name not recognized.  names are case-sensitive.");
    }
    
    public void set(String name, boolean elementValue) throws Exception
    {
    	if(name.equals("includeConditionCodes"))
    		this._includeConditionCodes = new IntradayTickRequestElementBool(name, elementValue);
    	
    	else if(name.equals("includeNonPlottableEvents"))
    		this._includeNonPlottableEvents = new IntradayTickRequestElementBool(name, elementValue);
    	
    	else if(name.equals("includeExchangeCodes"))
    		this._includeExchangeCodes = new IntradayTickRequestElementBool(name, elementValue);
    	
    	else if(name.equals("returnEids"))
    		this._returnEids = new IntradayTickRequestElementBool(name, elementValue);
    	
    	else if(name.equals("includeBrokerCodes"))
    		this._includeBrokerCodes = new IntradayTickRequestElementBool(name, elementValue);
    	
    	else if(name.equals("includeRpsCodes"))
    		this._includeRpsCodes = new IntradayTickRequestElementBool(name, elementValue);
    	
    	else if(name.equals("includeBicMicCodes"))
    		this._includeBicMicCodes = new IntradayTickRequestElementBool(name, elementValue);
    	
    	else
    		throw new Exception("name not recognized.  names are case-sensitive.");
    }
}
