package BEmu.HistoricalDataRequest;

import BEmu.Element;

//ElementParent is used to allow protected Element members to be visible in this package 
public abstract class ElementParent extends Element
{
	protected abstract StringBuilder prettyPrint(int tabIndent);
}
