//------------------------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="headers/IntradayBarRequest/IntradayBarRequestElementBool.h" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------------------------

#pragma once

#include "IntradayBarRequest/IntradayBarRequestElementString.h"

namespace BEmu
{
	namespace IntradayBarRequest
	{
		class IntradayBarRequestElementBool : public IntradayBarRequestElementString
		{
			private:
				bool _bvalue;

			public:
				IntradayBarRequestElementBool(const std::string& elementName, bool bvalue);
				~IntradayBarRequestElementBool();
				bool getBool() const;
		};
	}
}