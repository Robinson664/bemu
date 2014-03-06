//------------------------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="headers/IntradayTickRequest/ElementIntradayTickDataArray.h" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------------------------

#pragma once

#include <map>
#include <vector>
#include "BloombergTypes/ElementPtr.h"

namespace BEmu
{
	class Name;
	class Datetime;

	namespace IntradayTickRequest
	{
		class ElementIntradayTickData;
		class ElementIntradayTickDataTuple3;

		class ElementIntradayTickDataArray : public ElementPtr
		{
			private:
				std::vector<ElementIntradayTickData*> _tickData;

			public:
				ElementIntradayTickDataArray(std::map<Datetime, ElementIntradayTickDataTuple3*>* ticks, bool includeConditionCodes);
				~ElementIntradayTickDataArray();

				virtual ElementPtr * getValueAsElement(int index) const;
				virtual Name name() const;

				virtual size_t numValues() const;
				virtual size_t numElements() const { return 0; }
				virtual SchemaElementDefinition elementDefinition() const;
		
				virtual bool isArray() const { return true; }
				virtual bool isComplexType() const { return false; }

				virtual std::ostream& print(std::ostream& stream, int level, int spacesPerLevel) const;
		};
	}
}