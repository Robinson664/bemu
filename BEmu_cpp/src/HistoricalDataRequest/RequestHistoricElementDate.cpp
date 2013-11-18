//------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="src/HistoricalDataRequest/RequestHistoricElementDate.cpp" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

#include "HistoricalDataRequest/RequestHistoricElementDate.h"
#include "BloombergTypes/Datetime.h"

namespace BEmu
{
	namespace HistoricalDataRequest
	{
		RequestHistoricElementDate::RequestHistoricElementDate(const std::string& elementName) : RequestHistoricElementString(elementName, "")
		{
		}

		RequestHistoricElementDate::RequestHistoricElementDate(const std::string& elementName, const Datetime& datetime) : RequestHistoricElementString(elementName, datetime.ToYYYYMMDD())
		{
			this->_instance = datetime;
		}

		RequestHistoricElementDate::~RequestHistoricElementDate()
		{
		}

		Datetime RequestHistoricElementDate::getDatetime() const
		{
			return this->_instance;
		}
	}
}