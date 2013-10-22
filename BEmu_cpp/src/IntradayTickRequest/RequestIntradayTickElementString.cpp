//------------------------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="src/IntradayTickRequest/RequestIntradayTickElementString.cpp" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------------------------

#include "bemu_headers.h"
#include "IntradayTickRequest/RequestIntradayTickElementString.h"
#include "BloombergTypes/Name.h"
#include "BloombergTypes/Element.h"
#include "Types/IndentType.h"

namespace BEmu
{
	namespace IntradayTickRequest
	{
		RequestIntradayTickElementString::RequestIntradayTickElementString(const std::string& elementName, const std::string& value)
		{
			this->_elementName = elementName;
			this->_value = value;
		}

		RequestIntradayTickElementString::~RequestIntradayTickElementString()
		{
			//delete this->_elementName;
			//delete this->_value;
		}

		const std::string& RequestIntradayTickElementString::security()
		{
			return this->_value;
		}

		Name RequestIntradayTickElementString::name() const
		{
			Name result(this->_elementName.c_str());
			return result;
		}

		std::ostream& RequestIntradayTickElementString::print(std::ostream& stream, int level, int spacesPerLevel) const
		{
			std::string tabs = IndentType::Indent(level, spacesPerLevel);
			stream << tabs << this->_elementName << " = " << std::endl;
			return stream;
		}

	}
}