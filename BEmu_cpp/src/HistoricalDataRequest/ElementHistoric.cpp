//------------------------------------------------------------------------------
// <copyright project="BEmu" file="src/HistoricalDataRequest/ElementHistoric.cpp" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

#include "HistoricalDataRequest/ElementHistoric.h"
#include "HistoricalDataRequest/ElementHistoricSecurityData.h"
#include "HistoricalDataRequest/MessageHistoric.h"
#include "BloombergTypes/Name.h"

namespace BEmu
{
	namespace HistoricalDataRequest
	{
		ElementHistoric::ElementHistoric(const MessageHistoric& msg)
		{
			this->_security = (ElementHistoricSecurityData*)msg.getElement("securityData");
		}

		ElementHistoric::~ElementHistoric()
		{
		}


		Name ElementHistoric::name() const
		{
			Name result("securityData");
			return result;
		}

		size_t ElementHistoric::numValues() const
		{
			return 1;
		}

		size_t ElementHistoric::numElements() const
		{
			return 1;
		}

		
		bool ElementHistoric::isNull() const
		{
			return false;
		}

		bool ElementHistoric::isArray() const
		{
			return false;
		}

		bool ElementHistoric::isComplexType() const
		{
			return true;
		}


		std::ostream& ElementHistoric::print(std::ostream& stream, int level, int spacesPerLevel) const
		{
			stream << "HistoricalDataResponse (choice) = {" << std::endl;
			this->_security->print(stream, level + 1, spacesPerLevel);
			stream << '}' << std::endl;

			return stream;
		}

	}
}