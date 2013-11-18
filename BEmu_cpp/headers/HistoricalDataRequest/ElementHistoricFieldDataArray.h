//------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="headers/HistoricalDataRequest/ElementHistoricFieldDataArray.h" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

#pragma once

#include "BloombergTypes/ElementPtr.h"
#include <vector>
#include <map>

namespace BEmu
{
	class ObjectType;

	namespace HistoricalDataRequest
	{
		class ElementHistoricFieldData;

		class ElementHistoricFieldDataArray : public ElementPtr
		{
			private:
				std::vector<ElementHistoricFieldData*> _fieldData;

			public:
				ElementHistoricFieldDataArray(const std::map<Datetime, std::map<std::string, ObjectType>*> * fieldData);
				~ElementHistoricFieldDataArray();

				virtual ElementPtr * getValueAsElement(int index) const;

				virtual Name name() const;
				virtual size_t numValues() const;
				virtual size_t numElements() const;
		
				bool isNull() const;
				virtual bool isArray() const;
				virtual bool isComplexType() const;

				virtual std::ostream& print(std::ostream& stream, int level = 0, int spacesPerLevel = 4) const;
		};
	}
}