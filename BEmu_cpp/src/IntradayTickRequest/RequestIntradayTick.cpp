//------------------------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="src/IntradayTickRequest/RequestIntradayTick.cpp" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------------------------

#include "IntradayTickRequest/RequestIntradayTick.h"
#include "BloombergTypes/Name.h"
#include "BloombergTypes/Element.h"
#include "BloombergTypes/ElementPtr.h"
#include "BloombergTypes/RequestPtr.h"
#include "BloombergTypes/Datetime.h"
#include "Types/RandomDataGenerator.h"
#include "IntradayTickRequest/RequestIntradayTickElementStringArray.h"
#include <vector>

namespace BEmu
{
	namespace IntradayTickRequest
	{
		RequestIntradayTick::RequestIntradayTick(const Service& svc)
		{
			this->_eventTypes = 0;
			this->_security = 0;
			this->_timeStart = 0;
			this->_timeEnd = 0;
			this->_includeConditionCodes = 0;
			this->_includeNonPlottableEvents = 0;
			this->_includeExchangeCodes = 0;
			this->_returnEids = 0;
			this->_includeBrokerCodes = 0;
			this->_includeRpsCodes = 0;
			this->_includeBicMicCodes = 0;

			this->_eventTypes = new RequestIntradayTickElementStringArray("eventTypes");
			this->_service = svc;
			this->_requestType = RequestPtr::intradayTick;
		}

		RequestIntradayTick::~RequestIntradayTick()
		{
			delete this->_eventTypes;
			this->_eventTypes = 0;

			if(this->_security != 0) //I don't know why I need this
			{
				delete this->_security;
				this->_security = 0;
			}

			delete this->_timeStart;
			this->_timeStart = 0;

			delete this->_timeEnd;
			this->_timeEnd = 0;

			delete this->_includeConditionCodes;
			this->_includeConditionCodes = 0;

			delete this->_includeNonPlottableEvents;
			this->_includeNonPlottableEvents = 0;

			delete this->_includeExchangeCodes;
			this->_includeExchangeCodes = 0;

			delete this->_returnEids;
			this->_returnEids = 0;

			delete this->_includeBrokerCodes;
			this->_includeBrokerCodes = 0;

			delete this->_includeRpsCodes;
			this->_includeRpsCodes = 0;
			
			delete this->_includeBicMicCodes;
			this->_includeBicMicCodes = 0;
		}

		const Service RequestIntradayTick::getService()
		{
			return this->_service;
		}

		bool RequestIntradayTick::hasStartDate() const
		{
			return this->_timeStart != 0;
		}

		bool RequestIntradayTick::hasEndDate() const
		{
			return this->_timeEnd != 0;
		}

		const Datetime RequestIntradayTick::getStartDate() const
		{
			Datetime dtStartOrYesterday;
			if(this->_timeStart == 0)
			{
				dtStartOrYesterday = Datetime::Today();
				dtStartOrYesterday.addDays(-1); //yesterday
			}
			else
			{
				dtStartOrYesterday = this->_timeStart->getDate();
			}

			//if dtStart is older than 140 days, cap it at 140 days
			Datetime dtOldest = Datetime::Today();
			dtOldest.addDays(-140);

			//cap start day at 140 days ago
			if(dtStartOrYesterday < dtOldest)
				dtStartOrYesterday = dtOldest;

			return dtStartOrYesterday;
		}

		const Datetime RequestIntradayTick::getEndDate() const
		{
			Datetime dtEnd;
			if(this->_timeEnd == 0)
				dtEnd = Datetime::Now(); //right now
			else
				dtEnd = this->_timeEnd->getDate();

			return dtEnd;
		}

		std::vector<Datetime>* RequestIntradayTick::getDates() //the caller will need to delete the vector
		{
			std::vector<Datetime>* result = new std::vector<Datetime>();

			Datetime dtStart = this->getStartDate();
			Datetime dtEnd = this->getEndDate();
			Datetime dtLoop = dtStart;

			while(dtLoop < dtEnd)
			{
				result->push_back(dtLoop);
				dtLoop.addMinutes(RandomDataGenerator::IntradayTickIntervalInMinutes());
			}

			return result;
		}

		bool RequestIntradayTick::includeConditionCodes()
		{
			return this->_includeConditionCodes->getBool();
		}

		const std::string& RequestIntradayTick::security()
		{
			return this->_security->security();
		}

		Datetime RequestIntradayTick::dtStart()
		{
			return this->_timeStart->getDate();
		}

		Datetime RequestIntradayTick::dtEnd()
		{
			return this->_timeEnd->getDate();
		}

