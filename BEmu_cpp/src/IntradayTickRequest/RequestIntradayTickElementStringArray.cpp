//------------------------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="src/IntradayTickRequest/RequestIntradayTickElementStringArray.cpp" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------------------------

#include "bemu_headers.h"
#include "IntradayTickRequest/RequestIntradayTickElementStringArray.h"
#include "BloombergTypes/Name.h"
#include "BloombergTypes/Element.h"
#include "Types/IndentType.h"

#include <vector>


namespace BEmu
{
	namespace IntradayTickRequest
	{
		RequestIntradayTickElementStringArray::RequestIntradayTickElementStringArray(const std::string& elementName)
		{
			this->_elementName = elementName;
		}

		RequestIntradayTickElementStringArray::~RequestIntradayTickElementStringArray()
		{
			for(std::vector<std::string*>::iterator iter = this->_values.begin(); iter != this->_values.end(); ++iter)
			{
				std::string* value = *iter;
				delete value;
				value = 0;
			}
		}

		void RequestIntradayTickElementStringArray::addValue(const std::string& value)
		{
			if(value.compare("TRADE") == 0 ||
				value.compare("BID") == 0 ||
				value.compare("ASK") == 0 ||
				value.compare("BID_BEST") == 0 ||
				value.compare("ASK_BEST") == 0 ||
				value.compare("MID_PRICE") == 0 ||
				value.compare("AT_TRADE") == 0 ||
				value.compare("BEST_BID") == 0 ||
				value.compare("BEST_ASK") == 0)
			{
				std::string* str = new std::string(value);
				this->_values.push_back(str);
			}
			else
			{
				//yes, the BloombergAPI actually throws an exception if the user requests a field that isn't supported.
				throw elementPtrEx;
			}
		}

		const std::vector<std::string*>& RequestIntradayTickElementStringArray::getValues()
		{
			return this->_values;
		}

		Name RequestIntradayTickElementStringArray::name() const
		{
			Name result(this->_elementName.c_str());
			return result;
		}

		int RequestIntradayTickElementStringArray::numElements() const
		{
			return this->_values.size();
		}

		std::ostream& RequestIntradayTickElementStringArray::print(std::ostream& stream, int level, int spacesPerLevel) const
		{
			std::string tabs = IndentType::Indent(level, spacesPerLevel);
			std::string tab = IndentType::Indent(level, 1);
			stream << tabs << this->_elementName << "[] = {" << std::endl;
			stream << tabs << tab;

			unsigned count = 1;
			for(std::vector<std::string*>::const_iterator iter = this->_values.begin(); iter != this->_values.end(); ++iter, ++count)
			{
				std::string* str = *iter;

				stream << str;
				if(count < this->_values.size())
					stream << ", ";
			}

			stream << tabs << '}' << std::endl;
			return stream;
		}

	}
}