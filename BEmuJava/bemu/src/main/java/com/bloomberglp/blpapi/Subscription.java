//------------------------------------------------------------------------------
//	This code comes from blpapi-3.6.1-0.jar
//------------------------------------------------------------------------------

package com.bloomberglp.blpapi;

import java.util.Arrays;
import java.util.Iterator;
import java.util.List;

public class Subscription
{
	// The following is not part of the DLL
	
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
	
    private final Integer _conflationInterval;
    Integer conflationInterval() 
    {
    	return this._conflationInterval;
    }
	
    private Integer ReadConflationInterval(List<String> options)
    {
    	if(options == null)
    		return null;
    	
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
	// The above is not part of the DLL
	
	
	private String d_subscriptionString;
	private CorrelationID d_correlationId;
	private Session.SubscriptionStatus d_subscriptionStatus = Session.SubscriptionStatus.UNSUBSCRIBED;
	
	private static final String utsReg = "//[^/]+/[^/]+/[^?]+(\\?[^&]+(&[^&]+)*)?";
	private static final String topicReg = "[^?]+(\\?[^&]+(&[^&]+)*)?";

    private static final char OPTIONS_SEPARATOR = '&';
	private static final char TOPIC_OPTIONS_SEPARATOR = '?';
	private static final char FIELDS_SEPARATOR = ',';
	private static final String FIELDS_OPTION = "fields=";
	
	Subscription(String subscriptionString, CorrelationID correlationID, Session.SubscriptionStatus status)
	{
		this.d_subscriptionString = subscriptionString;
		this.d_correlationId = correlationID;
		this.d_subscriptionStatus = status;
		
		this._conflationInterval = null;
		this._security = null;
		this._fields = null;
	}
	
	public Subscription(String subscriptionString)
	{
		this(subscriptionString, new CorrelationID());
	}
	
	public Subscription(String subscriptionString, CorrelationID correlationID)
	{
		if ((subscriptionString == null) || (correlationID == null)) {
			throw new IllegalArgumentException("Null arguments");
		}
		if (!isValidSubscriptionString(subscriptionString)) {
			throw new IllegalArgumentException("Invalid subscription string");
		}
		this.d_subscriptionString = subscriptionString;
		this.d_correlationId = correlationID;
		
		this._conflationInterval = null;
		this._security = null;
		this._fields = null;
	}
	
	public Subscription(String security, String fields)
	{
		this(security, fields, "", new CorrelationID());
	}
	
	public Subscription(String security, String fields, CorrelationID correlationId)
	{
		this(security, fields, "", correlationId);
	}
	
	public Subscription(String security, String fields, String options)
	{
		this(security, fields, options, new CorrelationID());
	}
	
	public Subscription(String security, String fields, String options, CorrelationID correlationID)
	{
		if ((security == null) || (security.length() <= 0) || (security.indexOf(TOPIC_OPTIONS_SEPARATOR) >= 0)) {
			throw new IllegalArgumentException("Invalid security: " + security);
		}
		if (options == null) {
			options = "";
		}
		if (fields == null) {
			fields = "";
		}
		if (fields.indexOf(OPTIONS_SEPARATOR) >= 0) {
			throw new IllegalArgumentException("Invalid fields: " + fields);
		}
		if (correlationID == null) {
			correlationID = new CorrelationID();
		}
		StringBuilder localStringBuilder = new StringBuilder(security.length() + fields.length() + options.length());
		
		localStringBuilder.append(security);
		
		boolean hasFields = fields.length() > 0;
		boolean hasOptions = options.length() > 0; 
		
		if (hasFields || hasOptions)
		{
			localStringBuilder.append(TOPIC_OPTIONS_SEPARATOR);
			if (hasFields)
			{
				localStringBuilder.append(FIELDS_OPTION);
				localStringBuilder.append(fields);
			}
			
			if (hasFields && hasOptions)
			{
				localStringBuilder.append(OPTIONS_SEPARATOR);
			}
			if (hasOptions)
			{
				localStringBuilder.append(options);
			}
		}
		this.d_subscriptionString = localStringBuilder.toString();
		this.d_correlationId = correlationID;
		

		this._security = security;
		
		if(hasOptions)
		{
			String[] arrOptions = options.split(",");	
			this._conflationInterval = this.ReadConflationInterval(Arrays.asList(arrOptions));
		}
		else
			this._conflationInterval = null;
		
		if(hasFields)
		{
			String[] arrFields = fields.split(",");
			this._fields = Arrays.asList(arrFields);
		}
		else
			this._fields = null;
	}
	
	public Subscription(String security, List<String> fields)
	{
		this(security, fields, null, new CorrelationID());
	}
	
	public Subscription(String security, List<String> fields, CorrelationID correlationID)
	{
		this(security, fields, null, correlationID);
	}
	
	public Subscription(String security, List<String> fields, List<String> options)
	{
		this(security, fields, options, new CorrelationID());
	}
	
	public Subscription(String security, List<String> fields, List<String> options, CorrelationID correlationID)
	{
		if ((security == null) || (security.length() <= 0) || (security.indexOf(TOPIC_OPTIONS_SEPARATOR) >= 0)) {
			throw new IllegalArgumentException("Invalid security: " + security);
		}
		if (correlationID == null) {
			throw new IllegalArgumentException("Null correlationId argument");
		}
		StringBuilder localStringBuilder = new StringBuilder(64);
		
		localStringBuilder.append(security);
		
		getFieldsAndOptions(localStringBuilder, fields, options);
		
		this.d_subscriptionString = localStringBuilder.toString();
		this.d_correlationId = correlationID;
		
		this._security = security;
		this._conflationInterval = this.ReadConflationInterval(options);
		this._fields = fields;
	}
	
	public String subscriptionString()
	{
		return this.d_subscriptionString;
	}
	
	public CorrelationID correlationID()
	{
		return this.d_correlationId;
	}
	
	public Session.SubscriptionStatus subscriptionStatus()
	{
		return this.d_subscriptionStatus;
	}
	
	public void setSubscriptionString(String subscriptionString)
	{
		if (subscriptionString == null) {
			throw new IllegalArgumentException("A null argument");
		}
		if (subscriptionString.length() <= 0) {
			throw new IllegalArgumentException("An empty subscription string");
		}
		this.d_subscriptionString = subscriptionString;
	}
	
	public void setCorrelationID(CorrelationID correlationID)
	{
		if (correlationID == null) {
			throw new IllegalArgumentException("A null argument");
		}
		this.d_correlationId = correlationID;
	}
	
	public String toString()
	{
		StringBuilder localStringBuilder = new StringBuilder();
		
		localStringBuilder.append("[");
		
		localStringBuilder.append(this.d_subscriptionString);
		
		localStringBuilder.append(" CorrelationID = {");
		localStringBuilder.append(this.d_correlationId.toString());
		localStringBuilder.append("}");
		
		localStringBuilder.append(" Status = {");
		localStringBuilder.append(this.d_subscriptionStatus.toString());
		localStringBuilder.append("}");
		
		localStringBuilder.append("]");
		
		return localStringBuilder.toString();
	}
	
	private static void getFieldsAndOptions(StringBuilder stringBuilder, List<String> fields, List<String> options)
	{
		boolean hasFields = (fields != null) && (fields.size() != 0);
		boolean hasOptions = (options != null) && (options.size() != 0);
		boolean separatorsAppended = false;
		
		String current;
		
		Iterator<String> localIterator;
		if (hasFields) {
			for (localIterator = fields.iterator(); localIterator.hasNext();)
			{
				current = (String)localIterator.next();
				if ((current != null) && (current.length() > 0))
				{
					if (!separatorsAppended)
					{
						stringBuilder.append(TOPIC_OPTIONS_SEPARATOR);
						stringBuilder.append(FIELDS_OPTION);
						separatorsAppended = true;
					}
					else
					{
						stringBuilder.append(FIELDS_SEPARATOR);
					}
					stringBuilder.append(current);
				}
			}
		}
		
		if (hasOptions) {
			for (localIterator = options.iterator(); localIterator.hasNext();)
			{
				current = (String)localIterator.next();
				if ((current != null) && (current.length() > 0))
				{
					if (!separatorsAppended)
					{
						stringBuilder.append(TOPIC_OPTIONS_SEPARATOR);
						separatorsAppended = true;
					}
					else
					{
						stringBuilder.append(OPTIONS_SEPARATOR);
					}
					stringBuilder.append(current);
				}
			}
		}
	}
	
	static boolean isValidSubscriptionString(String paramString)
	{
		if (paramString.startsWith("//")) {
			return paramString.matches(utsReg);
		}
		return paramString.matches(topicReg);
	}
}
