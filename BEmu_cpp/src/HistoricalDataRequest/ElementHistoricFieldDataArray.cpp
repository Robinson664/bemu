//------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="src/HistoricalDataRequest/ElementHistoricFieldDataArray.cpp" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

#include "HistoricalDataRequest/ElementHistoricFieldDataArray.h"
#include "HistoricalDataRequest/ElementHistoricFieldData.h"
#include "Types/ObjectType.h"
#include "Types/IndentType.h"
#include "BloombergTypes/Name.h"
#include "BloombergTypes/Datetime.h"


namespace BEmu
{
	namespace HistoricalDataRequest
	{
		ElementHistoricFieldDataArray::ElementHistoricFieldDataArray(const std::map<Datetime, std::map<std::string, ObjectType>*> * fieldData)
		{
			for(std::map<Datetime, std::map<std::string, ObjectType>*>::const_iterator iter = fieldData->begin(); iter != fieldData->end(); ++iter)
			{
				const std::map<std::string, ObjectType> * mm = iter->second;

				ElementHistoricFieldData * elmFieldData = new ElementHistoricFieldData(iter->first, *mm);
				this->_fieldData.push_back(elmFieldData);
			}
		}

		ElementHistoricFieldDataArray::~ElementHistoricFieldDataArray()
		{
			for(std::vector<ElementHistoricFieldData*>::const_iterator iter = this->_fieldData.begin(); iter != this->_fieldData.end(); ++iter)
			{
				ElementHistoricFieldData * elm = *iter;
				delete elm;
			}
		}


		ElementPtr * ElementHistoricFieldDataArray::getValueAsElement(int index) const
		{
			return this->_fieldData.at(index);
		}


		Name ElementHistoricFieldDataArray::name() const
		{
			Name result("fieldData");
			return result;
		}

		size_t ElementHistoricFieldDataArray::numValues() const
		{
			return this->_fieldData.size();
		}

		size_t ElementHistoricFieldDataArray::numElements() const
		{
			return 0;
		}

		SchemaElementDefinition ElementHistoricFieldDataArray::elementDefinition() const
		{
			::blpapi_DataType_t dtype = (::blpapi_DataType_t)this->datatype();
			SchemaElementDefinition result(dtype, Name("HistoricalDataRow"));
			return result;
		}

		
		bool ElementHistoricFieldDataArray::isNull() const
		{
			return false;
		}

		bool ElementHistoricFieldDataArray::isArray() const
		{
			return true;
		}

		bool ElementHistoricFieldDataArray::isComplexType() const
		{
			return false;
		}


		std::ostream& ElementHistoricFieldDataArray::print(std::ostream& stream, int level, int spacesPerLevel) const
		{
			std::string tabs(IndentType::Indent(level, spacesPerLevel));

			stream << tabs << "fieldData[] = {" << std::endl;
			for(std::vector<ElementHistoricFieldData*>::const_iterator iter = this->_fieldData.begin(); iter != this->_fieldData.end(); ++iter)
			{
				ElementHistoricFieldData * elm = *iter;
				elm->print(stream, level + 1, spacesPerLevel);
			}
			stream << tabs << '}' << std::endl;

			return stream;
		}

	}
}