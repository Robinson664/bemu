//------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="src/MarketDataRequest/ElementMarketDatetime.cpp" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

#include "MarketDataRequest/ElementMarketDatetime.h"
#include "Types/DisplayFormats.h"

namespace BEmu
{
	namespace MarketDataRequest
	{
		ElementMarketDatetime::ElementMarketDatetime(std::string name, Datetime datetime)
		{
			this->_name = name;
			this->_datetime = datetime;
		}

		Name ElementMarketDatetime::name() const
		{
			return Name(this->_name.c_str());
		}

		size_t ElementMarketDatetime::numValues() const
		{
			return 1;
		}

		size_t ElementMarketDatetime::numElements() const
		{
			return 0;
		}

		bool ElementMarketDatetime::isNull() const
		{
			return false;
		}

		Datetime ElementMarketDatetime::getValueAsDatetime(int index) const
		{
			if(index == 0)
				return this->_datetime;
			else
				throw elementPtrEx;
		}

		std::ostream& ElementMarketDatetime::print(std::ostream& stream, int level, int spacesPerLevel) const
		{
			std::string strDateTime(DisplayFormats::MarketDataRequests_FormatDateZone(this->_datetime));
			this->prettyPrintHelper(stream, level, spacesPerLevel, strDateTime);
			return stream;
		}
		
	}
}