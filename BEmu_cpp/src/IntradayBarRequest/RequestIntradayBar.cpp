//------------------------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="src/IntradayBarRequest/RequestIntradayBar.cpp" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------------------------

#include "IntradayBarRequest/RequestIntradayBar.h"

#include "IntradayBarRequest/RequestIntradayBarElementInt.h"
#include "IntradayBarRequest/RequestIntradayBarElementBool.h"
#include "IntradayBarRequest/RequestIntradayBarElementTime.h"
#include "IntradayBarRequest/RequestIntradayBarElementString.h"
#include "IntradayBarRequest/RequestIntradayBarElementStringArray.h"


namespace BEmu
{
	namespace IntradayBarRequest
	{
		RequestIntradayBar::RequestIntradayBar(const Service *svc)
		{
			this->_eventTypes = 0;
			this->_service = 0;
			this->_security = 0;
			this->_dtStart = 0;
			this->_dtEnd = 0;
			this->_intervalInMinutes = 0;
			this->_gapFillInitialBar = 0;
			this->_returnEids = 0;
			this->_adjustmentNormalElement = 0;
			this->_adjustmentAbnormalElement = 0;
			this->_adjustmentSplitElement = 0;
			this->_adjustmentFollowDPDF = 0;

			this->_service = svc;
			this->_eventTypes = new RequestIntradayBarElementStringArray("TBD");
			this->_requestType = RequestPtr::intradayBar;
		}

		RequestIntradayBar::~RequestIntradayBar()
		{
			delete this->_eventTypes;
			this->_eventTypes = 0;

			delete this->_service;
			this->_service = 0;

			delete this->_security;
			this->_security = 0;

			delete this->_dtStart;
			this->_dtStart = 0;

			delete this->_dtEnd;
			this->_dtEnd = 0;

			delete this->_intervalInMinutes;
			this->_intervalInMinutes = 0;

			delete this->_gapFillInitialBar;
			this->_gapFillInitialBar = 0;

			delete this->_returnEids;
			this->_returnEids = 0;

			delete this->_adjustmentNormalElement;
			this->_adjustmentNormalElement = 0;

			delete this->_adjustmentAbnormalElement;
			this->_adjustmentAbnormalElement = 0;

			delete this->_adjustmentSplitElement;
			this->_adjustmentSplitElement = 0;

			delete this->_adjustmentFollowDPDF;
			this->_adjustmentFollowDPDF = 0;
		}

		std::vector<Datetime*>* RequestIntradayBar::getDateTimes() const
		{
			//dtStart, dtEnd, and interval are required
			if(this->_dtStart == 0 || this->_dtEnd == 0 || this->_intervalInMinutes == 0)
				throw requestEx;

			int intervalInMinutes = this->_intervalInMinutes->getInt();
			if (intervalInMinutes < 1 || intervalInMinutes > 1440) //if less than one, the loop below will never terminate
				throw requestEx;
			
			Datetime * dtStart = this->_dtStart->getDatetime();
			Datetime * dtEnd = this->_dtEnd->getDatetime();

			if((*dtStart) >= (*dtEnd)) //dtStart must be before dtEnd
				throw requestEx;

			std::vector<Datetime*>* result = new std::vector<Datetime*>();

			Datetime * dtLoop = new Datetime(dtStart->year(), dtStart->month(), dtStart->day(), dtStart->hours(), dtStart->minutes(), dtStart->seconds());
			while( (*dtLoop) < (*dtEnd) )
			{
				result->push_back(new Datetime(*dtLoop));
				dtLoop->addMinutes(this->_intervalInMinutes->getInt());
			}
			delete dtLoop; //after the last iteration, dtLoop doesn't get added to the result

			return result;
		}

		Datetime * RequestIntradayBar::getDtStart() const
		{
			return this->_dtStart->getDatetime();
		}

		Datetime * RequestIntradayBar::getDtEnd() const
		{
			return this->_dtEnd->getDatetime();
		}

		const Service * RequestIntradayBar::getService() const
		{
			return this->_service;
		}

		const std::string& RequestIntradayBar::security() const
		{
			return this->_security->security();
		}

		void RequestIntradayBar::set(const char* name, const char* value)
		{
			if(strncmp(name, "security", 8) == 0)
			{
				this->_security = new RequestIntradayBarElementString(name, value);
			}
			else if(strncmp(name, "eventType", 9) == 0)
			{
				this->_eventTypes->addValue(value);
			}
			else
				throw requestEx;
		}

		void RequestIntradayBar::set(const char* name, const Datetime& elementValue)
		{
			if(strncmp(name, "startDateTime", 13) == 0)
			{
				this->_dtStart = new RequestIntradayBarElementTime(name, elementValue);
			}
			else if(strncmp(name, "endDateTime", 11) == 0)
			{
				this->_dtEnd = new RequestIntradayBarElementTime(name, elementValue);
			}
			else
				throw requestEx;
		}

		void RequestIntradayBar::set(const char* name, int elementValue)
		{
			if(strncmp(name, "interval", 8) == 0)
			{
				this->_intervalInMinutes = new RequestIntradayBarElementInt(name, elementValue);
			}
			else
				throw requestEx;
		}

		void RequestIntradayBar::set(const char* name, bool elementValue)
		{
			if(strncmp(name, "gapFillInitialBar", 8) == 0)
			{
				this->_gapFillInitialBar = new RequestIntradayBarElementBool(name, elementValue);
			}
			else if(strncmp(name, "returnEids", 8) == 0)
			{
				this->_returnEids = new RequestIntradayBarElementBool(name, elementValue);
			}
			else if(strncmp(name, "adjustmentNormal", 8) == 0)
			{
				this->_adjustmentNormalElement = new RequestIntradayBarElementBool(name, elementValue);
			}
			else if(strncmp(name, "adjustmentAbnormal", 8) == 0)
			{
				this->_adjustmentAbnormalElement = new RequestIntradayBarElementBool(name, elementValue);
			}
			else if(strncmp(name, "adjustmentSplit", 8) == 0)
			{
				this->_adjustmentSplitElement = new RequestIntradayBarElementBool(name, elementValue);
			}
			else if(strncmp(name, "adjustmentFollowDPDF", 8) == 0)
			{
				this->_adjustmentFollowDPDF = new RequestIntradayBarElementBool(name, elementValue);
			}
			else
				throw requestEx;
		}

		//std::ostream& RequestIntradayBar::print(std::ostream& stream, int level, int spacesPerLevel) const
		//{
		//	return stream;
		//}



	}
}