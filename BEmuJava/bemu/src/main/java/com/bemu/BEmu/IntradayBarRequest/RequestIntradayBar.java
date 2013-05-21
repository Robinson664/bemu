//------------------------------------------------------------------------------
// <copyright project="BEmuJava" file="BEmu.IntradayBarRequest.RequestIntradayBar.java" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

package com.bemu.BEmu.IntradayBarRequest;

import com.bemu.BEmu.Service;
import com.bemu.BEmu.Request;
import com.bemu.BEmu.Datetime;

import java.util.Calendar;
import java.util.List;
import java.util.ArrayList;

public class RequestIntradayBar extends Request
{
	public RequestIntradayBar(Service service)
	{
		this._service = service;
        this._eventTypes = new RequestIntradayBarElementStringArray("TBD");
	}
	
    @SuppressWarnings("unused")
	private RequestIntradayBarElementString _security;
    private final RequestIntradayBarElementStringArray _eventTypes;
    private RequestIntradayBarElementTime _dtStart, _dtEnd;
    private RequestIntradayBarElementInt _intervalInMinutes;
    @SuppressWarnings("unused")
	private RequestIntradayBarElementBool _gapFillInitialBar, _returnEids, _adjustmentNormalElement, _adjustmentAbnormalElement, _adjustmentSplitElement, _adjustmentFollowDPDF;
	
	private final Service _service;
	protected Service getService()
	{
		return this._service;
	}

	protected Datetime getDtStart()
    {
    	return this._dtStart.getDate(); 
    }
    
	protected Datetime getDtEnd()
    {
    	return this._dtEnd.getDate();
    }
    
	protected List<Datetime> getDateTimes() throws Exception
    {
        if (this._dtStart.getDate() == null)
            throw new Exception("Invalid startDate.  None specified.");

        else if (this._dtEnd.getDate() == null)
            throw new Exception("Invalid endDate.  None specified.");

        else if (this._intervalInMinutes == null)
            throw new Exception("Invalid interval.  None specified (despite A.2.8 in the documentation, interval is required).");

        int interval = this._intervalInMinutes.getInt();
        if (interval < 1 || interval > 1440) //if less than one, the loop below will never terminate
            throw new Exception("The interval must be an integer between 1 and 1440.  You entered " + String.valueOf(interval));
                
        List<Datetime> result = new ArrayList<Datetime>();
        Datetime dtCurrent = new Datetime(this._dtStart.getDate());
        while(dtCurrent.calendar().getTimeInMillis() <= this._dtEnd.getDate().calendar().getTimeInMillis())
        {
        	//Show times between 13:30 and 19:30.
        	//  In the Eastern time zone this is between 9:30 am and 4:00 pm (I assume) 
        	if(dtCurrent.hour() >= 13 && dtCurrent.hour() <= 19)
        	{
        		if((dtCurrent.hour() == 13 && dtCurrent.minute() >= 30) || (dtCurrent.hour() > 13)) 
        			result.add(new Datetime(dtCurrent));
        	}
        	
        	dtCurrent.calendar().add(Calendar.MINUTE, interval);
        }
        
        return result;
    }
    
    public void set(String name, String elementValue)
    {
        String upper = name.toUpperCase();
        
        if(upper.equals("SECURITY"))
        	this._security = new RequestIntradayBarElementString(name, elementValue);
        else if (upper.equals("EVENTTYPE"))
        	this._eventTypes.addValue(elementValue);
    }
    
    public void set(String name, Datetime elementValue)
    {
        String upper = name.toUpperCase();

        if(upper.equals("STARTDATETIME"))
        {
        	elementValue.setSecond(0);
            this._dtStart = new RequestIntradayBarElementTime(name, elementValue);
        }
        else if(upper.equals("ENDDATETIME"))
        	this._dtEnd = new RequestIntradayBarElementTime(name, elementValue);
    }
    
    public void set(String name, int elementValue)
    {
        String upper = name.toUpperCase();
        if(upper.equals("INTERVAL"))
        	this._intervalInMinutes = new RequestIntradayBarElementInt(name, elementValue);
    }

    public void set(String name, boolean elementValue)
    {
        String upper = name.toUpperCase();
        
        if(upper.equals("GAPFILLINITIALBAR"))
        	this._gapFillInitialBar = new RequestIntradayBarElementBool(name, elementValue);
        
        else if(upper.equals("RETURNEIDS"))
            this._returnEids = new RequestIntradayBarElementBool(name, elementValue);
        
        else if(upper.equals("ADJUSTMENTNORMAL"))
            this._adjustmentNormalElement = new RequestIntradayBarElementBool(name, elementValue);
        
        else if(upper.equals("ADJUSTMENTABNORMAL"))
            this._adjustmentAbnormalElement = new RequestIntradayBarElementBool(name, elementValue);
        
        else if(upper.equals("ADJUSTMENTSPLIT"))
            this._adjustmentSplitElement = new RequestIntradayBarElementBool(name, elementValue);
        
        else if(upper.equals("ADJUSTMENTFOLLOWDPDF"))
            this._adjustmentFollowDPDF = new RequestIntradayBarElementBool(name, elementValue);
    }
    
    
    
}
