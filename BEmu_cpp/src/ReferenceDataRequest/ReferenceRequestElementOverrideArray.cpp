//------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="src/ReferenceDataRequest/ReferenceRequestElementOverrideArray.cpp" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

#include "ReferenceDataRequest/ReferenceRequestElementOverrideArray.h"
#include "ReferenceDataRequest/ReferenceRequestElementOverride.h"
#include "Types/IndentType.h"
#include "BloombergTypes/Name.h"

namespace BEmu
{
	namespace ReferenceDataRequest
	{
		ReferenceRequestElementOverrideArray::ReferenceRequestElementOverrideArray()
		{
		}

		ReferenceRequestElementOverrideArray::~ReferenceRequestElementOverrideArray()
		{
		}

		Name ReferenceRequestElementOverrideArray::name() const { return Name("overrides"); }
		size_t ReferenceRequestElementOverrideArray::numValues() const { return this->_overrides.size(); }
		size_t ReferenceRequestElementOverrideArray::numElements() const { return 0; }

		bool ReferenceRequestElementOverrideArray::isNull() const { return false; }
		bool ReferenceRequestElementOverrideArray::isArray() const { return true; }
		bool ReferenceRequestElementOverrideArray::isComplexType() const { return false; }

		ElementPtr * ReferenceRequestElementOverrideArray::getValueAsElement(int index) const
		{
			return this->_overrides[index];
		}

		ElementPtr * ReferenceRequestElementOverrideArray::appendElement()
		{
            ReferenceRequestElementOverride * result = new ReferenceRequestElementOverride();
			this->_overrides.push_back(result);
            return result;
		}

		std::ostream& ReferenceRequestElementOverrideArray::print(std::ostream& stream, int level, int spacesPerLevel) const
		{
			std::string tabs(IndentType::Indent(level, spacesPerLevel));

			stream << tabs << "overrides[] = {" << std::endl;

			for(std::vector<ReferenceRequestElementOverride*>::const_iterator iter = this->_overrides.begin(); iter != this->_overrides.end(); iter++)
			{
				ReferenceRequestElementOverride * req = *iter;
				req->print(stream, level + 1, spacesPerLevel);
			}

			stream << tabs << '}' << std::endl;

			return stream;
		}
		
			


	}
}