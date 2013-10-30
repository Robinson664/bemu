//------------------------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="src/IntradayTickRequest/ElementIntradayTickDataTuple3.cpp" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------------------------

#include <iostream>
#include "IntradayTickRequest/ElementIntradayTickDataTuple3.h"

namespace BEmu
{
	namespace IntradayTickRequest
	{
		ElementIntradayTickDataTuple3::ElementIntradayTickDataTuple3(std::string item1, double item2, int item3)
		{
			this->_item1 = item1;
			this->_item2 = item2;
			this->_item3 = item3;
		}

		std::string ElementIntradayTickDataTuple3::item1() const
		{
			return this->_item1;
		}

		double ElementIntradayTickDataTuple3::item2() const
		{
			return this->_item2;
		}

		int ElementIntradayTickDataTuple3::item3() const
		{
			return this->_item3;
		}

	}
}