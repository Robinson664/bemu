//------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="src/MarketDataRequest/MessageMarketSessionOpened.cpp" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

#include "MarketDataRequest/MessageMarketSessionOpened.h"

namespace BEmu
{
	namespace MarketDataRequest
	{
		MessageMarketSessionOpened::MessageMarketSessionOpened() : MessagePtr(Name("SessionStarted"), CorrelationId((long)0))
		{
		}

		const char* MessageMarketSessionOpened::topicName() const
		{
			return "";
		}
	}
}