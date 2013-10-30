//------------------------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="src/IntradayTickRequest/ElementReference.cpp" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------------------------

#include "IntradayTickRequest/ElementReference.h"
#include "BloombergTypes/Name.h"
#include "BloombergTypes/ElementPtr.h"

#include "IntradayTickRequest/MessageIntradayTick.h"

namespace BEmu
{
	namespace IntradayTickRequest
	{
		ElementReference::ElementReference(const MessageIntradayTick& msg)
		{
			this->_parent = msg.firstElement();
		}

		Name ElementReference::name() const
		{
			Name result("IntradayTickRequest");
			return result;
		}

		ElementPtr * ElementReference::getElement(const char* name) const
		{
			if(this->_parent->name() == name)
				return this->_parent;
			else
				throw elementPtrEx;
		}

		std::ostream& ElementReference::print(std::ostream& stream, int level, int spacesPerLevel) const
		{
			stream << "IntradayTickRequest (choice) = {" << std::endl;
			this->_parent->print(stream, level + 1, spacesPerLevel);
			stream << '}' << std::endl;

			return stream;
		}

	}
}