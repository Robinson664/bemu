//------------------------------------------------------------------------------
// <copyright project="BEmuJava" file="BEmu.IntradayTickRequest.Tuple3.java" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

package com.bemu.BEmu.IntradayTickRequest;

//In my C# code, I use Tuples.
//  I'll create my own tuples in Java to keep the code looking similar to my C# code.
class Tuple3<T1, T2, T3>
{
	private final T1 _item1;
	private final T2 _item2;
	private final T3 _item3; 
	
	public Tuple3(T1 item1, T2 item2, T3 item3)
	{
		this._item1 = item1;
		this._item2 = item2;
		this._item3 = item3;
	}

	public T1 item1() { return this._item1; }
	public T2 item2() { return this._item2; }
	public T3 item3() { return this._item3; }
}
