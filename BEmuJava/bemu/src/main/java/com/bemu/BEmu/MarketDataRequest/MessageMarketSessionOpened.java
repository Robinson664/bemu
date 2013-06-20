//------------------------------------------------------------------------------
// <copyright project="BEmuJava" file="BEmu.MarketDataRequest.MessageMarketSessionOpened.java" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

package com.bemu.BEmu.MarketDataRequest;

import com.bemu.BEmu.Name;
import com.bemu.BEmu.Message;

public class MessageMarketSessionOpened extends Message
{
    MessageMarketSessionOpened()
    {
    	super(new Name("SessionStarted"), null, null);
    }

    public String topicName()
    {
    	return "";
    }
}
