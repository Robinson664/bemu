package com.examples;

import com.bemu.BEmu.*; //un-comment this line to use the Bloomberg API Emulator
//import com.bloomberglp.blpapi.*; //un-comment this line to use the actual Bloomberg API

public class RunReferenceDataRequest
{
	public static void RunExample() throws Exception
	{
		SessionOptions soptions = new SessionOptions();
		soptions.setServerHost("127.0.0.1");
		soptions.setServerPort(8194);
		
		Session session = new Session(soptions);
		if(session.start() && session.openService("//blp/refdata"))
		{
            CorrelationID requestID = new CorrelationID(1);
			Service service = session.getService("//blp/refdata");
			Request request = service.createRequest("ReferenceDataRequest");

            //request information for the following securities
            request.append("securities", "IBM US EQUITY");
            request.append("securities", "SPY US EQUITY");
            request.append("securities", "MSFT US EQUITY");
            request.append("securities", "AAPL 150117C00600000 EQUITY"); //this is a stock option: TICKER yyMMdd[C/P]\d{8} EQUITY

            //include the following simple fields in the result
            request.append("fields", "PX_LAST");
            request.append("fields", "BID");
            request.append("fields", "ASK");
            request.append("fields", "TICKER");
            request.append("fields", "OPT_EXPIRE_DT");

            //request a field that can be overriden and returns bulk data
            request.append("fields", "CHAIN_TICKERS");
            Element overrides = request.getElement("overrides");

            //request only puts
            Element ovrdPutCall = overrides.appendElement();
            ovrdPutCall.setElement("fieldId", "CHAIN_PUT_CALL_TYPE_OVRD");
            ovrdPutCall.setElement("value", "P"); //accepts either "C" for calls or "P" for puts

            //request 5 options in the result
            Element ovrdNumStrikes = overrides.appendElement();
            ovrdNumStrikes.setElement("fieldId", "CHAIN_POINTS_OVRD");
            ovrdNumStrikes.setElement("value", 5); //accepts a positive integer

            //request options that expire on Dec. 20, 2014
            Element ovrdDtExps = overrides.appendElement();
            ovrdDtExps.setElement("fieldId", "CHAIN_EXP_DT_OVRD");
            ovrdDtExps.setElement("value", "20141220"); //accepts dates in the format yyyyMMdd

            session.sendRequest(request, requestID);

            boolean continueToLoop = true;
            while (continueToLoop)
            {
                Event eventObj = session.nextEvent();
                switch (eventObj.eventType().intValue())
                {
                    case Event.EventType.Constants.RESPONSE: // final event
                        continueToLoop = false;
                        handleResponseEvent(eventObj);
                        break;
                    case Event.EventType.Constants.PARTIAL_RESPONSE:
                        handleResponseEvent(eventObj);
                        break;
                }
            }
		}		
	}


    private static void handleResponseEvent(Event eventObj) throws Exception
    {
    	System.out.println("EventType =" + eventObj.eventType());
		MessageIterator miter = eventObj.messageIterator();
		while(miter.hasNext())
        {
			Message message = miter.next();
			
			System.out.println("correlationID=" + message.correlationID().toString());
			System.out.println("messageType =" + message.messageType().toString());

            Element elmSecurityDataArray = message.getElement("securityData");
            for (int valueIndex = 0; valueIndex < elmSecurityDataArray.numValues(); valueIndex++)
            {
                Element elmSecurityData = elmSecurityDataArray.getValueAsElement(valueIndex);

                String security = elmSecurityData.getElementAsString("security");
                System.out.println();
                System.out.println();
                System.out.println(security);

                Element elmFieldData = elmSecurityData.getElement("fieldData");

                double pxLast = elmFieldData.getElementAsFloat64("PX_LAST");
                double bid = elmFieldData.getElementAsFloat64("BID");
                double ask = elmFieldData.getElementAsFloat64("ASK");
                String ticker = elmFieldData.getElementAsString("TICKER");

                System.out.println("PX_LAST = " + String.valueOf(pxLast));
                System.out.println("BID = " + String.valueOf(bid));
                System.out.println("ASK = " + String.valueOf(ask));
                System.out.println("TICKER = " + ticker);

                boolean excludeNullElements = true;
                if (elmFieldData.hasElement("CHAIN_TICKERS", excludeNullElements)) //be careful, excludeNullElements is false by default
                {
                    Element chainTickers = elmFieldData.getElement("CHAIN_TICKERS");
                    for (int chainTickerValueIndex = 0; chainTickerValueIndex < chainTickers.numValues(); chainTickerValueIndex++)
                    {
                        Element chainTicker = chainTickers.getValueAsElement(chainTickerValueIndex);
                        String strChainTicker = chainTicker.getElementAsString("Ticker");

                        System.out.println("CHAIN_TICKER = " + strChainTicker);
                    }
                }
                else
                {
                	System.out.println("No CHAIN_TICKER information");
                }
            }
        }
    }

}
