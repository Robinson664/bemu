//------------------------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="headers/IntradayTickRequest/ElementIntradayTickDateTime.h" company="Jordan Robinson">
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
	class Datetime;
	class Name;

	namespace IntradayTickRequest
	{
		class ElementIntradayTickDateTime : public ElementPtr
		{
			private:
				Datetime* _value;
				std::string _name;

			public:
				ElementIntradayTickDateTime(const std::string& name, const Datetime& value);
				~ElementIntradayTickDateTime();

				virtual Name name() const;
				virtual int numValues() const { return 1; }
				virtual int numElements() const { return 0; }
		
				virtual bool isArray() const { return false; }
				virtual bool isComplexType() const { return false; }

				virtual bool hasElement(const char* name, bool excludeNullElements = false) const;
				
				virtual Datetime getValueAsDatetime(int index) const;
				virtual char* getValueAsString(int index) const;

				virtual std::ostream& print(std::ostream& stream, int level, int spacesPerLevel) const;
		};
	}
}