package BEmu.HistoricalDataRequest;

import BEmu.Element;
import BEmu.Name;
import BEmu.Message;
import BEmu.CorrelationID;
import BEmu.Datetime;
import java.util.Map;

public class MessageHistoric extends Message
{
    private final ElementHistoricSecurityData _security;
    
    MessageHistoric(CorrelationID corr, String securityName, Map<Datetime, Map<String, Object>> fieldData, int sequenceNumber)
    {
    	super(new Name("HistoricalDataResponse"), corr, null);
    	this._security = new ElementHistoricSecurityData(securityName, fieldData, sequenceNumber);
    }
    
    ElementHistoricSecurityData security()
    {
    	return this._security;
    }
    
	public Element getElement(String name) throws Exception
	{
		if(name.toLowerCase().equals(this._security.name().toString().toLowerCase()))
			return this._security;
		else
			throw new Exception("not implemented");
	}
    
    public String toString()
    {
        StringBuilder result = new StringBuilder();
        
        result.append("HistoricalDataResponse (choice) = {" + System.getProperty("line.separator"));
        result.append(this._security.prettyPrint(1));
        result.append("}");

        return result.toString();
    }
}
