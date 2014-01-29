//------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="src/HistoricalDataRequest/ElementHistoricDateTime.cpp" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

#include "HistoricalDataRequest/ElementHistoricDateTime.h"
#include "BloombergTypes/Name.h"
#include "Types/DisplayFormats.h"

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
			return DisplayFormats::HistoricalOrReferenceRequests_FormatDate(this->_value).c_str();
		}

		std::ostream& ElementHistoricDateTime::print(std::ostream& stream, int level, int spacesPerLevel) const
		{
			std::string strValue(DisplayFormats::HistoricalOrReferenceRequests_FormatDate(this->_value));
			ElementPtr::prettyPrintHelper(stream, level, spacesPerLevel, strValue);
			return stream;
		}

	}
}