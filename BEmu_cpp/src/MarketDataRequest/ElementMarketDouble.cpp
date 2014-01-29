//------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="src/MarketDataRequest/ElementMarketDouble.cpp" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

#include "MarketDataRequest/ElementMarketDouble.h"
#include "Types/DisplayFormats.h"

namespace BEmu
{
	namespace MarketDataRequest
	{
		ElementMarketDouble::ElementMarketDouble(std::string name, double value)
		{
			this->_name = name;
			this->_value = value;
		}

		Name ElementMarketDouble::name() const
		{
			return Name(this->_name.c_str());
		}

		size_t ElementMarketDouble::numValues() const
		{
			return 1;
		}

		size_t ElementMarketDouble::numElements() const
		{
			return 0;
		}

		bool ElementMarketDouble::isNull() const
		{
			return false;
		}

		bool ElementMarketDouble::isArray() const
		{
			return false;
		}

		bool ElementMarketDouble::isComplexType() const
		{
			return false;
		}

		double ElementMarketDouble::getValueAsFloat64(int index) const
		{
			if(index == 0)
				return this->_value;
			else
				throw elementPtrEx;
		}

		std::ostream& ElementMarketDouble::print(std::ostream& stream, int level, int spacesPerLevel) const
		{
			std::string strValue(DisplayFormats::FormatNumberNoSeparators(this->_value, 2));
			this->prettyPrintHelper(stream, level, spacesPerLevel, strValue);
			return stream;
		}

	}
}