//------------------------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="src/IntradayBarRequest/ElementBarTickData.cpp" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------------------------

#include "BloombergTypes/Name.h"
#include "BloombergTypes/Datetime.h"
#include "BloombergTypes/ElementPtr.h"
#include "Types/IndentType.h"
#include "IntradayBarRequest/BarTickDataType.h"
#include "IntradayBarRequest/ElementBarTickData.h"
#include "IntradayBarRequest/ElementIntradayBarDateTime.h"
#include "IntradayBarRequest/ElementIntradayBarDouble.h"
#include "IntradayBarRequest/ElementIntradayBarLong.h"
#include "IntradayBarRequest/ElementIntradayBarInt.h"

namespace BEmu
{
	namespace IntradayBarRequest
	{
		ElementBarTickData::ElementBarTickData(const BarTickDataType& arg)
		{
			Datetime * dtTime = arg.getDatetime();
			this->_time = new ElementIntradayBarDateTime("time", *dtTime);
			
			this->_open = new ElementIntradayBarDouble("open", arg.getOpen());
			this->_high = new ElementIntradayBarDouble("high", arg.getHigh());
			this->_low = new ElementIntradayBarDouble("low", arg.getLow());
			this->_close = new ElementIntradayBarDouble("close", arg.getClose());
			this->_value = new ElementIntradayBarDouble("value", arg.getValue());
			this->_volume = new ElementIntradayBarLong("volume", arg.getVolume());
			this->_numEvents = new ElementIntradayBarInt("numEvents", arg.getNumevents());
		}

		ElementBarTickData::~ElementBarTickData()
		{
			delete this->_time;
			this->_time = 0;
			
			delete this->_open;
			this->_open = 0;
			
			delete this->_high;
			this->_high = 0;
			
			delete this->_low;
			this->_low = 0;
			
			delete this->_close;
			this->_close = 0;
			
			delete this->_value;
			this->_value = 0;
			
			delete this->_volume;
			this->_volume = 0;
			
			delete this->_numEvents;
			this->_numEvents = 0;
		}

		Name ElementBarTickData::name() const
		{
			Name result("barTickData");
			return result;
		}

		int ElementBarTickData::numValues() const
		{
			return 0;
		}

		int ElementBarTickData::numElements() const
		{
			return 8;
		}

		bool ElementBarTickData::isArray() const
		{
			return false;
		}

		bool ElementBarTickData::isComplexType() const
		{
			return true;
		}

		ElementPtr * ElementBarTickData::getElement(const char* name) const
		{
			if(strncmp(name, "time", 4) == 0)
				return this->_time;

			else if(strncmp(name, "open", 4) == 0)
				return this->_open;

			else if(strncmp(name, "high", 4) == 0)
				return this->_high;

			else if(strncmp(name, "low", 3) == 0)
				return this->_low;

			else if(strncmp(name, "close", 5) == 0)
				return this->_close;

			else if(strncmp(name, "value", 5) == 0)
				return this->_value;

			else if(strncmp(name, "volume", 6) == 0)
				return this->_volume;

			else if(strncmp(name, "numEvents", 6) == 0)
				return this->_numEvents;

			else
				throw elementPtrEx;
		}

		bool ElementBarTickData::hasElement(const char* name, bool excludeNullElements) const
		{
			return
				(strncmp(name, "time", 4) == 0) ||
				(strncmp(name, "open", 4) == 0) ||
				(strncmp(name, "high", 4) == 0) ||
				(strncmp(name, "low", 3) == 0) ||
				(strncmp(name, "close", 5) == 0) ||
				(strncmp(name, "value", 5) == 0) ||
				(strncmp(name, "volume", 6) == 0) ||
				(strncmp(name, "numEvents", 6) == 0);
		}

		int ElementBarTickData::getElementAsInt32(const char* name) const
		{
			return this->getElement(name)->getValueAsInt32(0);
		}

		long ElementBarTickData::getElementAsInt64(const char* name) const
		{
			return this->getElement(name)->getValueAsInt64(0);
		}

		Datetime ElementBarTickData::getElementAsDatetime(const char* name) const
		{
			return this->getElement(name)->getValueAsDatetime(0);
		}

		double ElementBarTickData::getElementAsFloat64(const char* name) const
		{
			return this->getElement(name)->getValueAsFloat64(0);
		}

		std::ostream& ElementBarTickData::print(std::ostream& stream, int level, int spacesPerLevel) const
		{
			std::string tabs(IndentType::Indent(level, spacesPerLevel));

			stream << tabs << "barTickData = {" << std::endl;
			this->_time->print(stream, level + 1, spacesPerLevel);
			this->_open->print(stream, level + 1, spacesPerLevel);
			this->_high->print(stream, level + 1, spacesPerLevel);
			this->_low->print(stream, level + 1, spacesPerLevel);
			this->_close->print(stream, level + 1, spacesPerLevel);
			this->_value->print(stream, level + 1, spacesPerLevel);
			this->_volume->print(stream, level + 1, spacesPerLevel);
			this->_numEvents->print(stream, level + 1, spacesPerLevel);
			stream << tabs << '}' << std::endl;

			return stream;
		}


	}
}