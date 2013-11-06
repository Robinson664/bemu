//------------------------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="headers/IntradayTickRequest/ElementIntradayTickData.h" company="Jordan Robinson">
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

	namespace IntradayTickRequest
	{
		class ElementIntradayTickDateTime;
		class ElementIntradayTickDouble;
		class ElementIntradayTickInt;
		class ElementIntradayTickString;
		class ElementIntradayTickDataTuple3;

		class ElementIntradayTickData : public ElementPtr
		{
			private:
				bool _includeConditionCodes;

				ElementIntradayTickDateTime * _time;
				ElementIntradayTickDouble * _value;
				ElementIntradayTickInt * _size;
				ElementIntradayTickString * _type, * _conditionCodes;
				
			public:
				ElementIntradayTickData(const Datetime& datetime, const ElementIntradayTickDataTuple3& arg, bool includeConditionCodes);
				~ElementIntradayTickData();

				virtual Name name() const;
				virtual size_t numValues() const { return 1; }
				virtual size_t numElements() const { return 0; }
		
				virtual bool isArray() const { return false; }
				virtual bool isComplexType() const { return false; }

				virtual bool hasElement(const char* name, bool excludeNullElements = false) const;
				virtual ElementPtr * getElement(int position) const;
				virtual ElementPtr * getElement(const char* name) const;

				virtual int getElementAsInt32(const char* name) const;
				virtual Datetime getElementAsDatetime(const char* name) const;
				virtual const char* getElementAsString(const char* name) const;

				virtual std::ostream& print(std::ostream& stream, int level, int spacesPerLevel) const;
		};
	}
}