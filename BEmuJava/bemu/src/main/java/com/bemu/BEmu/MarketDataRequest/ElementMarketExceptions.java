package com.bemu.BEmu.MarketDataRequest;

import com.bemu.BEmu.Element;
import com.bemu.BEmu.Name;
import com.bemu.BEmu.SchemaTypeDefinition;

public class ElementMarketExceptions extends ElementParent
{
    private final ElementMarketString _fieldId;
    private final ElementMarketReason _reason;

    public ElementMarketExceptions(String badField)
    {
        this._fieldId = new ElementMarketString("fieldId", badField);
        this._reason = new ElementMarketReason(ElementMarketReason.ReasonTypeEnum.badField);
    }
    
    public SchemaTypeDefinition typeDefinition() throws Exception
    {
    	return new SchemaTypeDefinition(this.datatype(), new Name("SubscriptionException"));
    }
	
    public Name name() throws Exception
    {
    	return new Name("exceptions");
    }
    
    public int numValues()
    {
    	return 1;
    }
    
    public int numElements()
    {
    	return 2;
    }
    
    public boolean isComplexType()
    {
    	return true;
    }
    
    public boolean isArray()
    {
    	return false;
    }
    
    public boolean isNull()
    {
    	return false;
    }
    
    public boolean hasElement(String name, boolean excludeNullElements)
    {
    	return this.hasElement(name);
    }
    
    public boolean hasElement(String name)
    {
    	return name.equals("fieldId") || name.equals("reason");
    }

    public String getElementAsString(String name) throws Exception
    {
        return this.getElement(name).getValueAsString();
    }
    
    public Element getElement(String name) throws Exception
    {
    	if(name.equals("fieldId"))
    		return this._fieldId;
    	
    	else if(name.equals("reason"))
    		return this._reason;
    	
    	else
    		throw new Exception("name not recognized. names are case-sensitive.");
    }
    
    protected StringBuilder prettyPrint(int tabIndent) throws Exception
    {
        String tabs = com.bemu.BEmu.types.IndentType.Indent(tabIndent);
        StringBuilder result = new StringBuilder();
        
        result.append(String.format("%s%s = {%s", tabs, this.name().toString(), System.getProperty("line.separator")));
        result.append(this._fieldId.prettyPrint(tabIndent + 1));
        result.append(this._reason.prettyPrint(tabIndent + 1));
        result.append(String.format("%s}%s", tabs, System.getProperty("line.separator")));

        return result;
    }

}
