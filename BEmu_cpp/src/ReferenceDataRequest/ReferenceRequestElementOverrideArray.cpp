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
			this->_overrides.clear();
		}

		Name ReferenceRequestElementOverrideArray::name() const { return Name("overrides"); }
		size_t ReferenceRequestElementOverrideArray::numValues() const { return this->_overrides.size(); }
		size_t ReferenceRequestElementOverrideArray::numElements() const { return 0; }

		bool ReferenceRequestElementOverrideArray::isNull() const { return false; }
		bool ReferenceRequestElementOverrideArray::isArray() const { return true; }
		bool ReferenceRequestElementOverrideArray::isComplexType() const { return false; }

		boost::shared_ptr<ElementPtr> ReferenceRequestElementOverrideArray::getValueAsElement(int index) const
		{
			return boost::dynamic_pointer_cast<ElementPtr>(this->_overrides[index]);
		}

		boost::shared_ptr<ElementPtr> ReferenceRequestElementOverrideArray::appendElement()
		{
			boost::shared_ptr<ReferenceRequestElementOverride> elmP(new ReferenceRequestElementOverride());

			this->_overrides.push_back(elmP);
			return boost::dynamic_pointer_cast<ElementPtr>(elmP);
		}

		std::ostream& ReferenceRequestElementOverrideArray::print(std::ostream& stream, int level, int spacesPerLevel) const
		{
			std::string tabs(IndentType::Indent(level, spacesPerLevel));

			stream << tabs << "overrides[] = {" << std::endl;

			for(std::vector< boost::shared_ptr<ReferenceRequestElementOverride> >::const_iterator iter = this->_overrides.begin(); iter != this->_overrides.end(); iter++)
			{
				boost::shared_ptr<ReferenceRequestElementOverride> req = *iter;
				req->print(stream, level + 1, spacesPerLevel);
			}

			stream << tabs << '}' << std::endl;

			return stream;
		}

	}
}