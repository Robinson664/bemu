//------------------------------------------------------------------------------
// <copyright project="BEmu" file="src/HistoricalDataRequest/RequestHistoricElementString.cpp" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

#include "HistoricalDataRequest/RequestHistoricElementString.h"
#include "BloombergTypes/Name.h"
#include "Types/IndentType.h"

namespace BEmu
{
	namespace HistoricalDataRequest
	{
		RequestHistoricElementString::RequestHistoricElementString(const std::string& elementName, const std::string& value)
		{
			this->_elementName = elementName;
			this->_value = value;
		}

		RequestHistoricElementString::~RequestHistoricElementString()
		{
		}


		Name RequestHistoricElementString::name() const
		{
			Name result(this->_elementName.c_str());
			return result;
		}

		size_t RequestHistoricElementString::numValues() const
		{
			return 1;
		}

		size_t RequestHistoricElementString::numElements() const
		{
			return 0;
		}


		std::ostream& RequestHistoricElementString::print(std::ostream& stream, int level, int spacesPerLevel) const
		{
			std::string tabs = IndentType::Indent(level, spacesPerLevel);
			stream << tabs << this->_elementName << " = " << this->_value << std::endl;
			return stream;
		}

	}
}