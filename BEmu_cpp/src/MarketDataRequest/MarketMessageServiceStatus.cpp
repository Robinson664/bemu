//------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="src/MarketDataRequest/MarketMessageServiceStatus.cpp" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

#include "MarketDataRequest/MarketMessageServiceStatus.h"
#include "MarketDataRequest/MarketElementString.h"
#include "MarketDataRequest/MarketElementServiceStatus.h"

namespace BEmu
{
	namespace MarketDataRequest
	{
		MarketMessageServiceStatus::MarketMessageServiceStatus(CorrelationId corr) : MessagePtr(Name("ServiceOpened"), corr)
		{
			this->_serviceName = new MarketElementString("serviceName", "//blp/mktdata");
		}

		std::stack<ElementPtr*> MarketMessageServiceStatus::getRootElements() const
		{
			std::stack<ElementPtr*> result;

			if(this->_serviceName != 0)
				result.push(this->_serviceName);

			return result;
		}

		ElementPtr * MarketMessageServiceStatus::firstElement() const
		{
			return this->_serviceName;
		}

		size_t MarketMessageServiceStatus::numElements() const
		{
			return 1;
		}

		const char* MarketMessageServiceStatus::topicName() const
		{
			return "";
		}

		ElementPtr * MarketMessageServiceStatus::asElement() const
		{
			const MarketMessageServiceStatus * ptr = this;
			return new MarketElementServiceStatus(ptr);
		}

		std::ostream& MarketMessageServiceStatus::print(std::ostream& stream, int level, int spacesPerLevel) const
		{
			stream << "ServiceOpened = {" << std::endl;
			this->_serviceName->print(stream, level + 1, spacesPerLevel);
			stream << '}' << std::endl;

			return stream;
		}
	}
}