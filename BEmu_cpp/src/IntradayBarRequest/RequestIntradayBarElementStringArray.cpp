//------------------------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="src/IntradayBarRequest/RequestIntradayBarElementStringArray.cpp" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------------------------

#include "BloombergTypes/Name.h"
#include "BloombergTypes/ElementPtr.h"
#include "Types/IndentType.h"
#include "IntradayBarRequest/RequestIntradayBarElementStringArray.h"

namespace BEmu
{
	namespace IntradayBarRequest
	{
		RequestIntradayBarElementStringArray::RequestIntradayBarElementStringArray(const std::string& elementName)
		{
			this->_name = elementName;
		}

		RequestIntradayBarElementStringArray::~RequestIntradayBarElementStringArray()
		{
			for(std::vector<std::string*>::const_iterator iter = this->_values.begin(); iter != this->_values.end(); ++iter)
			{
				std::string* value = *iter;
				delete value;
			}
		}

		Name RequestIntradayBarElementStringArray::name() const
		{
			Name result(this->_name.c_str());
			return result;
		}

		size_t RequestIntradayBarElementStringArray::numValues() const
		{
			return this->_values.size();
		}

		size_t RequestIntradayBarElementStringArray::numElements() const
		{
			return 0;
		}

		bool RequestIntradayBarElementStringArray::isArray() const
		{
			return true;
		}

		bool RequestIntradayBarElementStringArray::isComplexType() const
		{
			return false;
		}

		std::vector<std::string*> RequestIntradayBarElementStringArray::values()
		{
			return this->_values;
		}

		void RequestIntradayBarElementStringArray::addValue(const std::string& value)
		{
			if(this->isEventTypeAllowed(value))
			{
				std::string* str = new std::string(value);
				this->_values.push_back(str);
			}
			else
				throw elementPtrEx;
		}

		bool RequestIntradayBarElementStringArray::isEventTypeAllowed(const std::string& value)
		{
			return 
				(value.compare("TRADE") == 0) ||
				(value.compare("BID") == 0) ||
				(value.compare("ASK") == 0) ||
				(value.compare("BID_BEST") == 0) ||
				(value.compare("ASK_BEST") == 0) ||
				(value.compare("BEST_BID") == 0) ||
				(value.compare("BEST_ASK") == 0) ||
				(value.compare("BID_YIELD") == 0) ||
				(value.compare("ASK_YIELD") == 0) ||
				(value.compare("MID_PRICE") == 0) ||
				(value.compare("AT_TRADE") == 0) ||
				(value.compare("SETTLE") == 0);
		}

		std::ostream& RequestIntradayBarElementStringArray::print(std::ostream& stream, int level, int spacesPerLevel) const
		{
			std::string tabs(IndentType::Indent(level, spacesPerLevel));

			stream << tabs << this->_name << "[] = {" << std::endl;

			int index = 0, lastIndex = this->_values.size() - 1;
			for(std::vector<std::string*>::const_iterator iter = this->_values.begin(); iter != this->_values.end(); ++iter)
			{
				std::string* value = *iter;

				stream << value;

				if(index < lastIndex)
					stream << ", ";
			}

			stream << tabs << '}' << std::endl;

			return stream;
		}



	}
}