//------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="src/HistoricalDataRequest/RequestHistoricElementBool.cpp" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

#include "HistoricalDataRequest/RequestHistoricElementBool.h"

namespace BEmu
{
	namespace HistoricalDataRequest
	{
		RequestHistoricElementBool::RequestHistoricElementBool(const std::string& elementName, bool bvalue) : RequestHistoricElementString(elementName, bvalue ? "true" : "false")
		{
			this->_bvalue = bvalue;
		}

		RequestHistoricElementBool::~RequestHistoricElementBool()
		{
		}

		bool RequestHistoricElementBool::getBool() const
		{
			return this->_bvalue;
		}
	}
}