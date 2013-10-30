//------------------------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="headers/IntradayBarRequest/ElementBarData.h" company="Jordan Robinson">
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
		class ElementBarTickDataArray;

		class ElementBarData : public ElementPtr
		{
			private:
				ElementBarTickDataArray * _array;

			public:
				ElementBarData(const std::vector<BarTickDataType*>& bars);
				~ElementBarData();

				virtual Name name() const;
				virtual int numValues() const;
				virtual int numElements() const;
		
				virtual bool isArray() const;
				virtual bool isComplexType() const;

				virtual ElementPtr * getElement(const char* name) const;

				virtual std::ostream& print(std::ostream& stream, int level, int spacesPerLevel) const;
		};
	}
}