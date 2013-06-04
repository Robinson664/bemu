//------------------------------------------------------------------------------
// <copyright project="BEmuJava" file="BEmu.IntradayBarRequest.ElementBarTickDataArray.java" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

package com.bemu.BEmu.IntradayBarRequest;

import com.bemu.BEmu.Element;
import com.bemu.BEmu.Name;
import java.lang.StringBuilder;
import java.util.List;
import java.util.ArrayList;

public class ElementBarTickDataArray extends Element
{
	 private final List<ElementBarTickData> _elements;
	 
     ElementBarTickDataArray(List<BarTickDataType> bars)
     {
         this._elements = new ArrayList<ElementBarTickData>();
         
         for(int i = 0; i < bars.size(); i++)
         {
        	 this._elements.add(new ElementBarTickData(bars.get(i)));
         }
     }
     
     public Element getValueAsElement(int index)
     {
    	 return this._elements.get(index);
     }
     
     public Name name()
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
     
     protected StringBuilder prettyPrint(int tabIndent)
     {
         String tabs = com.bemu.BEmu.types.IndentType.Indent(tabIndent);
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
