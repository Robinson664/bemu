//------------------------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="headers/IntradayTickRequest/ElementIntradayTickInt.h" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------------------------

#include "bemu_headers.h"
#include "BloombergTypes\Name.h"
#include "BloombergTypes\ElementPtr.h"

#pragma once

namespace BEmu
{
	namespace IntradayTickRequest
	{
		class ElementIntradayTickData;
		class ElementIntradayTickResponseError;

		class ElementIntradayTickInt : private ElementPtr
		{
			private:
				int _value;
				std::string _name;

				ElementIntradayTickInt(const std::string& name, int value);
				~ElementIntradayTickInt();

			public:
				virtual Name name() const;
				virtual int numValues() const;
				virtual int numElements() const;
		
				virtual bool isArray() const;
				virtual bool isComplexType() const;

				virtual bool hasElement(const char* name, bool excludeNullElements = false) const;

				virtual int getValueAsInt32(int index) const;
				virtual long getValueAsInt64(int index) const;
				virtual float getValueAsFloat32(int index) const;
				virtual double getValueAsFloat64(int index) const;
				virtual char* getValueAsString(int index) const;

				virtual std::ostream& print(std::ostream& stream, int level, int spacesPerLevel) const;

				friend class ElementIntradayTickData; //ElementIntradayTickData constructor needs access to the ElementIntradayTickInt constructor
				friend class ElementIntradayTickResponseError; //ElementIntradayTickResponseError constructor needs access to the ElementIntradayTickInt constructor
		};
	}
}