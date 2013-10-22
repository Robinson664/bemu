//------------------------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="headers/IntradayTickRequest/ElementIntradayTickDataParent.h" company="Jordan Robinson">
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

#include "IntradayTickRequest\ElementIntradayTickDataArray.h"
#include "IntradayTickRequest\ElementIntradayTickDataTuple3.h"
#include <map>

#pragma once

namespace BEmu
{
	namespace IntradayTickRequest
	{
		class MessageIntradayTick;

		class ElementIntradayTickDataParent : private ElementPtr
		{
			private:
				ElementIntradayTickDataArray *_array;
				ElementIntradayTickDataParent(std::map<Datetime*, ElementIntradayTickDataTuple3*>* ticks, bool includeConditionCodes);
				~ElementIntradayTickDataParent();

			public:
				virtual Name name() const;
				virtual int numValues() const { return 1; }
				virtual int numElements() const { return 1; }		
				virtual bool isArray() const { return false; }
				virtual bool isComplexType() const { return true; }

				virtual ElementPtr * getElement(const char* name) const;

				virtual std::ostream& print(std::ostream& stream, int level, int spacesPerLevel) const;

				friend class MessageIntradayTick; //The MessageIntradayTick constructor needs access to the ElementIntradayTickDataParent constructor
		};
	}
}