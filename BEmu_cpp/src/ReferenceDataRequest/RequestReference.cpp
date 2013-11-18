//------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="src/ReferenceDataRequest/RequestReference.cpp" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

#include "ReferenceDataRequest/RequestReference.h"

#include "ReferenceDataRequest/RequestReferenceElementStringArray.h"
#include "ReferenceDataRequest/RequestReferenceElementOverrideArray.h"

namespace BEmu
{
	namespace ReferenceDataRequest
	{
		RequestReference::RequestReference()
		{
            this->_securities = new RequestReferenceElementStringArray("securities");
            this->_fields = new RequestReferenceElementStringArray("fields");
            this->_overrides = new RequestReferenceElementOverrideArray();
			
			this->_requestType = RequestPtr::reference;
		}

		RequestReference::~RequestReference()
		{
			delete this->_securities;
			this->_securities = 0;
			
			delete this->_fields;
			this->_fields = 0;
			
			delete this->_overrides;
			this->_overrides = 0;
		}

		std::vector<std::string> RequestReference::getSecurities() const
		{
			return this->_securities->getValues();
		}

		std::vector<std::string> RequestReference::getFields() const
		{
			return this->_fields->getValues();
		}

		bool RequestReference::hasElement(std::string arg) const
		{
			return 
				arg.compare("securities") == 0 ||
				arg.compare("fields") == 0 ||
				arg.compare("overrides") == 0;
		}

		Element RequestReference::getElement(const char* name)
		{
			if(strncmp(name, "securities", 11) == 0)
				return this->_securities;
			
			else if(strncmp(name, "fields", 7) == 0)
				return this->_fields;
			
			else if(strncmp(name, "overrides", 10) == 0)
				return this->_overrides;

			else
				throw requestEx;
		}

		void RequestReference::append(const char* name, const char* value)
		{
			if(strncmp(name, "securities", 11) == 0)
				this->_securities->addValue(value);

			else if(strncmp(name, "fields", 7) == 0)
				this->_fields->addValue(value);

			else
				throw requestEx;
		}

	}
}