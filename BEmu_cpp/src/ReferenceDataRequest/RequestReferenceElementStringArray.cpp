//------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="src/ReferenceDataRequest/RequestReferenceElementStringArray.cpp" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

#include "ReferenceDataRequest/RequestReferenceElementStringArray.h"

#include "Types/IndentType.h"
#include "BloombergTypes/Name.h"

namespace BEmu
{
	namespace ReferenceDataRequest
	{
		RequestReferenceElementStringArray::RequestReferenceElementStringArray(const std::string& elementName)
		{
			this->_elementName = elementName;
		}

		RequestReferenceElementStringArray::~RequestReferenceElementStringArray()
		{
		}

		Name RequestReferenceElementStringArray::name() const { return Name(this->_elementName.c_str()); }
		size_t RequestReferenceElementStringArray::numValues() const { return this->_values.size(); }
		size_t RequestReferenceElementStringArray::numElements() const { return 0; }

		bool RequestReferenceElementStringArray::isNull() const { return false; }
		bool RequestReferenceElementStringArray::isArray() const { return true; }
		bool RequestReferenceElementStringArray::isComplexType() const { return false; }

		void RequestReferenceElementStringArray::addValue(const std::string& elementName)
		{
			this->_values.push_back(elementName);
		}

		std::vector<std::string> RequestReferenceElementStringArray::getValues() const
		{
			return this->_values;
		}

		std::ostream& RequestReferenceElementStringArray::print(std::ostream& stream, int level, int spacesPerLevel) const
		{
			std::string tabs(IndentType::Indent(level, spacesPerLevel));

			stream << tabs << this->_elementName << "[] = {" << std::endl;

			stream << tabs;
			for(size_t i = 0; i < this->_values.size(); i++)
			{
				stream << this->_values[i];

				if(i + 1 < this->_values.size())
					stream << ", ";
			}
			stream << std::endl;

			stream << tabs << '}' << std::endl;

			return stream;

		}

	}
}