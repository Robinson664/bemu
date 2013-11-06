//------------------------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="headers/IntradayTickRequest/RequestIntradayTick.h" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------------------------

#pragma once

#include <vector>
#include "BloombergTypes/Service.h"
#include "BloombergTypes/RequestPtr.h"

#include "IntradayTickRequest/RequestIntradayTickElementString.h"
#include "IntradayTickRequest/RequestIntradayTickElementStringArray.h"
#include "IntradayTickRequest/RequestIntradayTickElementTime.h"
#include "IntradayTickRequest/RequestIntradayTickElementBool.h"

namespace BEmu
{
	class Datetime;
	class Element;

	namespace IntradayTickRequest
	{
		class RequestIntradayTick : public RequestPtr
		{
			private:
				RequestIntradayTickElementString *_security;
				RequestIntradayTickElementStringArray *_eventTypes;
				RequestIntradayTickElementTime *_timeStart, *_timeEnd;
				
				RequestIntradayTickElementBool *_includeConditionCodes, *_includeNonPlottableEvents, *_includeExchangeCodes, *_returnEids,
					*_includeBrokerCodes, *_includeRpsCodes, *_includeBicMicCodes;

				Service _service;
				
				const Datetime getStartDate() const; //used only as a helper for getDates()
				const Datetime getEndDate() const; //used only as a helper for getDates()

			public:
				RequestIntradayTick(const Service& svc);
				~RequestIntradayTick();
				const Service getService();
				std::vector<Datetime>* getDates();
				bool includeConditionCodes();
				const std::string& security();
				bool hasStartDate() const;
				bool hasEndDate() const;

				Datetime dtStart();
				Datetime dtEnd();

				virtual Element getElement(const char* name);
				virtual void append(const char* name, const char* value);
				virtual void set(const char* name, const char* value);
				virtual void set(const char* name, const Datetime& value);
				virtual void set(const char* name, bool value);

				virtual std::ostream& print(std::ostream& stream, int level, int spacesPerLevel) const;
		};
	}
}