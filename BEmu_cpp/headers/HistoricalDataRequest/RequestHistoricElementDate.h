//------------------------------------------------------------------------------
// <copyright project="BEmu" file="headers/HistoricalDataRequest/RequestHistoricElementDate.h" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

#pragma once

#include "HistoricalDataRequest/RequestHistoricElementString.h"

namespace BEmu
{
	namespace HistoricalDataRequest
	{
		class RequestHistoricElementDate : public RequestHistoricElementString
		{
			private:
				Datetime _instance;

			public:
				RequestHistoricElementDate(const std::string& elementName);
				RequestHistoricElementDate(const std::string& elementName, const Datetime& datetime);
				~RequestHistoricElementDate();

				Datetime getDatetime() const;
		};
	}
}