//------------------------------------------------------------------------------
// <copyright project="BEmu" file="src/HistoricalDataRequest/ElementHistoricFieldData.cpp" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

#include "HistoricalDataRequest/ElementHistoricFieldData.h"
#include "HistoricalDataRequest/ElementHistoricDateTime.h"
#include "HistoricalDataRequest/ElementHistoricDouble.h"

#include "BloombergTypes/Name.h"

#include "Types/ObjectType.h"
#include "Types/IndentType.h"

namespace BEmu
{
	namespace HistoricalDataRequest
	{
		ElementHistoricFieldData::ElementHistoricFieldData(const Datetime& date, const std::map<std::string, ObjectType>& values)
		{
			ElementPtr * elmDate = new ElementHistoricDateTime(date);
			this->_fields[elmDate->name().string()] = elmDate;

			for(std::map<std::string, ObjectType>::const_iterator iter = values.begin(); iter != values.end(); ++iter)
			{
				const std::string str = iter->first;
				const ObjectType obj = iter->second;
				double dvalue;

				if(obj.TryGetDouble(dvalue))
				{
					ElementPtr * elmDouble = new ElementHistoricDouble(str, dvalue);
					this->_fields[elmDouble->name().string()] = elmDouble;
				}
			}
		}

		ElementHistoricFieldData::~ElementHistoricFieldData()
		{
			for(std::map<std::string, ElementPtr*>::const_iterator iter = this->_fields.begin(); iter != this->_fields.end(); ++iter)
			{
				ElementPtr * elm = iter->second;
				delete elm;
			}
		}


		Name ElementHistoricFieldData::name() const
		{
			Name result("fieldData");
			return result;
		}

		size_t ElementHistoricFieldData::numValues() const
		{
			return 1;
		}

		size_t ElementHistoricFieldData::numElements() const
		{
			return this->_fields.size();
		}

		
		bool ElementHistoricFieldData::isNull() const
		{
			return false;
		}

		bool ElementHistoricFieldData::isArray() const
		{
			return false;
		}

		bool ElementHistoricFieldData::isComplexType() const
		{
			return true;
		}


		bool ElementHistoricFieldData::hasElement(const char* name, bool excludeNullElements) const
		{
			return this->_fields.find(name) != this->_fields.end();
		}

		ElementPtr * ElementHistoricFieldData::getElement(const char* name) const
		{
			std::string key(name);

			std::map<std::string, ElementPtr*>::const_iterator it = this->_fields.find(key);
			if(it == this->_fields.end())
				throw elementPtrEx;
			else
				return it->second;
		}

		int ElementHistoricFieldData::getElementAsInt32(const char* name) const
		{
			return this->getElement(name)->getValueAsInt32(0);
		}

		Datetime ElementHistoricFieldData::getElementAsDatetime(const char* name) const
		{
			return this->getElement(name)->getValueAsDatetime(0);
		}

		const char* ElementHistoricFieldData::getElementAsString(const char* name) const
		{
			return this->getElement(name)->getValueAsString(0);
		}

		float ElementHistoricFieldData::getElementAsFloat32(const char* name) const
		{
			return this->getElement(name)->getValueAsFloat32(0);
		}

		double ElementHistoricFieldData::getElementAsFloat64(const char* name) const
		{
			return this->getElement(name)->getValueAsFloat64(0);
		}

		long ElementHistoricFieldData::getElementAsInt64(const char* name) const
		{
			return this->getElement(name)->getValueAsInt64(0);
		}


		std::ostream& ElementHistoricFieldData::print(std::ostream& stream, int level, int spacesPerLevel) const
		{
			std::string tabs(IndentType::Indent(level, spacesPerLevel));

			stream << tabs << "fieldData = {" << std::endl;

			for(std::map<std::string, ElementPtr*>::const_iterator iter = this->_fields.begin(); iter != this->_fields.end(); ++iter)
			{
				const ElementPtr * elm = iter->second;
				elm->print(stream, level + 1, spacesPerLevel);
			}

			stream << tabs << std::endl;

			return stream;
		}

	}
}