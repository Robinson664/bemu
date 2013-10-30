//------------------------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="src/BloombergTypes/ServiceRefData.cpp" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------------------------

#include "BloombergTypes/ServiceRefData.h"
#include "BloombergTypes/RequestPtr.h"
#include "BloombergTypes/Service.h"

#include "IntradayTickRequest/RequestIntradayTick.h"
#include "IntradayBarRequest/RequestIntradayBar.h"

namespace BEmu
{
	const char* ServiceRefData::name() const
	{
		return "//blp/refdata";
	}

	Request ServiceRefData::createRequest(const char* operation) const
	{
		RequestPtr* reqP = this->createRequestPtr(operation);
		Request result(reqP);
		return result;
	}

	RequestPtr* ServiceRefData::createRequestPtr(const char* operation) const
	{
		if(strncmp(operation, "HistoricalDataRequest", 21) == 0)
		{
			throw serviceRefDataEx;
		}
		else if(strncmp(operation, "ReferenceDataRequest", 20) == 0)
		{
			throw serviceRefDataEx;
		}
		else if(strncmp(operation, "IntradayTickRequest", 19) == 0)
		{
			IntradayTickRequest::RequestIntradayTick *result = new IntradayTickRequest::RequestIntradayTick(this);
			return result;
		}
		else if(strncmp(operation, "IntradayBarRequest", 18) == 0)
		{
			const Service* svc = this;
			IntradayBarRequest::RequestIntradayBar *result = new IntradayBarRequest::RequestIntradayBar(svc);
			return result;
		}
		else
		{
			throw serviceRefDataEx;
		}


	}
}