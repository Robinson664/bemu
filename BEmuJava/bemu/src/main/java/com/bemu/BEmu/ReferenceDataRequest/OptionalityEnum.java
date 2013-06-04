package com.bemu.BEmu.ReferenceDataRequest;

public enum OptionalityEnum
{
	put('p'), call('c');
	
	private final char _putCall;
	
	OptionalityEnum(char ch)
	{
		this._putCall = ch;
	}
	
	public String toString()
	{
		return String.valueOf(this._putCall);
	}
}
