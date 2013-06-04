package com.bemu.BEmu.ReferenceDataRequest;

import com.bemu.BEmu.Element;

//ElementParent is used to allow protected Element members to be visible in this package 
public abstract class ElementParent extends Element
{
	protected abstract StringBuilder prettyPrint(int tabIndent);
}
