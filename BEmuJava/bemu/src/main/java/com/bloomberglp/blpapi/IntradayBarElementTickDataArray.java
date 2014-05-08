//------------------------------------------------------------------------------
// <copyright project="BEmu_maven" file="/BEmu_maven/bemu/src/main/java/com/bloomberglp/blpapi/IntradayBarElementTickDataArray.java" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

package com.bloomberglp.blpapi;

import com.bloomberglp.blpapi.Element;
import com.bloomberglp.blpapi.Name;
import com.bloomberglp.blpapi.SchemaTypeDefinition;

import java.lang.StringBuilder;
import java.util.List;
import java.util.ArrayList;

public class IntradayBarElementTickDataArray extends Element
{
	 private final List<IntradayBarElementTickData> _elements;
	 
     IntradayBarElementTickDataArray(List<IntradayBarTickDataType> bars)
     {
         this._elements = new ArrayList<IntradayBarElementTickData>();
         
         for(int i = 0; i < bars.size(); i++)
         {
        	 this._elements.add(new IntradayBarElementTickData(bars.get(i)));
         }
     }
     
     public SchemaTypeDefinition typeDefinition() throws Exception
     {
     	return new SchemaTypeDefinition(this.datatype(), new Name("IntradayBarTickData"));
     }
     
     public Element getValueAsElement(int index)
     {
    	 return this._elements.get(index);
     }
     
     public Name name() throws Exception
     {
     	return new Name("barTickData");
     }
     
     public int numValues()
     {
     	return this._elements.size();
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
    	 return this._elements.get(index);
     }
     
     protected StringBuilder prettyPrint(int tabIndent) throws Exception
     {
         String tabs = com.bloomberglp.blpapi.IndentType.Indent(tabIndent);
         StringBuilder result = new StringBuilder();

         result.append(String.format("%s%s[] = {%s", tabs, this.name(), System.getProperty("line.separator")));
         for(int i = 0; i < this._elements.size(); i++)
         {
        	 result.append(this._elements.get(i).prettyPrint(tabIndent + 1));
         }
         result.append(String.format("%s}%s", tabs, System.getProperty("line.separator")));

         return result;
     }
     
}
