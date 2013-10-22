//------------------------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="headers/IntradayTickRequest/ElementIntradayTickData.h" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------------------------

#include "bemu_headers.h"
#include "BloombergTypes\Name.h"
#include "BloombergTypes\ElementPtr.h"
#include "BloombergTypes\Datetime.h"
#include "IntradayTickRequest\ElementIntradayTickDataTuple3.h"
#include "IntradayTickRequest\ElementIntradayTickDateTime.h"
#include "IntradayTickRequest\ElementIntradayTickString.h"
#include "IntradayTickRequest\ElementIntradayTickDouble.h"
#include "IntradayTickRequest\ElementIntradayTickInt.h"

#pragma once

namespace BEmu
{
	namespace IntradayTickRequest
	{
		class ElementIntradayTickDataArray;

		class ElementIntradayTickData : private ElementPtr
		{
			private:
				bool _includeConditionCodes;

				ElementIntradayTickDateTime * _time;
				ElementIntradayTickDouble * _value;
				ElementIntradayTickInt * _size;
				ElementIntradayTickString * _type, * _conditionCodes;

				ElementIntradayTickData(const Datetime& datetime, const ElementIntradayTickDataTuple3& arg, bool includeConditionCodes);
				~ElementIntradayTickData();

			public:
				virtual Name name() const;
				virtual int numValues() const { return 1; }
				virtual int numElements() const { return 0; }
		
				virtual bool isArray() const { return false; }
				virtual bool isComplexType() const { return false; }

				virtual bool hasElement(const char* name, bool excludeNullElements = false) const;
				virtual ElementPtr * getElement(int position) const;
				virtual ElementPtr * getElement(const char* name) const;

				virtual int getElementAsInt32(const char* name) const;
				virtual Datetime getElementAsDatetime(const char* name) const;
				virtual const char* getElementAsString(const char* name) const;

				virtual std::ostream& print(std::ostream& stream, int level, int spacesPerLevel) const;

				friend class ElementIntradayTickDataArray; //ElementIntradayTickDataArray constructor needs access to the ElementIntradayTickData constructor
		};
	}
}