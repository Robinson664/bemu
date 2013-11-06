//------------------------------------------------------------------------------
// <copyright project="BEmu" file="src/HistoricalDataRequest/ElementHistoricDateTime.cpp" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

#include "HistoricalDataRequest/ElementHistoricDateTime.h"
#include "BloombergTypes/Name.h"

namespace BEmu
{
	namespace HistoricalDataRequest
	{
		ElementHistoricDateTime::ElementHistoricDateTime(const Datetime& value)
		{
			this->_value = value;
		}

		ElementHistoricDateTime::~ElementHistoricDateTime()
		{
		}

		Name ElementHistoricDateTime::name() const
		{
			return Name("date");
		}
				
		Datetime ElementHistoricDateTime::getValueAsDatetime(int index) const
		{
			return this->_value;
		}

		const char * ElementHistoricDateTime::getValueAsString(int index) const
		{
			return this->_value.ToYYYYMMDD().c_str();
		}

		std::ostream& ElementHistoricDateTime::print(std::ostream& stream, int level, int spacesPerLevel) const
		{
			ElementPtr::prettyPrintHelper(stream, level, spacesPerLevel, this->_value);
			return stream;
		}

	}
}