//------------------------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="headers/IntradayTickRequest/RequestIntradayTickElementString.h" company="Jordan Robinson">
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
		class RequestIntradayTickElementInt;
		class RequestIntradayTickElementBool;
		class RequestIntradayTickElementTime;
		class RequestIntradayTick;

		class RequestIntradayTickElementString : private ElementPtr
		{
			private:
				std::string _elementName, _value;
				RequestIntradayTickElementString(const std::string& elementName, const std::string& value);
				~RequestIntradayTickElementString();
				const std::string& security();
				
			public:
				virtual Name name() const;
				virtual int numValues() const { return 1; }
				virtual int numElements() const { return 0; }

				virtual std::ostream& print(std::ostream& stream, int level = 0, int spacesPerLevel = 4) const;

				//I don't understand this. RequestIntradayTickElementInt inherits from RequestIntradayTickElementString, 
				//  but I still need to declare it a friend so that the RequestIntradayTickElementInt constructor can call the RequestIntradayTickElementString constructor
				friend class RequestIntradayTickElementInt;
				friend class RequestIntradayTickElementBool; //ditto
				friend class RequestIntradayTickElementTime; //ditto ditto

				friend class RequestIntradayTick; //RequestIntradayTick::security needs access to security()
		};
	}
}