package com.bemu.BEmu.ReferenceDataRequest;

import java.util.List;
import java.util.ArrayList;

import com.bemu.BEmu.Element;
import com.bemu.BEmu.Name;
import com.bemu.BEmu.SchemaTypeDefinition;

public class ElementReferenceFieldExceptionsArray extends ElementParent
{
    private final List<ElementReferenceFieldExceptions> _exceptions;

    public ElementReferenceFieldExceptionsArray(List<String> badFields)
    {
        this._exceptions = new ArrayList<ElementReferenceFieldExceptions>(badFields.size());
        for(int i = 0; i < badFields.size(); i++)
        {
            this._exceptions.add(new ElementReferenceFieldExceptions(badFields.get(i)));
        }
    }
    
    public SchemaTypeDefinition typeDefinition() throws Exception
    {
    	return new SchemaTypeDefinition(this.datatype(), new Name("FieldException"));
    }
	
    public Name name() throws Exception
    {
    	return new Name("fieldExceptions");
    }
    
    public int numValues()
    {
    	return this._exceptions.size();
    }
    
    public int numElements()
    {
    	return 0;
    }
    
    public boolean isComplexType()
    {
    	return false;
    }
    
    public boolean isArray()
    {
    	return true;
    }
    
    public boolean isNull()
    {
    	return false;
    }

    public Object getValue(int index)
    {
        return this._exceptions.get(index);
    }

    public Element getValueAsElement(int index)
    {
        return this._exceptions.get(index);
    }
    
    protected StringBuilder prettyPrint(int tabIndent) throws Exception
    {
        String tabs = com.bemu.BEmu.types.IndentType.Indent(tabIndent);
        StringBuilder result = new StringBuilder();

        result.append(String.format("%s%s[] = {%s", tabs, this.name().toString(), System.getProperty("line.separator")));
        
        for(int i = 0; i < this._exceptions.size(); i++)
        {
        	result.append(this._exceptions.get(i).prettyPrint(tabIndent + 1));
        }

        result.append(String.format("%s}%s", tabs, System.getProperty("line.separator")));
        return result;
    }
}
