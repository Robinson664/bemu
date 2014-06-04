//------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="headers/ReferenceDataRequest/ReferenceElementFieldData.h" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

#pragma once

#include "BloombergTypes/ElementPtr.h"
#include "Types/ObjectType.h"
#include <vector>
#include <map>
#include <boost/shared_ptr.hpp>

namespace BEmu
{
	class Name;

	namespace ReferenceDataRequest
	{
		class ReferenceElementFieldData : public ElementPtr
		{
			private:
				//std::vector<ElementPtr*> _fields;
				std::vector< boost::shared_ptr<ElementPtr> > _fields;

			public:
				ReferenceElementFieldData(const std::map<std::string, ObjectType>& values);
				~ReferenceElementFieldData();

				virtual Name name() const;
				virtual size_t numValues() const;
				virtual size_t numElements() const;
				virtual SchemaElementDefinition elementDefinition() const;

				//virtual ElementPtr * getElement(int position) const;
				virtual boost::shared_ptr<ElementPtr> getElement(int position) const;
				
				//virtual ElementPtr * getElement(const char* name) const;
				virtual boost::shared_ptr<ElementPtr> getElement(const char* name) const;

				virtual bool hasElement(const char* name, bool excludeNullElements = false) const;

				virtual double getElementAsFloat64(const char* name) const;
				virtual int getElementAsInt32(const char* name) const;
				virtual long getElementAsInt64(const char* name) const;
				virtual const char* getElementAsString(const char* name) const;

				virtual std::ostream& print(std::ostream& stream, int level = 0, int spacesPerLevel = 4) const;
		};
	}
}