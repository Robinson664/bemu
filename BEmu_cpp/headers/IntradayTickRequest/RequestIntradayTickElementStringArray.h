//------------------------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="headers/IntradayTickRequest/RequestIntradayTickElementStringArray.h" company="Jordan Robinson">
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

	namespace IntradayTickRequest
	{
		class RequestIntradayTickElementStringArray : public ElementPtr
		{
			private:
				std::string _elementName;
				std::vector<std::string*> _values;
				
			public:
				RequestIntradayTickElementStringArray(const std::string& elementName);
				~RequestIntradayTickElementStringArray();
				void addValue(const std::string& value);
				const std::vector<std::string*>& getValues();

				virtual Name name() const;
				virtual int numValues() const { return 0; }
				virtual int numElements() const;
		
				virtual bool isArray() const { return true; }
				virtual bool isComplexType() const { return false; }
				virtual std::ostream& print(std::ostream& stream, int level, int spacesPerLevel) const;
		};
	}
}