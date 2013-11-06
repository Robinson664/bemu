//------------------------------------------------------------------------------
// <copyright project="BEmu" file="src/HistoricalDataRequest/RequestHistoricElementInt.cpp" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

#include "HistoricalDataRequest/RequestHistoricElementInt.h"

namespace BEmu
{
	namespace HistoricalDataRequest
	{
		RequestHistoricElementInt::RequestHistoricElementInt(const std::string& elementName, int value) : RequestHistoricElementString(elementName, ElementPtr::toString(value))
		{
			this->_ivalue = value;
		}

		RequestHistoricElementInt::~RequestHistoricElementInt()
		{
		}

		int RequestHistoricElementInt::getInt() const
		{
			return this->_ivalue;
		}

	}
}