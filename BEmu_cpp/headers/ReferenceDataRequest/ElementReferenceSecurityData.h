//------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="headers/ReferenceDataRequest/ElementReferenceSecurityData.h" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

#pragma once

#include "BloombergTypes/ElementPtr.h"
#include "Types/ObjectType.h"
#include <map>

namespace BEmu
{
	class Name;

	namespace ReferenceDataRequest
	{
        class ElementReferenceString;
        class ElementReferenceInt;
        class ElementReferenceFieldData;
        class ElementReferenceFieldExceptionsArray;
        class ElementReferenceSecurityError;

		class ElementReferenceSecurityData : public ElementPtr
		{
			private:
				ElementReferenceString * _elmSecurityName;
				ElementReferenceInt * _elmSequenceNumber;
				ElementReferenceFieldData * _elmFieldData;
				ElementReferenceFieldExceptionsArray * _elmFieldExceptions;
				ElementReferenceSecurityError * _elmSecError;
				bool _isSecurityError;

			public:
				ElementReferenceSecurityData(const std::string& securityName, std::map<std::string, ObjectType> * fieldData, int sequenceNumber);
				~ElementReferenceSecurityData();

				virtual Name name() const;
				virtual size_t numValues() const;
				virtual size_t numElements() const;
				virtual SchemaElementDefinition elementDefinition() const;

				virtual const char* getElementAsString(const char* name) const;
				virtual ElementPtr * getElement(const char* name) const;
				virtual bool hasElement(const char* name, bool excludeNullElements = false) const;

				virtual std::ostream& print(std::ostream& stream, int level = 0, int spacesPerLevel = 4) const;
		};
	}
}