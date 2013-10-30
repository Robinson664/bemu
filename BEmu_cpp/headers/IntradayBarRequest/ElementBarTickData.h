//------------------------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="headers/IntradayBarRequest/ElementBarTickData.h" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------------------------

#pragma once

#include "BloombergTypes/ElementPtr.h"

namespace BEmu
{
	class Name;
	class Datetime;

	namespace IntradayBarRequest
	{
		class BarTickDataType;
		class ElementIntradayBarDateTime;
		class ElementIntradayBarDouble;
		class ElementIntradayBarLong;
		class ElementIntradayBarInt;

		class ElementBarTickData : public ElementPtr
		{
			private:
				ElementIntradayBarDateTime * _time;
				ElementIntradayBarDouble * _open, * _high, * _low, * _close, * _value;
				ElementIntradayBarLong * _volume;
				ElementIntradayBarInt * _numEvents;

			public:
				ElementBarTickData(const BarTickDataType& arg);
				~ElementBarTickData();

				virtual Name name() const;
				virtual int numValues() const;
				virtual int numElements() const;
		
				virtual bool isArray() const;
				virtual bool isComplexType() const;
				
				virtual ElementPtr * getElement(const char* name) const;
				virtual bool hasElement(const char* name, bool excludeNullElements = false) const;
				
				virtual int getElementAsInt32(const char* name) const;
				virtual long getElementAsInt64(const char* name) const;
				virtual Datetime getElementAsDatetime(const char* name) const;
				virtual double getElementAsFloat64(const char* name) const;

				virtual std::ostream& print(std::ostream& stream, int level, int spacesPerLevel) const;
		};
	}
}