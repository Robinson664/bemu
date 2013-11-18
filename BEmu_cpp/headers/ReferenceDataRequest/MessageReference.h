//------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="headers/ReferenceDataRequest/MessageReference.h" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

#pragma once

#include "BloombergTypes/MessagePtr.h"
#include "Types/ObjectType.h"
#include <map>

namespace BEmu
{
	class CorrelationId;

	namespace ReferenceDataRequest
	{
		class ElementReferenceSecurityDataArray;

		class MessageReference : public MessagePtr
		{
			private:
				ElementReferenceSecurityDataArray * _securities;

			public:
				MessageReference(const CorrelationId& corr, const std::map<std::string, std::map<std::string, ObjectType>*>& fieldData);
				~MessageReference();

				virtual ElementPtr * getElement(const char* name) const;

				virtual const char* topicName() const;
				virtual ElementPtr * asElement() const;
				ElementPtr * firstElement() const;

				virtual std::ostream& print(std::ostream& stream, int level = 0, int spacesPerLevel = 4) const;
		};
	}
}