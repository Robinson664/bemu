//------------------------------------------------------------------------------
// <copyright project="BEmu" file="headers/HistoricalDataRequest/RequestHistoric.h" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

#pragma once

#include "BloombergTypes/RequestPtr.h"
#include <vector>

namespace BEmu
{
	namespace HistoricalDataRequest
	{
		namespace HistDataPeriodicityAdjustmentEnum
		{
			enum EnumType { actual, calendar, fiscal };
		}

		namespace HistDataPeriodicityEnum
		{
			enum EnumType { daily, weekly, monthly, quarterly, semi_annually, yearly };
		}

		namespace PricingOptionEnum
		{
			enum EnumType { price, yield };
		}

		namespace OverrideOptionsEnum
		{
			enum EnumType { closingPrice, averagePrice };
		}

		class RequestHistoricElementStringArray;
		class RequestHistoricElementDate;
		class RequestHistoricElementBool;
		class RequestHistoricElementInt;
		class RequestHistoricElementString;

		class RequestHistoric : public RequestPtr
		{
			private:
				RequestHistoricElementStringArray * _securities, * _fields;
				RequestHistoricElementDate * _dtStart, * _dtEnd;
				RequestHistoricElementBool * _adjustmentNormalElement, * _adjustmentAbnormalElement, * _adjustmentSplitElement;
				RequestHistoricElementInt * _maxDataPointElement;
				RequestHistoricElementString * _periodicityAdjustmentElement, * _periodicityElement, * _overrideOptionsElement, * _pricingOptionElement;

				HistDataPeriodicityAdjustmentEnum::EnumType _periodicityAdjustment;
				HistDataPeriodicityEnum::EnumType _periodicity;
				PricingOptionEnum::EnumType _pricingOption;
				OverrideOptionsEnum::EnumType _overrideOptions;

			public:
				RequestHistoric();
				~RequestHistoric();

				std::vector<std::string> securities() const;
				std::vector<std::string> fields() const;
				Datetime dtStart() const;
				Datetime dtEnd() const;

				std::vector<Datetime> * getDates() const;
				std::vector<Datetime> * getDatesBeforeMaxPoints() const;
				
				bool hasStartDate() const;
				bool hasEndDate() const;

				virtual void append(const char* name, const char* value);

				virtual void set(const char* name, const char* value);
				virtual void set(const char* name, bool value);
				virtual void set(const char* name, int value);
		};
	}
}