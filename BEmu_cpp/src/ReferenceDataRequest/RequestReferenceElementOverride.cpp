//------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="src/ReferenceDataRequest/ReferenceRequestElementOverride.cpp" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

#include "ReferenceDataRequest/ReferenceRequestElementOverride.h"
#include "ReferenceDataRequest/ReferenceElementString.h"
#include "ReferenceDataRequest/ReferenceElementObject.h"

#include "Types/IndentType.h"
#include "BloombergTypes/Name.h"

namespace BEmu
{
	namespace ReferenceDataRequest
	{
		ReferenceRequestElementOverride::ReferenceRequestElementOverride()
		{
            this->_fieldId = new ReferenceElementString("fieldId", "");
            this->_value = new ReferenceElementObject("value", "");
		}

		ReferenceRequestElementOverride::~ReferenceRequestElementOverride()
		{
			delete this->_fieldId;
			this->_fieldId = 0;

			delete this->_value;
			this->_value = 0;
		}

		Name ReferenceRequestElementOverride::name() const { return Name("overrides"); }
		size_t ReferenceRequestElementOverride::numValues() const { return 1; }
		size_t ReferenceRequestElementOverride::numElements() const { return 2; }

		void ReferenceRequestElementOverride::setElement(const char* name, const char* value)
		{
			if(strncmp(name, "fieldId", 8) == 0)
			{
				this->_fieldId->setName(name);
				this->_fieldId->setValue(value);
			}
			else if(strncmp(name, "value", 6) == 0)
			{
				this->_value->setName(name);
				
				ObjectType obj(value);
				this->_value->setValue(obj);
			}
			else
				throw elementPtrEx;
		}

		void ReferenceRequestElementOverride::setElement(const char* name, int value)
		{
			if(strncmp(name, "value", 6) == 0)
			{
				this->_value->setName(name);
				
				ObjectType obj(value);
				this->_value->setValue(obj);
			}
			else
				throw elementPtrEx;
		}

		ElementPtr * ReferenceRequestElementOverride::getElement(const char* name) const
		{
			if(strncmp(name, "fieldId", 8) == 0)
				return this->_fieldId;

			else if(strncmp(name, "value", 6) == 0)
				return this->_value;
			
			else
				throw elementPtrEx;
		}

		std::ostream& ReferenceRequestElementOverride::print(std::ostream& stream, int level, int spacesPerLevel) const
		{
			std::string tabs(IndentType::Indent(level, spacesPerLevel));

			stream << tabs << "overrides = {" << std::endl;
			
			this->_fieldId->print(stream, level + 1, spacesPerLevel);
			this->_value->print(stream, level + 1, spacesPerLevel);

			stream << tabs << '}' << std::endl;

			return stream;
		}
	}
}