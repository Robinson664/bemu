//------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="src/MarketDataRequest/ElementMarketSubscriptionStarted.cpp" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

#include "MarketDataRequest/ElementMarketSubscriptionStarted.h"
#include "MarketDataRequest/MessageMarketSubscriptionStarted.h"

namespace BEmu
{
	namespace MarketDataRequest
	{
		ElementMarketSubscriptionStarted::ElementMarketSubscriptionStarted(MessageMarketSubscriptionStarted * arg)
		{
			this->_exceptions = (ElementMarketNull*)arg->firstElement();
		}

		Name ElementMarketSubscriptionStarted::name() const
		{
			return Name("SubscriptionStarted");
		}

		size_t ElementMarketSubscriptionStarted::numValues() const
		{
			return 1;
		}

		size_t ElementMarketSubscriptionStarted::numElements() const
		{
			return 1;
		}

		bool ElementMarketSubscriptionStarted::isNull() const
		{
			return false;
		}

		bool ElementMarketSubscriptionStarted::isArray() const
		{
			return false;
		}

		bool ElementMarketSubscriptionStarted::isComplexType() const
		{
			return true;
		}

		std::ostream& ElementMarketSubscriptionStarted::print(std::ostream& stream, int level, int spacesPerLevel) const
		{
			stream << "SubscriptionStarted = {" << std::endl << '}' << std::endl;
			return stream;
		}
	}
}