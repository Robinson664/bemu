//------------------------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="src/IntradayBarRequest/IntradayBarElementData.cpp" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------------------------

#include "BloombergTypes/Name.h"
#include "BloombergTypes/ElementPtr.h"
#include <vector>
#include "IntradayBarRequest/IntradayBarElementData.h"
#include "IntradayBarRequest/IntradayBarElementTickDataArray.h"
#include "Types/IndentType.h"

namespace BEmu
{
	namespace IntradayBarRequest
	{
		IntradayBarElementData::IntradayBarElementData(std::vector< boost::shared_ptr<IntradayBarTickDataType> > bars) :
			_array(new IntradayBarElementTickDataArray(bars))
		{
			////std::vector< boost::shared_ptr<IntradayBarElementTickData> > bars2 = bars;

			//this->_array = boost::shared_ptr<IntradayBarElementTickDataArray>( new IntradayBarElementTickDataArray(bars) );

			////this->_array = new IntradayBarElementTickDataArray(bars); //deleted in destructor
		}

		IntradayBarElementData::~IntradayBarElementData()
		{
			//delete this->_array;
			//this->_array = 0;
		}

		Name IntradayBarElementData::name() const
		{
			Name result("barData");
			return result;
		}

		size_t IntradayBarElementData::numValues() const
		{
			return 1;
		}

		size_t IntradayBarElementData::numElements() const
		{
			return 1;
		}

		SchemaElementDefinition IntradayBarElementData::elementDefinition() const
		{
			::blpapi_DataType_t dtype = (::blpapi_DataType_t)this->datatype();
			SchemaElementDefinition result(dtype, Name("BarData"));
			return result;
		}

		bool IntradayBarElementData::isArray() const
		{
			return false;
		}

		bool IntradayBarElementData::isComplexType() const
		{
			return true;
		}

		//ElementPtr * IntradayBarElementData::getElement(const char* name) const
		boost::shared_ptr<ElementPtr> IntradayBarElementData::getElement(const char* name) const
		{
			int length = strlen(name);
			
			if(strncmp(this->_array->name().string(), name, length + 1) == 0)
				return boost::dynamic_pointer_cast<ElementPtr>(this->_array);
			else
				throw elementPtrEx;
		}

		std::ostream& IntradayBarElementData::print(std::ostream& stream, int level, int spacesPerLevel) const
		{
			std::string tabs(IndentType::Indent(level, spacesPerLevel));

			stream << tabs << "barData = {" << std::endl;
			this->_array->print(stream, level + 1, spacesPerLevel);
			stream << tabs << '}' << std::endl;

			return stream;
		}

	}
}