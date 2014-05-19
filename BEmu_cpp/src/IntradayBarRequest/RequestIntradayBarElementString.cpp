//------------------------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="src/IntradayBarRequest/RequestIntradayBarElementString.cpp" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------------------------

#include "BloombergTypes/Name.h"
#include "BloombergTypes/ElementPtr.h"
#include "IntradayBarRequest/RequestIntradayBarElementString.h"

namespace BEmu
{
	namespace IntradayBarRequest
	{
		RequestIntradayBarElementString::RequestIntradayBarElementString(const std::string& elementName, const std::string& value)
		{
			this->_elementName = elementName;
			this->_value = value;
		}

		RequestIntradayBarElementString::~RequestIntradayBarElementString()
		{
		}

		Name RequestIntradayBarElementString::name() const
		{
			Name result(this->_elementName.c_str());
			return result;
		}

		const std::string& RequestIntradayBarElementString::security() const
		{
			return this->_value;
		}

		size_t RequestIntradayBarElementString::numValues() const
		{
			return 1;
		}

		size_t RequestIntradayBarElementString::numElements() const
		{
			return 0;
		}

		bool RequestIntradayBarElementString::isArray() const
		{
			return false;
		}

		bool RequestIntradayBarElementString::isComplexType() const
		{
			return false;
		}

		const char * RequestIntradayBarElementString::getValueAsString(int index) const
		{
			if(index == 0)
				return this->_value.c_str();
			else
				throw elementPtrEx;
		}

		std::ostream& RequestIntradayBarElementString::print(std::ostream& stream, int level, int spacesPerLevel) const
		{
			this->prettyPrintHelper(stream, level, spacesPerLevel, this->_value);
			return stream;
		}
	}
}