		Element RequestIntradayTick::getElement(const char* name)
		{
			if(strncmp(name, "eventTypes", 11) == 0)
			{
				Element result(this->_eventTypes);
				return result;
			}

			else if(strncmp(name, "security", 9) == 0)
			{
				Element result(this->_security);
				return result;
			}

			else if(strncmp(name, "startDateTime", 14) == 0)
			{
				Element result(this->_timeStart);
				return result;
			}

			else if(strncmp(name, "endDateTime", 12) == 0)
			{
				Element result(this->_timeEnd);
				return result;
			}
			
			else if(strncmp(name, "includeConditionCodes", 22) == 0)
			{
				Element result(this->_includeConditionCodes);
				return result;
			}
			
			else if(strncmp(name, "includeNonPlottableEvents", 26) == 0)
			{
				Element result(this->_includeNonPlottableEvents);
				return result;
			}

			else if(strncmp(name, "includeExchangeCodes", 21) == 0)
			{
				Element result(this->_includeExchangeCodes);
				return result;
			}

			else if(strncmp(name, "returnEids", 11) == 0)
			{
				Element result(this->_returnEids);
				return result;
			}

			else if(strncmp(name, "includeBrokerCodes", 19) == 0)
			{
				Element result(this->_includeBrokerCodes);
				return result;
			}

			else if(strncmp(name, "includeRpsCodes", 16) == 0)
			{
				Element result(this->_includeRpsCodes);
				return result;
			}

			else if(strncmp(name, "includeBicMicCodes", 19) == 0)
			{
				Element result(this->_includeBicMicCodes);
				return result;
			}

			else
				throw requestEx;
		}

		void RequestIntradayTick::append(const char* name, const char* value)
		{
			if(strncmp(name, "eventTypes", 11) == 0)
				this->_eventTypes->addValue(value);

			else
				throw requestEx;
		}

		void RequestIntradayTick::set(const char* name, const char* value)
		{
			if(strncmp(name, "security", 9) == 0)
				this->_security = new RequestIntradayTickElementString(std::string(name), value);

			else
				throw requestEx;
		}

		void RequestIntradayTick::set(const char* name, const Datetime& value)
		{
			if(strncmp(name, "startDateTime", 14) == 0)
				this->_timeStart = new RequestIntradayTickElementTime(std::string(name), value);

			else if(strncmp(name, "endDateTime", 12) == 0)
				this->_timeEnd = new RequestIntradayTickElementTime(std::string(name), value);

			else
				throw requestEx;
		}

		void RequestIntradayTick::set(const char* name, bool value)
		{
			if(strncmp(name, "includeConditionCodes", 22) == 0)
				this->_includeConditionCodes = new RequestIntradayTickElementBool(std::string(name), value);
			
			else if(strncmp(name, "includeNonPlottableEvents", 26) == 0)
				this->_includeNonPlottableEvents = new RequestIntradayTickElementBool(std::string(name), value);

			else if(strncmp(name, "includeExchangeCodes", 21) == 0)
				this->_includeExchangeCodes = new RequestIntradayTickElementBool(std::string(name), value);

			else if(strncmp(name, "returnEids", 11) == 0)
				this->_returnEids = new RequestIntradayTickElementBool(std::string(name), value);

			else if(strncmp(name, "includeBrokerCodes", 19) == 0)
				this->_includeBrokerCodes = new RequestIntradayTickElementBool(std::string(name), value);

			else if(strncmp(name, "includeRpsCodes", 16) == 0)
				this->_includeRpsCodes = new RequestIntradayTickElementBool(std::string(name), value);

			else if(strncmp(name, "includeBicMicCodes", 19) == 0)
				this->_includeBicMicCodes = new RequestIntradayTickElementBool(std::string(name), value);

			else
				throw requestEx;
		}

		std::ostream& RequestIntradayTick::print(std::ostream& stream, int level, int spacesPerLevel) const
		{
			stream << "IntradayTickRequest = {" << std::endl;

			if(this->_security != 0)
				this->_security->print(stream, level + 1, spacesPerLevel);
			
			if(this->_eventTypes != 0)
				this->_eventTypes->print(stream, level + 1, spacesPerLevel);
			
			if(this->_timeStart != 0)
				this->_timeStart->print(stream, level + 1, spacesPerLevel);
			
			if(this->_timeEnd != 0)
				this->_timeEnd->print(stream, level + 1, spacesPerLevel);
			
			if(this->_includeConditionCodes != 0)
				this->_includeConditionCodes->print(stream, level + 1, spacesPerLevel);
			
			if(this->_includeNonPlottableEvents != 0)
				this->_includeNonPlottableEvents->print(stream, level + 1, spacesPerLevel);
			
			if(this->_includeExchangeCodes != 0)
				this->_includeExchangeCodes->print(stream, level + 1, spacesPerLevel);
			
			if(this->_returnEids != 0)
				this->_returnEids->print(stream, level + 1, spacesPerLevel);
			
			if(this->_includeBrokerCodes != 0)
				this->_includeBrokerCodes->print(stream, level + 1, spacesPerLevel);
			
			if(this->_includeRpsCodes != 0)
				this->_includeRpsCodes->print(stream, level + 1, spacesPerLevel);
			
			if(this->_includeBicMicCodes != 0)
				this->_includeBicMicCodes->print(stream, level + 1, spacesPerLevel);

			stream << '}';
			return stream;
		}

	}
}