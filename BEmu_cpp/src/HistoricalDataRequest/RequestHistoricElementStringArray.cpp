//------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="src/HistoricalDataRequest/RequestHistoricElementStringArray.cpp" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

#include "HistoricalDataRequest/RequestHistoricElementStringArray.h"
#include "BloombergTypes/Name.h"
#include "Types/IndentType.h"

namespace BEmu
{
	namespace HistoricalDataRequest
	{
		RequestHistoricElementStringArray::RequestHistoricElementStringArray(const std::string& elementName)
		{
			this->_elementName = elementName;
		}

		RequestHistoricElementStringArray::~RequestHistoricElementStringArray()
		{
		}


		Name RequestHistoricElementStringArray::name() const
		{
			Name result(this->_elementName.c_str());
			return result;
		}

		size_t RequestHistoricElementStringArray::numValues() const
		{
			return this->_values.size();
		}

		size_t RequestHistoricElementStringArray::numElements() const
		{
			return 0;
		}

		
		bool RequestHistoricElementStringArray::isNull() const
		{
			return false;
		}

		bool RequestHistoricElementStringArray::isArray() const
		{
			return true;
		}

		bool RequestHistoricElementStringArray::isComplexType() const
		{
			return false;
		}


		void RequestHistoricElementStringArray::addValue(const std::string& value)
		{
			this->_values.push_back(value);
		}

		std::vector<std::string> RequestHistoricElementStringArray::values() const
		{
			return this->_values;
		}


		std::ostream& RequestHistoricElementStringArray::print(std::ostream& stream, int level, int spacesPerLevel) const
		{
			std::string tabs(IndentType::Indent(level, spacesPerLevel));

			stream << tabs << this->_elementName << "[] = {" << std::endl;
			stream << tabs << IndentType::Indent(1, spacesPerLevel);

			int size = this->_values.size();
			int count = 0;
			for(std::vector<std::string>::const_iterator iter = this->_values.begin(); iter != this->_values.end(); ++iter)
			{
				std::string str = *iter;

				stream << str;
				if(count < size - 1)
					stream << ", ";

				count++;
			}

			stream << std::endl;			
			stream << tabs << '}' << std::endl;

			return stream;
		}

	}
}