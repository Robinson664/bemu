package com.examples;


import java.text.SimpleDateFormat;
import java.util.Calendar;

//import com.bemu.BEmu.*; //un-comment this line to use the Bloomberg API Emulator
import com.bloomberglp.blpapi.*; //un-comment this line to use the actual Bloomberg API

public class RunHistoricalDataRequest
{
	private static SimpleDateFormat dateFmt = new SimpleDateFormat("yyyyMMdd");
	private static SimpleDateFormat dateFmtOut = new SimpleDateFormat("yyyy-MM-dd");
	
	public static void RunExample() throws Exception
	{
		SessionOptions soptions = new SessionOptions();
		soptions.setServerHost("127.0.0.1");
		soptions.setServerPort(8194);
		
		Session session = new Session(soptions);
		if(session.start() && session.openService("//blp/refdata"))
		{
			Service service = session.getService("//blp/refdata");
			Request request = service.createRequest("HistoricalDataRequest");

            //request information for the following securities
            request.append("securities", "IBM US EQUITY");
            request.append("securities", "SPY US EQUITY");
            request.append("securities", "C A COMDTY");
            request.append("securities", "AAPL 150117C00600000 EQUITY"); //this is a stock option: TICKER yyMMdd[C/P]\d{8} EQUITY
            
            //include the following simple fields in the result
            request.append("fields", "BID");
            request.append("fields", "ASK");

            //Historical requests allow a few overrides.  See the developer's guide A.2.4 for more information.
            Calendar calStart = Calendar.getInstance();
            calStart.add(Calendar.MONTH, -1);
            String strStart = dateFmt.format(calStart.getTime());

            Calendar calEnd = Calendar.getInstance();
            calEnd.add(Calendar.DAY_OF_MONTH, 10);
            String strEnd = dateFmt.format(calEnd.getTime());
            
            request.set("startDate", strStart); //Request that the information start three months ago from today.  This override is required.
            request.set("endDate", strEnd); //Request that the information end three days before today.  This is an optional override.  The default is today.
                        
            //Determine the frequency and calendar type of the output. To be used in conjunction with Period Selection.
            request.set("periodicityAdjustment", "CALENDAR"); //Optional string.  Valid values are ACTUAL (default), CALENDAR, and FISCAL.
            
            //Determine the frequency of the output. To be used in conjunction with Period Adjustment.
            request.set("periodicitySelection", "DAILY"); //Optional string.  Valid values are DAILY (default), WEEKLY, MONTHLY, QUARTERLY, SEMI_ANNUALLY, and YEARLY

            //Sets quote to Price or Yield for a debt instrument whose default value is quoted in yield (depending on pricing source).
            request.set("pricingOption", "PRICING_OPTION_PRICE"); //Optional string.  Valid values are PRICING_OPTION_PRICE (default) and PRICING_OPTION_YIELD

            //Adjust for "change on day"
            request.set("adjustmentNormal", true); //Optional bool. Valid values are true and false (default = false)

            //Adjusts for Anormal Cash Dividends
            request.set("adjustmentAbnormal", false); //Optional bool. Valid values are true and false (default = false)

            //Capital Changes Defaults
            request.set("adjustmentSplit", true); //Optional bool. Valid values are true and false (default = false)

            //The maximum number of data points to return, starting from the startDate
            //request.set("maxDataPoints", 5); //Optional integer.  Valid values are positive integers.  The default is unspecified in which case the response will have all data points between startDate and endDate

            //Indicates whether to use the average or the closing price in quote calculation.
            request.set("overrideOption", "OVERRIDE_OPTION_CLOSE"); //Optional string.  Valid values are OVERRIDE_OPTION_GPA for an average and OVERRIDE_OPTION_CLOSE (default) for the closing price
            
            CorrelationID requestID = new CorrelationID(1);
            session.sendRequest(request, requestID);
            
			boolean continueLoop = true;
			while(continueLoop)
			{
				Event evt = session.nextEvent();
				switch(evt.eventType().intValue())
				{
					case Event.EventType.Constants.RESPONSE:
						RunHistoricalDataRequest.processResponseHist(evt);
						continueLoop = false;
						break;
					case Event.EventType.Constants.PARTIAL_RESPONSE:
						RunHistoricalDataRequest.processResponseHist(evt);
						break;
				}
			}
		}
	}
	
	private static void processResponseHist(Event evt) throws Exception
	{
        System.out.println("EventType = " + evt.eventType());
        
		MessageIterator miter = evt.messageIterator();
		while(miter.hasNext())
		{
			Message msg = miter.next();
			
			System.out.println();
			System.out.println("correlationID= " + msg.correlationID());
			System.out.println("messageType= " + msg.messageType());
			
			Element elmSecurityData = msg.getElement("securityData");
			
			Element elmSecurity = elmSecurityData.getElement("security");
			String security = elmSecurity.getValueAsString();
			System.out.println(security);
			
			Element elmFieldData = elmSecurityData.getElement("fieldData");
			for (int valueIndex = 0; valueIndex < elmFieldData.numValues(); valueIndex++)
			{
                Element elmValues = elmFieldData.getValueAsElement(valueIndex);                
				Datetime date = elmValues.getElementAsDate("date");
                double bid = elmValues.getElementAsFloat64("BID");
                double ask = elmValues.getElementAsFloat64("ASK");
                
                System.out.print(RunHistoricalDataRequest.dateFmtOut.format(date.calendar().getTime()));
                System.out.println(String.format(": BID = $%,.2f, ASK = $%,.2f", bid, ask));
			}
		}
	}
}
