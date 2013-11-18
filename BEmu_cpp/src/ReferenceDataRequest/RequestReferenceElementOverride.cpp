//------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="src/ReferenceDataRequest/RequestReferenceElementOverride.cpp" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

#include "ReferenceDataRequest/RequestReferenceElementOverride.h"
#include "ReferenceDataRequest/ElementReferenceString.h"
#include "ReferenceDataRequest/ElementReferenceObject.h"

#include "Types/IndentType.h"
#include "BloombergTypes/Name.h"

namespace BEmu
{
	namespace ReferenceDataRequest
	{
		RequestReferenceElementOverride::RequestReferenceElementOverride()
		{
            this->_fieldId = new ElementReferenceString("fieldId", "");
            this->_value = new ElementReferenceObject("value", "");
		}

		RequestReferenceElementOverride::~RequestReferenceElementOverride()
		{
			delete this->_fieldId;
			this->_fieldId = 0;

			delete this->_value;
			this->_value = 0;
		}

		Name RequestReferenceElementOverride::name() const { return Name("overrides"); }
		size_t RequestReferenceElementOverride::numValues() const { return 1; }
		size_t RequestReferenceElementOverride::numElements() const { return 2; }

		//bool RequestReferenceElementOverride::isNull() const { return false; }
		//bool RequestReferenceElementOverride::isArray() const { return false; }
		//bool RequestReferenceElementOverride::isComplexType() const { return false; }

		void RequestReferenceElementOverride::setElement(const char* name, const char* value)
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

		void RequestReferenceElementOverride::setElement(const char* name, int value)
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

		ElementPtr * RequestReferenceElementOverride::getElement(const char* name) const
		{
			if(strncmp(name, "fieldId", 8) == 0)
				return this->_fieldId;

			else if(strncmp(name, "value", 6) == 0)
				return this->_value;
			
			else
				throw elementPtrEx;
		}

		std::ostream& RequestReferenceElementOverride::print(std::ostream& stream, int level, int spacesPerLevel) const
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