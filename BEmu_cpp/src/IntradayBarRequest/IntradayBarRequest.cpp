//------------------------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="src/IntradayBarRequest/IntradayBarRequest.cpp" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------------------------

#include "IntradayBarRequest/IntradayBarRequest.h"

#include "IntradayBarRequest/IntradayBarRequestElementInt.h"
#include "IntradayBarRequest/IntradayBarRequestElementBool.h"
#include "IntradayBarRequest/IntradayBarRequestElementTime.h"
#include "IntradayBarRequest/IntradayBarRequestElementString.h"
#include "IntradayBarRequest/IntradayBarRequestElementStringArray.h"

#include "BloombergTypes/Service.h"


namespace BEmu
{
	namespace IntradayBarRequest
	{
		IntradayBarRequest::IntradayBarRequest(const Service& svc) :
			_eventTypes(new IntradayBarRequestElementStringArray("TBD"))
		{
			this->_isNull_eventTypes = false;

			this->_isNull_security = true;
			this->_isNull_dtStart = true;
			this->_isNull_dtEnd = true;
			this->_isNull_intervalInMinutes = true;
			this->_isNull_gapFillInitialBar = true;
			this->_isNull_returnEids = true;
			this->_isNull_adjustmentNormalElement = true;
			this->_isNull_adjustmentAbnormalElement = true;
			this->_isNull_adjustmentSplitElement = true;
			this->_isNull_adjustmentFollowDPDF = true;

			//this->_eventTypes = 0;
			//this->_security = 0;
			//this->_dtStart = 0;
			//this->_dtEnd = 0;
			//this->_intervalInMinutes = 0;
			//this->_gapFillInitialBar = 0;
			//this->_returnEids = 0;
			//this->_adjustmentNormalElement = 0;
			//this->_adjustmentAbnormalElement = 0;
			//this->_adjustmentSplitElement = 0;
			//this->_adjustmentFollowDPDF = 0;

			this->_service = svc;
			//this->_eventTypes = new IntradayBarRequestElementStringArray("TBD"); //deleted in the destructor
			this->_requestType = RequestPtr::intradayBar;
		}

		IntradayBarRequest::~IntradayBarRequest()
		{
			//delete this->_eventTypes;
			//this->_eventTypes = 0;

			//delete this->_security;
			//this->_security = 0;

			//delete this->_dtStart;
			//this->_dtStart = 0;

			//delete this->_dtEnd;
			//this->_dtEnd = 0;

			//delete this->_intervalInMinutes;
			//this->_intervalInMinutes = 0;

			//delete this->_gapFillInitialBar;
			//this->_gapFillInitialBar = 0;

			//delete this->_returnEids;
			//this->_returnEids = 0;

			//delete this->_adjustmentNormalElement;
			//this->_adjustmentNormalElement = 0;

			//delete this->_adjustmentAbnormalElement;
			//this->_adjustmentAbnormalElement = 0;

			//delete this->_adjustmentSplitElement;
			//this->_adjustmentSplitElement = 0;

			//delete this->_adjustmentFollowDPDF;
			//this->_adjustmentFollowDPDF = 0;
		}

		std::vector<Datetime> IntradayBarRequest::getDateTimes() const
		{
			//dtStart, dtEnd, and interval are required
			//if(this->_dtStart == 0 || this->_dtEnd == 0 || this->_intervalInMinutes == 0)
			if(this->_isNull_dtStart || this->_isNull_dtEnd || this->_isNull_intervalInMinutes)
				throw requestEx;

			int intervalInMinutes = this->_intervalInMinutes->getInt();
			if (intervalInMinutes < 1 || intervalInMinutes > 1440) //if less than one, the loop below will never terminate
				throw requestEx;
			
			Datetime dtStart = this->_dtStart->getDatetime();
			Datetime dtEnd = this->_dtEnd->getDatetime();

			if(dtStart >= dtEnd) //dtStart must be before dtEnd
				throw requestEx;

			std::vector<Datetime> result;

			Datetime dtLoop(dtStart.year(), dtStart.month(), dtStart.day(), dtStart.hours(), dtStart.minutes(), dtStart.seconds());
			while(dtLoop < dtEnd)
			{
				result.push_back(Datetime(dtLoop));
				dtLoop.addMinutes(this->_intervalInMinutes->getInt());
			}

			return result;
		}

		bool IntradayBarRequest::hasStartDate() const
		{
			return !this->_isNull_dtStart;
			//return this->_dtStart != 0;
		}

		bool IntradayBarRequest::hasEndDate() const
		{
			return !this->_isNull_dtEnd;
			//return this->_dtEnd != 0;
		}

		Datetime IntradayBarRequest::getDtStart() const
		{
			return this->_dtStart->getDatetime();
		}

		Datetime IntradayBarRequest::getDtEnd() const
		{
			return this->_dtEnd->getDatetime();
		}

		const Service IntradayBarRequest::getService() const
		{
			return this->_service;
		}

		const std::string& IntradayBarRequest::security() const
		{
			return this->_security->security();
		}

