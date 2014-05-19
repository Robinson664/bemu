//------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="headers/ReferenceDataRequest/ReferenceElementObject.h" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

#pragma once

#include "BloombergTypes/ElementPtr.h"
#include "Types/ObjectType.h"

namespace BEmu
{
	class Name;

	namespace ReferenceDataRequest
	{
		class ReferenceElementObject : public ElementPtr
		{
			private:
				ObjectType _value;
				std::string _name;
				const char * _cstr;

			public:
				ReferenceElementObject(std::string name, ObjectType value);
				~ReferenceElementObject();

				virtual Name name() const;
				virtual size_t numValues() const;
				virtual size_t numElements() const;
		
				virtual bool isNull() const;
				virtual bool isArray() const;
				virtual bool isComplexType() const;

				void setName(const std::string& name);
				void setValue(const ObjectType& value);

				virtual const char * getValueAsString(int index) const;

				virtual std::ostream& print(std::ostream& stream, int level = 0, int spacesPerLevel = 4) const;
		};
	}
}