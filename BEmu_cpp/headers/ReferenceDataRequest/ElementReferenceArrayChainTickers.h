//------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="headers/ReferenceDataRequest/ElementReferenceArrayChainTickers.h" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

#pragma once

#include "ReferenceDataRequest/ElementReferenceArray.h"

namespace BEmu
{
	namespace ReferenceDataRequest
	{
		namespace OptionalityEnum
		{
			enum EnumType { put, call };
		}

		class ElementReferenceArrayChainTickers : public ElementReferenceArray
		{
			private:
			public:
				ElementReferenceArrayChainTickers(const std::string& underlier, unsigned numPoints, const std::string& strDtExp, OptionalityEnum::EnumType optionality);
		};
	}
}