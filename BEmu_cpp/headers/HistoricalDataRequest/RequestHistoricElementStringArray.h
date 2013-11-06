//------------------------------------------------------------------------------
// <copyright project="BEmu" file="headers/HistoricalDataRequest/RequestHistoricElementStringArray.h" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

#pragma once

#include "BloombergTypes/ElementPtr.h"
#include <vector>

namespace BEmu
{
	namespace HistoricalDataRequest
	{
		class RequestHistoricElementStringArray : public ElementPtr
		{
			private:
				std::string _elementName;
				std::vector<std::string> _values;

			public:
				RequestHistoricElementStringArray(const std::string& elementName);
				~RequestHistoricElementStringArray();

				virtual Name name() const;
				virtual size_t numValues() const;
				virtual size_t numElements() const;
		
				bool isNull() const;
				virtual bool isArray() const;
				virtual bool isComplexType() const;

				void addValue(const std::string& value);
				std::vector<std::string> values() const;

				virtual std::ostream& print(std::ostream& stream, int level = 0, int spacesPerLevel = 4) const;
		};
	}
}