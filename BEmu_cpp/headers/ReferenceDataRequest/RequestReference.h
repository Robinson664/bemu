//------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="headers/ReferenceDataRequest/ReferenceRequest.h" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

#pragma once

#include "BloombergTypes/RequestPtr.h"
#include <vector>

namespace BEmu
{
	namespace ReferenceDataRequest
	{
		class ReferenceRequestElementStringArray;
		class ReferenceRequestElementOverrideArray;

		class ReferenceRequest : public RequestPtr
		{
			private:
				ReferenceRequestElementStringArray * _securities, * _fields;
				ReferenceRequestElementOverrideArray * _overrides;

			public:
				ReferenceRequest();
				~ReferenceRequest();
				
				std::vector<std::string> getSecurities() const;
				std::vector<std::string> getFields() const;

				bool hasElement(std::string arg) const; //note that while the C# and Java versions of Request have a DLL_EXPORT hasElement() function, the C++ version does not

				virtual Element getElement(const char* name);

				virtual void append(const char* name, const char* value);
		};
	}
}