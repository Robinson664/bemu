//------------------------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="headers/IntradayTickRequest/RequestIntradayTickElementString.h" company="Jordan Robinson">
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
	class Name;

	namespace IntradayTickRequest
	{
		class RequestIntradayTickElementString : public ElementPtr
		{
			private:
				std::string _elementName, _value;
				
			public:
				RequestIntradayTickElementString(const std::string& elementName, const std::string& value);
				~RequestIntradayTickElementString();
				const std::string& security();

				virtual Name name() const;
				virtual int numValues() const { return 1; }
				virtual int numElements() const { return 0; }

				virtual std::ostream& print(std::ostream& stream, int level = 0, int spacesPerLevel = 4) const;
		};
	}
}