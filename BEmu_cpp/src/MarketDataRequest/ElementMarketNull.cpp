//------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="src/MarketDataRequest/ElementMarketNull.cpp" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

#include "MarketDataRequest/ElementMarketNull.h"

namespace BEmu
{
	namespace MarketDataRequest
	{
		ElementMarketNull::ElementMarketNull(std::string name)
		{
			this->_name = name;
		}

		Name ElementMarketNull::name() const
		{
			return Name(this->_name.c_str());
		}

		size_t ElementMarketNull::numValues() const
		{
			return 0;
		}

		size_t ElementMarketNull::numElements() const
		{
			return 0;
		}

		bool ElementMarketNull::isNull() const
		{
			return true;
		}

		bool ElementMarketNull::isArray() const
		{
			return true;
		}

		bool ElementMarketNull::isComplexType() const
		{
			return false;
		}

		std::ostream& ElementMarketNull::print(std::ostream& stream, int level, int spacesPerLevel) const
		{
			return stream;
		}

	}
}