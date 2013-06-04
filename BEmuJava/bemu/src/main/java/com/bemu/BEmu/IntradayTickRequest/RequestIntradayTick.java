//------------------------------------------------------------------------------
// <copyright project="BEmuJava" file="BEmu.IntradayTickRequest.RequestIntradayTick.java" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

package com.bemu.BEmu.IntradayTickRequest;

import com.bemu.BEmu.Service;
import com.bemu.BEmu.Request;
import com.bemu.BEmu.Datetime;

import java.util.List;
import java.util.ArrayList;
import java.util.Calendar;

public class RequestIntradayTick extends Request
{
    private RequestIntradayTickElementString _security;
    private final RequestIntradayTickElementStringArray _eventTypes;
    private RequestIntradayTickElementTime _timeStart, _timeEnd;

    private RequestIntradayTickElementBool _includeConditionCodes, _includeNonPlottableEvents, _includeExchangeCodes, _returnEids,
        _includeBrokerCodes, _includeRpsCodes, _includeBicMicCodes;

    private final Service _service;
    Service getService()
    {
    	return this._service;
    }
    
    public RequestIntradayTick(Service service)
    {
    	this._includeConditionCodes = new RequestIntradayTickElementBool("includeConditionCodes", false);
        this._eventTypes = new RequestIntradayTickElementStringArray("eventTypes");
        this._service = service;
    }
    
    List<Datetime> GetDates()
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
        	int minutes = com.bemu.BEmu.types.RandomDataGenerator.intradayTickIntervalInMinutes();
        	
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

        if (this._security != null)
            result.append(this._security.prettyPrint(1));

        if (this._eventTypes != null)
            result.append(this._eventTypes.prettyPrint(1));

        if (this._timeStart != null)
            result.append(this._timeStart.prettyPrint(1));

        if (this._timeEnd != null)
            result.append(this._timeEnd.prettyPrint(1));

        if (this._includeConditionCodes != null)
            result.append(this._includeConditionCodes.prettyPrint(1));

        if (this._includeNonPlottableEvents != null)
            result.append(this._includeNonPlottableEvents.prettyPrint(1));

        if (this._includeExchangeCodes != null)
            result.append(this._includeExchangeCodes.prettyPrint(1));

        if (this._returnEids != null)
            result.append(this._returnEids.prettyPrint(1));

        if (this._includeBrokerCodes != null)
            result.append(this._includeBrokerCodes.prettyPrint(1));

        if (this._includeRpsCodes != null)
            result.append(this._includeRpsCodes.prettyPrint(1));

        if (this._includeBicMicCodes != null)
            result.append(this._includeBicMicCodes.prettyPrint(1));
        
        result.append("}");
        
        return result.toString();
    }
    
    public void append(String name, String elementValue) throws Exception
    {
    	String lower = name.toLowerCase();
    	if(lower.equals("eventtypes"))
    		this._eventTypes.addValue(elementValue);
    	else
    		throw new Exception("com.bemu.RequestIntradayTick.Append: Element name not supported " + name);
    }
    
    public void set(String name, String elementValue)
    {
    	String upper = name.toUpperCase();
    	if(upper.equals("SECURITY"))
    		this._security = new RequestIntradayTickElementString(name, elementValue);
    }
    
    public void set(String name, Datetime elementValue)
    {
    	String upper = name.toUpperCase();
    	if(upper.equals("STARTDATETIME"))
    		this._timeStart = new RequestIntradayTickElementTime(name, elementValue);
    	else if(upper.equals("ENDDATETIME"))
    		this._timeEnd = new RequestIntradayTickElementTime(name, elementValue);
    }
    
    public void set(String name, boolean elementValue)
    {
    	String upper = name.toUpperCase();
    	if(upper.equals("INCLUDECONDITIONCODES"))
    		this._includeConditionCodes = new RequestIntradayTickElementBool(name, elementValue);
    	
    	else if(upper.equals("INCLUDENONPLOTTABLEEVENTS"))
    		this._includeNonPlottableEvents = new RequestIntradayTickElementBool(name, elementValue);
    	
    	else if(upper.equals("INCLUDEEXCHANGECODES"))
    		this._includeExchangeCodes = new RequestIntradayTickElementBool(name, elementValue);
    	
    	else if(upper.equals("RETURNEIDS"))
    		this._returnEids = new RequestIntradayTickElementBool(name, elementValue);
    	
    	else if(upper.equals("INCLUDEBROKERCODES"))
    		this._includeBrokerCodes = new RequestIntradayTickElementBool(name, elementValue);
    	
    	else if(upper.equals("INCLUDERPSCODES"))
    		this._includeRpsCodes = new RequestIntradayTickElementBool(name, elementValue);
    	
    	else if(upper.equals("INCLUDEBICMICCODES"))
    		this._includeBicMicCodes = new RequestIntradayTickElementBool(name, elementValue);
    }
}
