package com.bemu.BEmu.ReferenceDataRequest;

import java.text.DateFormat;
import java.text.SimpleDateFormat;

import com.bemu.BEmu.Datetime;
import com.bemu.BEmu.Name;

public class ElementReferenceArrayChainTickersItem extends ElementParent
{
    private final ElementReferenceString _element;

    ElementReferenceArrayChainTickersItem(String ticker, Datetime dtExp, OptionalityEnum optionality, int strike)
    {
    	DateFormat df = new SimpleDateFormat ("MM/dd/yy");
        String optionTicker = String.format("%s US %s %s%s", 
        		ticker, 
        		df.format(dtExp.calendar().getTime()), 
    			optionality.toString().toUpperCase(), 
    			String.valueOf(strike));
        
        this._element = new ElementReferenceString("TICKER", optionTicker);
    }
    
    public Name name()
    {
    	return new Name("TICKER");
    }
    
    public int numValues()
    {
    	return 0;
    }
    
    public int numElements()
    {
    	return 1;
    }
    
    public boolean isComplexType()
    {
    	return false;
    }
    
    public boolean isArray()
    {
    	return false;
    }
    
    public boolean isNull()
    {
    	return false;
    }
    
    public String getElementAsString(String name) throws Exception
    {
    	if(this._element.name().toString().toUpperCase().equals(name.toUpperCase()))
    		return this._element.getValueAsString();
    	
    	else
    		return super.getElementAsString(name);
    }
    
    protected StringBuilder prettyPrint(int tabIndent)
    {
        String tabs = com.bemu.BEmu.types.IndentType.Indent(tabIndent);
        StringBuilder result = new StringBuilder();

        result.append(String.format("%sCHAIN_TICKERS = {%s", tabs, System.getProperty("line.separator")));
        result.append(this._element.prettyPrint(tabIndent + 1));
        result.append(String.format("%s}%s", tabs, System.getProperty("line.separator")));
        
        return result;
    }
    
    
}
