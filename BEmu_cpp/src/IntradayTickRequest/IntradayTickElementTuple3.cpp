//------------------------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="src/IntradayTickRequest/IntradayTickElementTuple3.cpp" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------------------------

#include <iostream>
#include "IntradayTickRequest/IntradayTickElementTuple3.h"

namespace BEmu
{
	namespace IntradayTickRequest
	{
		IntradayTickElementTuple3::IntradayTickElementTuple3(std::string item1, double item2, int item3)
		{
			this->_item1 = item1;
			this->_item2 = item2;
			this->_item3 = item3;
		}

		std::string IntradayTickElementTuple3::item1() const
		{
			return this->_item1;
		}

		double IntradayTickElementTuple3::item2() const
		{
			return this->_item2;
		}

		int IntradayTickElementTuple3::item3() const
		{
			return this->_item3;
		}

	}
}