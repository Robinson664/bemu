//------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="src/MarketDataRequest/ElementMarketBool.cpp" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

#include "MarketDataRequest/ElementMarketBool.h"

namespace BEmu
{
	namespace MarketDataRequest
	{
		ElementMarketBool::ElementMarketBool(std::string name, bool value)
		{
			this->_name = name;
			this->_value = value;
		}

		Name ElementMarketBool::name() const
		{
			return Name(this->_name.c_str());
		}

		size_t ElementMarketBool::numValues() const
		{
			return 1;
		}

		size_t ElementMarketBool::numElements() const
		{
			return 0;
		}

		bool ElementMarketBool::isNull() const
		{
			return false;
		}

		bool ElementMarketBool::isArray() const
		{
			return false;
		}

		bool ElementMarketBool::isComplexType() const
		{
			return false;
		}

		bool ElementMarketBool::getValueAsBool(int index) const
		{
			if(index == 0)
				return this->_value;
			else
				throw elementPtrEx;
		}

		std::ostream& ElementMarketBool::print(std::ostream& stream, int level, int spacesPerLevel) const
		{
			this->prettyPrintHelper(stream, level, spacesPerLevel, this->_value ? "True" : "False");
			return stream;
		}

	}
}