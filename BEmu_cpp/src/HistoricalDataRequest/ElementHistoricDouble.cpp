//------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="src/HistoricalDataRequest/ElementHistoricDouble.cpp" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

#include "HistoricalDataRequest/ElementHistoricDouble.h"
#include "BloombergTypes/Name.h"

namespace BEmu
{
	namespace HistoricalDataRequest
	{
		ElementHistoricDouble::ElementHistoricDouble(const std::string& name, double value)
		{
			this->_name = name;
			this->_value = value;
		}

		ElementHistoricDouble::~ElementHistoricDouble()
		{
		}

		Name ElementHistoricDouble::name() const
		{
			Name result(this->_name.c_str());
			return result;
		}

		int ElementHistoricDouble::getValueAsInt32(int index) const
		{
			if(index == 0)
				return (int)this->_value;
			else
				throw elementPtrEx;
		}

		long ElementHistoricDouble::getValueAsInt64(int index) const
		{
			if(index == 0)
				return (long)this->_value;
			else
				throw elementPtrEx;
		}

		float ElementHistoricDouble::getValueAsFloat32(int index) const
		{
			if(index == 0)
				return (float)this->_value;
			else
				throw elementPtrEx;
		}

		double ElementHistoricDouble::getValueAsFloat64(int index) const
		{
			if(index == 0)
				return this->_value;
			else
				throw elementPtrEx;
		}

		const char * ElementHistoricDouble::getValueAsString(int index) const
		{
			if(index == 0)
			{
				const char * result = ElementPtr::toCharPointer(this->_value);
				return result;
			}
			else
				throw elementPtrEx;
		}

		std::ostream& ElementHistoricDouble::print(std::ostream& stream, int level, int spacesPerLevel) const
		{
			ElementPtr::prettyPrintHelper(stream, level, spacesPerLevel, this->_value);
			return stream;
		}
	}
}