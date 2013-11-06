//------------------------------------------------------------------------------
// <copyright project="BEmu" file="headers/HistoricalDataRequest/ElementHistoricFieldData.h" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

#pragma once

#include "BloombergTypes/ElementPtr.h"
#include <map>

namespace BEmu
{
	class ObjectType;

	namespace HistoricalDataRequest
	{
		class ElementHistoricFieldData : public ElementPtr
		{
			private:
				std::map<std::string, ElementPtr*> _fields;

			public:
				ElementHistoricFieldData(const Datetime& date, const std::map<std::string, ObjectType>& values);
				~ElementHistoricFieldData();

				virtual Name name() const;
				virtual size_t numValues() const;
				virtual size_t numElements() const;
		
				bool isNull() const;
				virtual bool isArray() const;
				virtual bool isComplexType() const;

				virtual bool hasElement(const char* name, bool excludeNullElements = false) const;
				virtual ElementPtr * getElement(const char* name) const;

				virtual int getElementAsInt32(const char* name) const;
				virtual Datetime getElementAsDatetime(const char* name) const;
				virtual const char* getElementAsString(const char* name) const;
				virtual float getElementAsFloat32(const char* name) const;
				virtual double getElementAsFloat64(const char* name) const;
				virtual long getElementAsInt64(const char* name) const;

				virtual std::ostream& print(std::ostream& stream, int level = 0, int spacesPerLevel = 4) const;
		};
	}
}