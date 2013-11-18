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
#include "HistoricalDataRequest/RequestHistoric.h"
#include "ReferenceDataRequest/RequestReference.h"

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
			HistoricalDataRequest::RequestHistoric * result = new HistoricalDataRequest::RequestHistoric();
			return result;
		}
		else if(strncmp(operation, "ReferenceDataRequest", 21) == 0)
		{
			ReferenceDataRequest::RequestReference * result = new ReferenceDataRequest::RequestReference();
			return result;
		}
		else if(strncmp(operation, "IntradayTickRequest", 20) == 0)
		{
			IntradayTickRequest::RequestIntradayTick * result = new IntradayTickRequest::RequestIntradayTick(*this);
			return result;
		}
		else if(strncmp(operation, "IntradayBarRequest", 19) == 0)
		{
			IntradayBarRequest::RequestIntradayBar * result = new IntradayBarRequest::RequestIntradayBar(*this);
			return result;
		}
		else
		{
			throw serviceRefDataEx;
		}


	}
}