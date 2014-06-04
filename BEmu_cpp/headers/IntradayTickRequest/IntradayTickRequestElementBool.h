//------------------------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="headers/IntradayTickRequest/IntradayTickRequestElementBool.h" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------------------------

#pragma once

#include "IntradayTickRequest/IntradayTickRequestElementString.h"

namespace BEmu
{
	namespace IntradayTickRequest
	{
		class IntradayTickRequestElementBool : public IntradayTickRequestElementString
		{
			private:
				bool _bvalue;

			public:
				IntradayTickRequestElementBool(const std::string& elementName, bool bvalue);
				~IntradayTickRequestElementBool();

				bool getBool();
		};
	}
}