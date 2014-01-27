//------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="src/MarketDataRequest/ElementMarketInt.cpp" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

#include "MarketDataRequest/ElementMarketInt.h"

namespace BEmu
{
	namespace MarketDataRequest
	{
		ElementMarketInt::ElementMarketInt(std::string name, int value)
		{
			this->_name = name;
			this->_value = value;
		}

		Name ElementMarketInt::name() const
		{
			return Name(this->_name.c_str());
		}

		size_t ElementMarketInt::numValues() const
		{
			return 1;
		}

		size_t ElementMarketInt::numElements() const
		{
			return 0;
		}

		bool ElementMarketInt::isNull() const
		{
			return false;
		}

		bool ElementMarketInt::isArray() const
		{
			return false;
		}

		bool ElementMarketInt::isComplexType() const
		{
			return false;
		}

		int ElementMarketInt::getValueAsInt32(int index) const
		{
			if(index == 0)
				return this->_value;
			else
				throw elementPtrEx;
		}

		long ElementMarketInt::getValueAsInt64(int index) const
		{
			if(index == 0)
				return (long)this->_value;
			else
				throw elementPtrEx;
		}

		float ElementMarketInt::getValueAsFloat32(int index) const
		{
			if(index == 0)
				return (float)this->_value;
			else
				throw elementPtrEx;
		}

		double ElementMarketInt::getValueAsFloat64(int index) const
		{
			if(index == 0)
				return (double)this->_value;
			else
				throw elementPtrEx;
		}

		std::ostream& ElementMarketInt::print(std::ostream& stream, int level, int spacesPerLevel) const
		{
			this->prettyPrintHelper(stream, level, spacesPerLevel, this->_value);
			return stream;
		}

	}
}