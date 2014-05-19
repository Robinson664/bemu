//------------------------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="src/IntradayBarRequest/BarTickDataType.cpp" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------------------------

#include "BloombergTypes/Datetime.h"
#include "IntradayBarRequest/BarTickDataType.h"

namespace BEmu
{
	namespace IntradayBarRequest
	{
		BarTickDataType::BarTickDataType(const Datetime& dtTime, double open, double high, double low, double close, double value, long volume, int numEvents)
		{
			this->_open = open;
			this->_high = high;
			this->_low = low;
			this->_close = close;
			this->_value = value;
			this->_volume = volume;
			this->_numEvents = numEvents;

			this->_dtTime = dtTime;
		}

		BarTickDataType::~BarTickDataType()
		{
		}

		BarTickDataType::BarTickDataType(const BarTickDataType& arg)
		{
			this->_open = arg._open;
			this->_high = arg._high;
			this->_low = arg._low;
			this->_close = arg._close;
			this->_value = arg._value;
			this->_volume = arg._volume;
			this->_numEvents = arg._numEvents;
			
			this->_dtTime = arg._dtTime;
		}

		BarTickDataType& BarTickDataType::operator=(const BarTickDataType &rhs)
		{
			if (this != &rhs)
			{
				this->_open = rhs._open;
				this->_high = rhs._high;
				this->_low = rhs._low;
				this->_close = rhs._close;
				this->_value = rhs._value;
				this->_volume = rhs._volume;
				this->_numEvents = rhs._numEvents;
			
				this->_dtTime = rhs._dtTime;
			}
			return *this;
		}

		Datetime BarTickDataType::getDatetime() const
		{
			return this->_dtTime;
		}
		
		double BarTickDataType::getOpen() const
		{
			return this->_open;
		}

		double BarTickDataType::getHigh() const
		{
			return this->_high;
		}

		double BarTickDataType::getLow() const
		{
			return this->_low;
		}

		double BarTickDataType::getClose() const
		{
			return this->_close;
		}

		double BarTickDataType::getValue() const
		{
			return this->_value;
		}

		long BarTickDataType::getVolume() const
		{
			return this->_volume;
		}

		int BarTickDataType::getNumevents() const
		{
			return this->_numEvents;
		}
	}
}