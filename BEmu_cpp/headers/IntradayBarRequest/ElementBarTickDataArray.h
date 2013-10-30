//------------------------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="headers/IntradayBarRequest/ElementBarTickDataArray.h" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------------------------

#pragma once

#include "BloombergTypes/ElementPtr.h"
#include <vector>

namespace BEmu
{
	class Name;

	namespace IntradayBarRequest
	{
		class BarTickDataType;
		class ElementBarTickData;

		class ElementBarTickDataArray : public ElementPtr
		{
			private:
				std::vector<ElementBarTickData*> _elements;

			public:
				ElementBarTickDataArray(const std::vector<BarTickDataType*>& bars);
				~ElementBarTickDataArray();

				virtual Name name() const;
				virtual int numValues() const;
				virtual int numElements() const;
		
				virtual bool isArray() const;
				virtual bool isComplexType() const;

				virtual ElementPtr * getValueAsElement(int index) const;

				virtual std::ostream& print(std::ostream& stream, int level, int spacesPerLevel) const;
		};
	}
}