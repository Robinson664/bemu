//------------------------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="headers/IntradayTickRequest/ElementReference.h" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------------------------

#include "bemu_headers.h"
#include "BloombergTypes\Name.h"
#include "BloombergTypes\ElementPtr.h"
#include "IntradayTickRequest/ElementIntradayTickDataParent.h"

#pragma once

namespace BEmu
{
	namespace IntradayTickRequest
	{
		class MessageIntradayTick;

		class ElementReference : private ElementPtr
		{
			private:
				ElementPtr *_parent;
				ElementReference(const MessageIntradayTick& msg);

			public:
				virtual Name name() const;
				virtual int numValues() const { return 1; }
				virtual int numElements() const { return 1; }				
		
				virtual bool isArray() const { return false; }
				virtual bool isComplexType() const { return false; }
				virtual ElementPtr * getElement(const char* name) const;

				virtual std::ostream& print(std::ostream& stream, int level, int spacesPerLevel) const;

				friend class MessageIntradayTick;
		};
	}
}