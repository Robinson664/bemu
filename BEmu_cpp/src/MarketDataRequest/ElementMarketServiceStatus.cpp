//------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="src/MarketDataRequest/ElementMarketServiceStatus.cpp" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

#include "MarketDataRequest/ElementMarketServiceStatus.h"
#include "MarketDataRequest/MessageMarketServiceStatus.h"
#include "MarketDataRequest/ElementMarketString.h"

namespace BEmu
{
	namespace MarketDataRequest
	{
		ElementMarketServiceStatus::ElementMarketServiceStatus(const MessageMarketServiceStatus * arg)
		{
			ElementPtr * elmFirst = arg->firstElement();
			this->_serviceName = (ElementMarketString*)elmFirst;
		}

		Name ElementMarketServiceStatus::name() const
		{
			return Name("ServiceOpened");
		}

		size_t ElementMarketServiceStatus::numValues() const
		{
			return 1;
		}

		size_t ElementMarketServiceStatus::numElements() const
		{
			return 1;
		}

		bool ElementMarketServiceStatus::isNull() const
		{
			return false;
		}

		bool ElementMarketServiceStatus::isArray() const
		{
			return false;
		}

		bool ElementMarketServiceStatus::isComplexType() const
		{
			return true;
		}

		ElementPtr * ElementMarketServiceStatus::getElement(int position) const
		{
			if(position == 0)
				return this->_serviceName;
			else
				throw elementPtrEx;
		}

		std::ostream& ElementMarketServiceStatus::print(std::ostream& stream, int level, int spacesPerLevel) const
		{
			stream << "ServiceOpened = {" << std::endl;
			this->_serviceName->print(stream, level + 1, spacesPerLevel);
			stream << '}' << std::endl;

			return stream;
		}

	}
}