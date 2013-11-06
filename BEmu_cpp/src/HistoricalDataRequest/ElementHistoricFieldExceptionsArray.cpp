//------------------------------------------------------------------------------
// <copyright project="BEmu" file="src/HistoricalDataRequest/ElementHistoricFieldExceptionsArray.cpp" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

#include "HistoricalDataRequest/ElementHistoricFieldExceptionsArray.h"
#include "HistoricalDataRequest/ElementHistoricFieldExceptions.h"

#include "BloombergTypes/Name.h"
#include "Types/IndentType.h"

namespace BEmu
{
	namespace HistoricalDataRequest
	{
		ElementHistoricFieldExceptionsArray::ElementHistoricFieldExceptionsArray(const std::vector<std::string>& badFields)
		{
			for(std::vector<std::string>::const_iterator iter = badFields.begin(); iter != badFields.end(); ++iter)
			{
				std::string str = *iter;
				ElementHistoricFieldExceptions * elm = new ElementHistoricFieldExceptions(str);
				this->_exceptions.push_back(elm);
			}
		}

		ElementHistoricFieldExceptionsArray::~ElementHistoricFieldExceptionsArray()
		{
			for(std::vector<ElementHistoricFieldExceptions*>::const_iterator iter = this->_exceptions.begin(); iter != this->_exceptions.end(); ++iter)
			{
				ElementHistoricFieldExceptions * elm = *iter;
				delete elm;
			}
		}


		Name ElementHistoricFieldExceptionsArray::name() const
		{
			Name result("fieldExceptions");
			return result;
		}

		size_t ElementHistoricFieldExceptionsArray::numValues() const
		{
			return this->_exceptions.size();
		}

		size_t ElementHistoricFieldExceptionsArray::numElements() const
		{
			return 0;
		}

		
		bool ElementHistoricFieldExceptionsArray::isNull() const
		{
			return false;
		}

		bool ElementHistoricFieldExceptionsArray::isArray() const
		{
			return true;
		}

		bool ElementHistoricFieldExceptionsArray::isComplexType() const
		{
			return false;
		}


		ElementPtr * ElementHistoricFieldExceptionsArray::getValueAsElement(int index) const
		{
			return this->_exceptions.at(index);
		}


		std::ostream& ElementHistoricFieldExceptionsArray::print(std::ostream& stream, int level, int spacesPerLevel) const
		{
			std::string tabs(IndentType::Indent(level, spacesPerLevel));

			stream << tabs << "fieldExceptions = {" << std::endl;

			for(std::vector<ElementHistoricFieldExceptions*>::const_iterator iter = this->_exceptions.begin(); iter != this->_exceptions.end(); ++iter)
			{
				ElementHistoricFieldExceptions * elm = *iter;
				elm->print(stream, level + 1, spacesPerLevel);
			}

			stream << tabs << '}' << std::endl;

			return stream;
		}

	}
}