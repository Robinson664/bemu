//------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="src/MarketDataRequest/ElementMarketString.cpp" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

#include "MarketDataRequest/ElementMarketString.h"

namespace BEmu
{
	namespace MarketDataRequest
	{
		ElementMarketString::ElementMarketString(std::string name, std::string value)
		{
			this->_name = name;
			this->_value = value;
		}

		Name ElementMarketString::name() const
		{
			return Name(this->_name.c_str());
		}

		size_t ElementMarketString::numValues() const
		{
			return 1;
		}

		size_t ElementMarketString::numElements() const
		{
			return 0;
		}

		bool ElementMarketString::isNull() const
		{
			return false;
		}

		bool ElementMarketString::isArray() const
		{
			return false;
		}

		bool ElementMarketString::isComplexType() const
		{
			return false;
		}

		const char * ElementMarketString::getValueAsString(int index) const
		{
			if(index == 0)
				return this->toCharPointer(this->_value);
			else
				throw elementPtrEx;
		}

		std::ostream& ElementMarketString::print(std::ostream& stream, int level, int spacesPerLevel) const
		{
			this->prettyPrintHelper(stream, level, spacesPerLevel, this->_value);
			return stream;
		}

	}
}