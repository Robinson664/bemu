//------------------------------------------------------------------------------
// <copyright project="BEmu" file="headers/HistoricalDataRequest/RequestHistoricElementInt.h" company="Jordan Robinson">
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
		class RequestHistoricElementInt : public RequestHistoricElementString
		{
			private:
				int _ivalue;

			public:
				RequestHistoricElementInt(const std::string& elementName, int value);
				~RequestHistoricElementInt();

				int getInt() const;
		};
	}
}