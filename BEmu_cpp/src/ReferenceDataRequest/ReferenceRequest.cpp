//------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="src/ReferenceDataRequest/ReferenceRequest.cpp" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

#include "ReferenceDataRequest/ReferenceRequest.h"

#include "ReferenceDataRequest/ReferenceRequestElementStringArray.h"
#include "ReferenceDataRequest/ReferenceRequestElementOverrideArray.h"

namespace BEmu
{
	namespace ReferenceDataRequest
	{
		ReferenceRequest::ReferenceRequest()
		{
            this->_securities = new ReferenceRequestElementStringArray("securities");
            this->_fields = new ReferenceRequestElementStringArray("fields");
            this->_overrides = new ReferenceRequestElementOverrideArray();
			
			this->_requestType = RequestPtr::reference;
		}

		ReferenceRequest::~ReferenceRequest()
		{
			delete this->_securities;
			this->_securities = 0;
			
			delete this->_fields;
			this->_fields = 0;
			
			delete this->_overrides;
			this->_overrides = 0;
		}

		std::vector<std::string> ReferenceRequest::getSecurities() const
		{
			return this->_securities->getValues();
		}

		std::vector<std::string> ReferenceRequest::getFields() const
		{
			return this->_fields->getValues();
		}

		bool ReferenceRequest::hasElement(std::string arg) const
		{
			return 
				arg.compare("securities") == 0 ||
				arg.compare("fields") == 0 ||
				arg.compare("overrides") == 0;
		}

		Element ReferenceRequest::getElement(const char* name)
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

		void ReferenceRequest::append(const char* name, const char* value)
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