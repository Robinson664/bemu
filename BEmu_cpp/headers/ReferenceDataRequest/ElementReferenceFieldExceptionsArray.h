//------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="headers/ReferenceDataRequest/ElementReferenceFieldExceptionsArray.h" company="Jordan Robinson">
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
	class Name;

	namespace ReferenceDataRequest
	{
		class ElementReferenceFieldExceptions;

		class ElementReferenceFieldExceptionsArray : public ElementPtr
		{
			private:
				std::vector<ElementReferenceFieldExceptions*> _exceptions;

			public:
				ElementReferenceFieldExceptionsArray(const std::vector<std::string>& badFields);
				~ElementReferenceFieldExceptionsArray();

				virtual Name name() const;
				virtual size_t numValues() const;
				virtual size_t numElements() const;
		
				virtual bool isNull() const;
				virtual bool isArray() const;
				virtual bool isComplexType() const;

				virtual ElementPtr * getValueAsElement(int index) const;

				virtual std::ostream& print(std::ostream& stream, int level = 0, int spacesPerLevel = 4) const;
		};
	}
}