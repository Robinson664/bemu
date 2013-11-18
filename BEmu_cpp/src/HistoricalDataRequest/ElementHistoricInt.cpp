//------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="src/HistoricalDataRequest/ElementReferenceInt.cpp" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

#include "HistoricalDataRequest/ElementHistoricInt.h"

#include "BloombergTypes/Name.h"

namespace BEmu
{
	namespace HistoricalDataRequest
	{
		ElementHistoricInt::ElementHistoricInt(const std::string& name, int value)
		{
			this->_name = name;
			this->_value = value;
		}

		ElementHistoricInt::~ElementHistoricInt()
		{
		}


		Name ElementHistoricInt::name() const
		{
			Name result(this->_name.c_str());
			return result;
		}

		size_t ElementHistoricInt::numValues() const
		{
			return 1;
		}

		size_t ElementHistoricInt::numElements() const
		{
			return 0;
		}

		
		bool ElementHistoricInt::isArray() const
		{
			return false;
		}

		bool ElementHistoricInt::isComplexType() const
		{
			return false;
		}


		int ElementHistoricInt::getValueAsInt32(int index) const
		{
			if(index == 0)
				return this->_value;
			else
				throw elementPtrEx;
		}

		long ElementHistoricInt::getValueAsInt64(int index) const
		{
			if(index == 0)
				return (long)this->_value;
			else
				throw elementPtrEx;
		}

		float ElementHistoricInt::getValueAsFloat32(int index) const
		{
			if(index == 0)
				return (float)this->_value;
			else
				throw elementPtrEx;
		}

		double ElementHistoricInt::getValueAsFloat64(int index) const
		{
			if(index == 0)
				return (double)this->_value;
			else
				throw elementPtrEx;
		}

		const char * ElementHistoricInt::getValueAsString(int index) const
		{
			if(index == 0)
				return ElementPtr::toCharPointer(this->_value);
			else
				throw elementPtrEx;
		}


		std::ostream& ElementHistoricInt::print(std::ostream& stream, int level, int spacesPerLevel) const
		{
			ElementPtr::prettyPrintHelper(stream, level, spacesPerLevel, this->_value);
			return stream;
		}

	}
}