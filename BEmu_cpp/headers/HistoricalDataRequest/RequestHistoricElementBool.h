//------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="headers/HistoricalDataRequest/RequestHistoricElementBool.h" company="Jordan Robinson">
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
		class RequestHistoricElementBool : public RequestHistoricElementString
		{
			private:
				bool _bvalue;

			public:
				RequestHistoricElementBool(const std::string& elementName, bool bvalue);
				~RequestHistoricElementBool();

				bool getBool() const;
		};
	}
}