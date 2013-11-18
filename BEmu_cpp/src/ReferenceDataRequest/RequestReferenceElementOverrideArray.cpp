//------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="src/ReferenceDataRequest/RequestReferenceElementOverrideArray.cpp" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

#include "ReferenceDataRequest/RequestReferenceElementOverrideArray.h"
#include "ReferenceDataRequest/RequestReferenceElementOverride.h"
#include "Types/IndentType.h"
#include "BloombergTypes/Name.h"

namespace BEmu
{
	namespace ReferenceDataRequest
	{
		RequestReferenceElementOverrideArray::RequestReferenceElementOverrideArray()
		{
		}

		RequestReferenceElementOverrideArray::~RequestReferenceElementOverrideArray()
		{
		}

		Name RequestReferenceElementOverrideArray::name() const { return Name("overrides"); }
		size_t RequestReferenceElementOverrideArray::numValues() const { return this->_overrides.size(); }
		size_t RequestReferenceElementOverrideArray::numElements() const { return 0; }

		bool RequestReferenceElementOverrideArray::isNull() const { return false; }
		bool RequestReferenceElementOverrideArray::isArray() const { return true; }
		bool RequestReferenceElementOverrideArray::isComplexType() const { return false; }

		ElementPtr * RequestReferenceElementOverrideArray::getValueAsElement(int index) const
		{
			return this->_overrides[index];
		}

		ElementPtr * RequestReferenceElementOverrideArray::appendElement()
		{
            RequestReferenceElementOverride * result = new RequestReferenceElementOverride();
			this->_overrides.push_back(result);
            return result;
		}

		std::ostream& RequestReferenceElementOverrideArray::print(std::ostream& stream, int level, int spacesPerLevel) const
		{
			std::string tabs(IndentType::Indent(level, spacesPerLevel));

			stream << tabs << "overrides[] = {" << std::endl;

			for(std::vector<RequestReferenceElementOverride*>::const_iterator iter = this->_overrides.begin(); iter != this->_overrides.end(); iter++)
			{
				RequestReferenceElementOverride * req = *iter;
				req->print(stream, level + 1, spacesPerLevel);
			}

			stream << tabs << '}' << std::endl;

			return stream;
		}
		
			


	}
}