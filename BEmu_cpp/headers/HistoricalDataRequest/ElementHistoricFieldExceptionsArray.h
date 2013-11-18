//------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="headers/HistoricalDataRequest/ElementHistoricFieldExceptionsArray.h" company="Jordan Robinson">
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
		class ElementHistoricFieldExceptions;

		class ElementHistoricFieldExceptionsArray : public ElementPtr
		{
			private:
				std::vector<ElementHistoricFieldExceptions*> _exceptions;

			public:
				ElementHistoricFieldExceptionsArray(const std::vector<std::string>& badFields);
				~ElementHistoricFieldExceptionsArray();

				virtual Name name() const;
				virtual size_t numValues() const;
				virtual size_t numElements() const;
		
				bool isNull() const;
				virtual bool isArray() const;
				virtual bool isComplexType() const;

				virtual ElementPtr * getValueAsElement(int index) const;

				virtual std::ostream& print(std::ostream& stream, int level = 0, int spacesPerLevel = 4) const;
		};
	}
}