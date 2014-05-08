//------------------------------------------------------------------------------
// <copyright project="BEmu_maven" file="/BEmu_maven/bemu/src/main/java/com/bloomberglp/blpapi/Subscription.java" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

package com.bloomberglp.blpapi;

import java.util.List;
import java.util.LinkedList;
import com.bloomberglp.blpapi.CorrelationID;

public class Subscription
{
    private final String _security;
    public String security()
    {
    	return this._security;
    }

    private final List<String> _fields;
    public List<String> fields()
    {
    	return this._fields;
    }

    private final CorrelationID _corr;
    public CorrelationID correlationID()
    {
    	return this._corr;
    }

    private final Integer _conflationInterval;
    Integer conflationInterval() 
    {
    	return this._conflationInterval;
    }
    
    public Subscription(String security, List<String> fields)
    {
        this._security = security;
        this._corr = new CorrelationID();
        this._conflationInterval = null;

        this._fields = new LinkedList<String>();
        for(int i = 0; i < fields.size(); i++)
        {
        	this._fields.add(fields.get(i));
        }
    }
    
    public Subscription(String security, List<String> fields, List<String> options)
    {
        this._security = security;
        this._corr = new CorrelationID();
        this._conflationInterval = this.ReadConflationInterval(options);

        this._fields = new LinkedList<String>();
        for(int i = 0; i < fields.size(); i++)
        {
        	this._fields.add(fields.get(i));
        }
    }
    
    public Subscription(String security, String field, CorrelationID correlationID)
    {
        this._security = security;
        this._fields = new LinkedList<String>();
        this._fields.add(field);
        this._corr = correlationID;
        this._conflationInterval = null;
    }
    
    public Subscription(String security, List<String> fields, CorrelationID correlationID)
    {
        this._security = security;
        
        this._fields = new LinkedList<String>();
        for(int i = 0; i < fields.size(); i++)
        {
        	this._fields.add(fields.get(i));
        }
        
        this._corr = correlationID;
        this._conflationInterval = null;
    }
    
    public Subscription(String security, List<String> fields, List<String> options, CorrelationID correlationID)
    {
        this._security = security;

        this._fields = new LinkedList<String>();
        for(int i = 0; i < fields.size(); i++)
        {
        	this._fields.add(fields.get(i));
        }
        
        this._corr = correlationID;
        this._conflationInterval = this.ReadConflationInterval(options);
    }
    
    
    
    
    
    private Integer ReadConflationInterval(List<String> options)
    {
        Integer result = null;
        for(int i = 0; i < options.size(); i++)
        {
        	String str = options.get(i);
        	
            if (str.startsWith("interval="))
            {
                String strInterval = str.substring(0, str.indexOf('=') + 1);                
                if(this.tryParseInt(strInterval))
                {
                	result = Integer.parseInt(strInterval);
                }
            }
        }
        return result;
    }
    
    private boolean tryParseInt(String value)  
    {  
         try  
         {  
             Integer.parseInt(value);  
             return true;  
         }
         catch(NumberFormatException nfe)  
         {
        	 return false;  
         }  
    }

}
