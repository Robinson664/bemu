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
		RequestIntradayTick::RequestIntradayTick(const Service *svc)
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

		const Service* RequestIntradayTick::getService()
		{
			return this->_service;
		}

		const Datetime RequestIntradayTick::getStartDate() const
		{
			Datetime *dtStart = this->_timeStart->getDate();
			Datetime *dtStartOrYesterday;

			if(dtStart == 0)
			{ //yesterday
				boost::posix_time::ptime ptStart(boost::posix_time::second_clock::local_time().date());
				ptStart -= boost::gregorian::days(1);
				
				dtStartOrYesterday = new Datetime(
					ptStart.date().year(), ptStart.date().month(), ptStart.date().day(),
					ptStart.time_of_day().hours(), ptStart.time_of_day().minutes(), ptStart.time_of_day().seconds());
			}
			else
			{
				dtStartOrYesterday = new Datetime(*dtStart);
			}

			//if dtStart is older than 140 days, cap it at 140 days
			boost::posix_time::ptime ptOldest(boost::posix_time::second_clock::local_time().date());
			ptOldest -= boost::gregorian::days(140);

			Datetime dtOldest(
				ptOldest.date().year(), ptOldest.date().month(), ptOldest.date().day(),
				ptOldest.time_of_day().hours(), ptOldest.time_of_day().minutes(), ptOldest.time_of_day().seconds());

			if ((*dtStart) < dtOldest) //cap at 140
			{
				delete dtStartOrYesterday;
				dtStartOrYesterday = 0;
				return dtOldest;
			}
			else //no need to cap
			{
				Datetime result(*dtStartOrYesterday);
				delete dtStartOrYesterday;
				dtStartOrYesterday = 0;
				return result;
			}
		}

		const Datetime RequestIntradayTick::getEndDate() const
		{
			Datetime *dtEnd = this->_timeEnd->getDate();

			if(dtEnd == 0)
			{ //right now
				boost::posix_time::ptime ptEnd(boost::posix_time::second_clock::local_time());

				Datetime result(ptEnd.date().year(), ptEnd.date().month(), ptEnd.date().day(),
					ptEnd.time_of_day().hours(), ptEnd.time_of_day().minutes(), ptEnd.time_of_day().seconds());

				return result;
			}
			else
			{
				Datetime result(*dtEnd);
				return result;
			}
		}

		std::vector<Datetime*>* RequestIntradayTick::getDates() //the caller will need to delete these dates
		{
			const Datetime dtStart = this->getStartDate();
			const Datetime dtEnd = this->getEndDate();
			Datetime* dtLoop = new Datetime(dtStart);

			std::vector<Datetime*>* result = new std::vector<Datetime*>();
			while(*dtLoop < dtEnd)
			{
				result->push_back(dtLoop);

				//add a tick interval duration
				boost::gregorian::date dt(dtLoop->year(), dtLoop->month(), dtLoop->day());
				boost::posix_time::time_duration tm(dtLoop->hours(), dtLoop->minutes(), dtLoop->seconds());
				boost::posix_time::ptime pt(dt, tm);
				pt += RandomDataGenerator::IntradayTickInterval();

				//increment the loop counter
				dtLoop = new Datetime(
					pt.date().year(), pt.date().month(), pt.date().day(),
					pt.time_of_day().hours(), pt.time_of_day().minutes(), pt.time_of_day().seconds());

			}

			delete dtLoop; //after the last iteration, dtLoop doesn't get added to the result

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

		Datetime* RequestIntradayTick::dtStart()
		{
			return this->_timeStart->getDate();
		}

		Datetime* RequestIntradayTick::dtEnd()
		{
			return this->_timeEnd->getDate();
		}

		Element RequestIntradayTick::getElement(const char* name)
		{
			if(strncmp(name, "eventTypes", 10) == 0)
			{
				Element result(this->_eventTypes);
				return result;
			}

			else if(strncmp(name, "security", 8) == 0)
			{
				Element result(this->_security);
				return result;
			}

			else if(strncmp(name, "startDateTime", 13) == 0)
			{
				Element result(this->_timeStart);
				return result;
			}

			else if(strncmp(name, "endDateTime", 11) == 0)
			{
				Element result(this->_timeEnd);
				return result;
			}
			
			else if(strncmp(name, "includeConditionCodes", 21) == 0)
			{
				Element result(this->_includeConditionCodes);
				return result;
			}
			
			else if(strncmp(name, "includeNonPlottableEvents", 25) == 0)
			{
				Element result(this->_includeNonPlottableEvents);
				return result;
			}

			else if(strncmp(name, "includeExchangeCodes", 20) == 0)
			{
				Element result(this->_includeExchangeCodes);
				return result;
			}

			else if(strncmp(name, "returnEids", 10) == 0)
			{
				Element result(this->_returnEids);
				return result;
			}

			else if(strncmp(name, "includeBrokerCodes", 18) == 0)
			{
				Element result(this->_includeBrokerCodes);
				return result;
			}

			else if(strncmp(name, "includeRpsCodes", 15) == 0)
			{
				Element result(this->_includeRpsCodes);
				return result;
			}

			else if(strncmp(name, "includeBicMicCodes", 18) == 0)
			{
				Element result(this->_includeBicMicCodes);
				return result;
			}

			else
				throw requestEx;
		}

		void RequestIntradayTick::append(const char* name, const char* value)
		{
			if(strncmp(name, "eventTypes", 10) == 0)
				this->_eventTypes->addValue(value);

			else
				throw requestEx;
		}

		void RequestIntradayTick::set(const char* name, const char* value)
		{
			if(strncmp(name, "security", 8) == 0)
				this->_security = new RequestIntradayTickElementString(std::string(name), value);

			else
				throw requestEx;
		}

		void RequestIntradayTick::set(const char* name, const Datetime& value)
		{
			if(strncmp(name, "startDateTime", 13) == 0)
				this->_timeStart = new RequestIntradayTickElementTime(std::string(name), value);

			else if(strncmp(name, "endDateTime", 11) == 0)
				this->_timeEnd = new RequestIntradayTickElementTime(std::string(name), value);

			else
				throw requestEx;
		}

		void RequestIntradayTick::set(const char* name, bool value)
		{
			if(strncmp(name, "includeConditionCodes", 21) == 0)
				this->_includeConditionCodes = new RequestIntradayTickElementBool(std::string(name), value);
			
			else if(strncmp(name, "includeNonPlottableEvents", 25) == 0)
				this->_includeNonPlottableEvents = new RequestIntradayTickElementBool(std::string(name), value);

			else if(strncmp(name, "includeExchangeCodes", 20) == 0)
				this->_includeExchangeCodes = new RequestIntradayTickElementBool(std::string(name), value);

			else if(strncmp(name, "returnEids", 10) == 0)
				this->_returnEids = new RequestIntradayTickElementBool(std::string(name), value);

			else if(strncmp(name, "includeBrokerCodes", 18) == 0)
				this->_includeBrokerCodes = new RequestIntradayTickElementBool(std::string(name), value);

			else if(strncmp(name, "includeRpsCodes", 15) == 0)
				this->_includeRpsCodes = new RequestIntradayTickElementBool(std::string(name), value);

			else if(strncmp(name, "includeBicMicCodes", 18) == 0)
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