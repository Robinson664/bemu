//------------------------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="headers/IntradayTickRequest/ElementIntradayTickString.h" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------------------------

#include "bemu_headers.h"
#include "BloombergTypes\Name.h"
#include "BloombergTypes\ElementPtr.h"

#pragma once

namespace BEmu
{
	namespace IntradayTickRequest
	{
		class ElementIntradayTickData;
		class ElementIntradayTickResponseError;

		class ElementIntradayTickString : private ElementPtr
		{
			private:
				std::string _value;
				std::string _name;
				ElementIntradayTickString(const std::string& name, const std::string& value);
				~ElementIntradayTickString();

			public:
				virtual Name name() const;
				virtual int numValues() const { return 1; }
				virtual int numElements() const { return 0; }
		
				virtual bool isArray() const { return false; }
				virtual bool isComplexType() const { return false; }

				virtual bool hasElement(const char* name, bool excludeNullElements = false) const;
				virtual char* getValueAsString(int index) const;

				virtual std::ostream& print(std::ostream& stream, int level, int spacesPerLevel) const;

				friend class ElementIntradayTickData; //ElementIntradayTickData constructor needs access to the ElementIntradayTickString constructor
				friend class ElementIntradayTickResponseError; //ElementIntradayTickResponseError constructor needs access to the ElementIntradayTickString constructor
		};
	}
}