//------------------------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="headers/IntradayTickRequest/ElementIntradayTickDataArray.h" company="Jordan Robinson">
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
#include "IntradayTickRequest\ElementIntradayTickData.h"
#include "IntradayTickRequest\ElementIntradayTickDataTuple3.h"
#include <map>
#include <vector>

#pragma once

namespace BEmu
{
	namespace IntradayTickRequest
	{
		class ElementIntradayTickDataParent;

		class ElementIntradayTickDataArray : private ElementPtr
		{
			private:
				std::vector<ElementIntradayTickData*> _tickData;
				ElementIntradayTickDataArray(std::map<Datetime*, ElementIntradayTickDataTuple3*>* ticks, bool includeConditionCodes);
				~ElementIntradayTickDataArray();

			public:
				virtual ElementPtr * getValueAsElement(int index) const;
				virtual Name name() const;

				virtual int numValues() const;
				virtual int numElements() const { return 0; }
		
				virtual bool isArray() const { return true; }
				virtual bool isComplexType() const { return false; }

				virtual std::ostream& print(std::ostream& stream, int level, int spacesPerLevel) const;

				friend class ElementIntradayTickDataParent; //ElementIntradayTickDataParent constructor needs access to the ElementIntradayTickDataArray constructor
		};
	}
}