//------------------------------------------------------------------------------
// <copyright project="BEmu" file="src/HistoricalDataRequest/ElementHistoricString.cpp" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

#include "HistoricalDataRequest/ElementHistoricString.h"
#include "BloombergTypes/Name.h"

namespace BEmu
{
	namespace HistoricalDataRequest
	{
		ElementHistoricString::ElementHistoricString(const std::string& name, const std::string& value)
		{
			this->_name = name;
			this->_value = value;
		}

		ElementHistoricString::~ElementHistoricString()
		{
		}


		Name ElementHistoricString::name() const
		{
			Name result(this->_name.c_str());
			return result;
		}


		const char * ElementHistoricString::getValueAsString(int index) const
		{
			if(index == 0)
				return this->_value.c_str();
			else
				throw elementPtrEx;
		}


		std::ostream& ElementHistoricString::print(std::ostream& stream, int level, int spacesPerLevel) const
		{
			this->prettyPrintHelper(stream, level, spacesPerLevel, this->_value);
			return stream;
		}

	}
}