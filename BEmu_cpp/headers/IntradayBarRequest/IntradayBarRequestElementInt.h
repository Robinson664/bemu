//------------------------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="headers/IntradayBarRequest/IntradayBarRequestElementInt.h" company="Jordan Robinson">
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
		class IntradayBarRequestElementInt : public IntradayBarRequestElementString
		{
			private:
				int _ivalue;

			public:
				IntradayBarRequestElementInt(const std::string& elementName, int ivalue);
				~IntradayBarRequestElementInt();
				int getInt() const;
		};
	}
}