//------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="src/MarketDataRequest/MessageMarketServiceStatus.cpp" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

#include "MarketDataRequest/MessageMarketServiceStatus.h"
#include "MarketDataRequest/ElementMarketString.h"
#include "MarketDataRequest/ElementMarketServiceStatus.h"

namespace BEmu
{
	namespace MarketDataRequest
	{
		MessageMarketServiceStatus::MessageMarketServiceStatus(CorrelationId corr) : MessagePtr(Name("ServiceOpened"), corr)
		{
			this->_serviceName = new ElementMarketString("serviceName", "//blp/mktdata");
		}

		ElementPtr * MessageMarketServiceStatus::firstElement() const
		{
			return this->_serviceName;
		}

		size_t MessageMarketServiceStatus::numElements() const
		{
			return 1;
		}

		const char* MessageMarketServiceStatus::topicName() const
		{
			return "";
		}

		ElementPtr * MessageMarketServiceStatus::asElement() const
		{
			const MessageMarketServiceStatus * ptr = this;
			return new ElementMarketServiceStatus(ptr);
		}

		std::ostream& MessageMarketServiceStatus::print(std::ostream& stream, int level, int spacesPerLevel) const
		{
			stream << "ServiceOpened = {" << std::endl;
			this->_serviceName->print(stream, level + 1, spacesPerLevel);
			stream << '}' << std::endl;

			return stream;
		}
	}
}