		void IntradayBarRequest::set(const char* name, const char* value)
		{
			if(strncmp(name, "security", 9) == 0)
			{
				//if(this->_security != 0)
				//	delete this->_security;

				//this->_security = new IntradayBarRequestElementString(name, value); //deleted in destructor

				this->_security = boost::shared_ptr<IntradayBarRequestElementString>(new IntradayBarRequestElementString(name, value));
				this->_isNull_security = false;
			}
			else if(strncmp(name, "eventType", 10) == 0)
			{
				this->_eventTypes->addValue(value);
			}
			else
				throw requestEx;
		}

		void IntradayBarRequest::set(const char* name, const Datetime& elementValue)
		{
			if(strncmp(name, "startDateTime", 14) == 0)
			{
				//if(this->_dtStart != 0)
				//	delete this->_dtStart;

				//this->_dtStart = new IntradayBarRequestElementTime(name, elementValue); //deleted in destructor

				this->_dtStart = boost::shared_ptr<IntradayBarRequestElementTime>(new IntradayBarRequestElementTime(name, elementValue));
				this->_isNull_dtStart = false;
			}
			else if(strncmp(name, "endDateTime", 12) == 0)
			{
				//if(this->_dtEnd != 0)
				//	delete this->_dtEnd;

				//this->_dtEnd = new IntradayBarRequestElementTime(name, elementValue); //deleted in destructor

				this->_dtEnd = boost::shared_ptr<IntradayBarRequestElementTime>(new IntradayBarRequestElementTime(name, elementValue));
				this->_isNull_dtEnd = false;
			}
			else
				throw requestEx;
		}

		void IntradayBarRequest::set(const char* name, int elementValue)
		{
			if(strncmp(name, "interval", 9) == 0)
			{
				//if(this->_intervalInMinutes != 0)
				//	delete this->_intervalInMinutes;

				//this->_intervalInMinutes = new IntradayBarRequestElementInt(name, elementValue); //deleted in destructor

				this->_intervalInMinutes = boost::shared_ptr<IntradayBarRequestElementInt>(new IntradayBarRequestElementInt(name, elementValue));
				this->_isNull_intervalInMinutes = false;
			}
			else
				throw requestEx;
		}

		void IntradayBarRequest::set(const char* name, bool elementValue)
		{
			if(strncmp(name, "gapFillInitialBar", 18) == 0)
			{
				//if(this->_gapFillInitialBar != 0)
				//	delete this->_gapFillInitialBar;

				//this->_gapFillInitialBar = new IntradayBarRequestElementBool(name, elementValue);

				this->_gapFillInitialBar = boost::shared_ptr<IntradayBarRequestElementBool>(new IntradayBarRequestElementBool(name, elementValue));
				this->_isNull_gapFillInitialBar = false;
			}
			else if(strncmp(name, "returnEids", 11) == 0)
			{
				//if(this->_returnEids != 0)
				//	delete this->_returnEids;

				//this->_returnEids = new IntradayBarRequestElementBool(name, elementValue);

				this->_returnEids = boost::shared_ptr<IntradayBarRequestElementBool>(new IntradayBarRequestElementBool(name, elementValue));
				this->_isNull_returnEids = false;
			}
			else if(strncmp(name, "adjustmentNormal", 17) == 0)
			{
				//if(this->_adjustmentNormalElement != 0)
				//	delete this->_adjustmentNormalElement;

				//this->_adjustmentNormalElement = new IntradayBarRequestElementBool(name, elementValue);

				this->_adjustmentNormalElement = boost::shared_ptr<IntradayBarRequestElementBool>(new IntradayBarRequestElementBool(name, elementValue));
				this->_isNull_adjustmentNormalElement = false;
			}
			else if(strncmp(name, "adjustmentAbnormal", 19) == 0)
			{
				//if(this->_adjustmentAbnormalElement != 0)
				//	delete this->_adjustmentAbnormalElement;

				//this->_adjustmentAbnormalElement = new IntradayBarRequestElementBool(name, elementValue);

				this->_adjustmentAbnormalElement = boost::shared_ptr<IntradayBarRequestElementBool>(new IntradayBarRequestElementBool(name, elementValue));
				this->_isNull_adjustmentAbnormalElement = false;
			}
			else if(strncmp(name, "adjustmentSplit", 16) == 0)
			{
				//if(this->_adjustmentSplitElement != 0)
				//	delete this->_adjustmentSplitElement;

				//this->_adjustmentSplitElement = new IntradayBarRequestElementBool(name, elementValue);

				this->_adjustmentSplitElement = boost::shared_ptr<IntradayBarRequestElementBool>(new IntradayBarRequestElementBool(name, elementValue));
				this->_isNull_adjustmentSplitElement = false;
			}
			else if(strncmp(name, "adjustmentFollowDPDF", 21) == 0)
			{
				//if(this->_adjustmentFollowDPDF != 0)
				//	delete this->_adjustmentFollowDPDF;

				//this->_adjustmentFollowDPDF = new IntradayBarRequestElementBool(name, elementValue);

				this->_adjustmentFollowDPDF = boost::shared_ptr<IntradayBarRequestElementBool>(new IntradayBarRequestElementBool(name, elementValue));
				this->_isNull_adjustmentFollowDPDF = false;
			}
			else
				throw requestEx;
		}
	}
}