//------------------------------------------------------------------------------
// <copyright project="BEmu_maven" file="/BEmu_maven/bemu/src/main/java/com/bloomberglp/blpapi/IntradayBarRequest.java" company="Jordan Robinson">
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

import java.util.Calendar;
import java.util.List;
import java.util.ArrayList;

public class IntradayBarRequest extends Request
{
	public IntradayBarRequest(Service service)
	{
		this._service = service;
        //this._eventTypes = new IntradayBarRequestElementStringArray("TBD");
	}
	
	private IntradayBarRequestElementString _security;
    
	//private final IntradayBarRequestElementStringArray _eventTypes;
	private IntradayBarRequestElementString _eventType;
    
    private IntradayBarRequestElementTime _dtStart, _dtEnd;
    private IntradayBarRequestElementInt _intervalInMinutes;
	private IntradayBarRequestElementBool _gapFillInitialBar, _returnEids, _adjustmentNormalElement, _adjustmentAbnormalElement, _adjustmentSplitElement, _adjustmentFollowDPDF;
	
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
	
	//Don't use this.  It's only used internally.
	public String security() throws Exception
	{
		return this._security.getValueAsString();
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
    
    public void set(String name, String elementValue) throws Exception
    {
        if(name.equals("security"))
        	this._security = new IntradayBarRequestElementString(name, elementValue);
        
        else if (name.equals("eventType"))
        	//this._eventTypes.addValue(elementValue);
        	this._eventType = new IntradayBarRequestElementString(name, elementValue);
        
        else
        	throw new Exception("name not recognized.  case-sensitive.");
    }
    
    public void set(String name, Datetime elementValue) throws Exception
    {
        if(name.equals("startDateTime"))
        {
        	elementValue.setSecond(0);
            this._dtStart = new IntradayBarRequestElementTime(name, elementValue);
        }
        else if(name.equals("endDateTime"))
        	this._dtEnd = new IntradayBarRequestElementTime(name, elementValue);
        
        else
        	throw new Exception("name not recognized.  case-sensitive.");
    }
    
    public void set(String name, int elementValue) throws Exception
    {
        if(name.equals("interval"))
        	this._intervalInMinutes = new IntradayBarRequestElementInt(name, elementValue);
        
        else
        	throw new Exception("name not recognized.  case-sensitive.");
    }

    public void set(String name, boolean elementValue) throws Exception
    {
        if(name.equals("gapFillInitialBar"))
        	this._gapFillInitialBar = new IntradayBarRequestElementBool(name, elementValue);
        
        else if(name.equals("returnEids"))
            this._returnEids = new IntradayBarRequestElementBool(name, elementValue);
        
        else if(name.equals("adjustmentNormal"))
            this._adjustmentNormalElement = new IntradayBarRequestElementBool(name, elementValue);
        
        else if(name.equals("adjustmentAbnormal"))
            this._adjustmentAbnormalElement = new IntradayBarRequestElementBool(name, elementValue);
        
        else if(name.equals("adjustmentSplit"))
            this._adjustmentSplitElement = new IntradayBarRequestElementBool(name, elementValue);
        
        else if(name.equals("adjustmentFollowDPDF"))
            this._adjustmentFollowDPDF = new IntradayBarRequestElementBool(name, elementValue);
        
        else
        	throw new Exception("name not recognized.  case-sensitive.");
    }

    public String toString()
    {
    	StringBuilder result = new StringBuilder();
    	result.append("IntradayBarRequest = {" + System.getProperty("line.separator"));
    	
    	Element[] elms = { this._security, this._eventType, this._dtStart, this._dtEnd, this._intervalInMinutes, 
    			this._gapFillInitialBar, this._returnEids, this._adjustmentNormalElement,  this._adjustmentAbnormalElement, 
    			this._adjustmentSplitElement, this._adjustmentFollowDPDF };
    	
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
}
