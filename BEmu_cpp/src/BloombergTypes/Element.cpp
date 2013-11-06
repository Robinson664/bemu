//------------------------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="src/BloombergTypes/Element.cpp" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------------------------

#include "BloombergTypes/Name.h"
#include "BloombergTypes/Element.h"
#include "BloombergTypes/ElementPtr.h"
#include "BloombergTypes/Datetime.h"
#include "Types/IndentType.h"

namespace BEmu
{
	Element::Element()
	{
		this->_ptr = 0;
	}

	Element::Element(const Element& arg)
	{
		this->_ptr = arg._ptr;
	}

	Element::Element(const ElementPtr* arg)
	{
		this->_ptr = arg;
	}

	Element& Element::operator=(const Element &rhs)
	{
		if (this != &rhs)
		{
			this->_ptr = rhs._ptr;
		}
		return *this;
	}

	std::ostream& Element::print(std::ostream& stream, int level, int spacesPerLevel) const
	{
		this->_ptr->print(stream, level, spacesPerLevel);
		return stream;
	}

	bool Element::isNull() const { return this->_ptr->isNull(); }
	bool Element::isArray() const { return this->_ptr->isArray(); }
	bool Element::isComplexType() const { return this->_ptr->isComplexType(); }
	
	size_t Element::numValues() const { return this->_ptr->numValues(); }
	size_t Element::numElements() const { return this->_ptr->numElements(); }
	Name Element::name() const { return this->_ptr->name(); }

	bool Element::getValueAsBool(int index) const { return this->_ptr->getValueAsBool(index); }
	int Element::getValueAsInt32(int index) const { return this->_ptr->getValueAsInt32(index); }
	long Element::getValueAsInt64(int index) const { return this->_ptr->getValueAsInt64(index); }
	float Element::getValueAsFloat32(int index) const { return this->_ptr->getValueAsFloat32(index); }
	double Element::getValueAsFloat64(int index) const { return this->_ptr->getValueAsFloat64(index); }
	Datetime Element::getValueAsDatetime(int index) const { return this->_ptr->getValueAsDatetime(index); }
	const char * Element::getValueAsString(int index) const { return this->_ptr->getValueAsString(index); }
	Element Element::getValueAsElement(int index) const { return this->_ptr->getValueAsElement(index); }

	Element Element::getElement(int position) const
	{
		Element result(this->_ptr->getElement(position));
		return result;
	}
	Element Element::getElement(const char* name) const
	{
		ElementPtr * elementP = this->_ptr->getElement(name);
		Element result(elementP);
		return result;
	}	
	Element Element::getElement(const Name& name) const
	{
		return this->getElement(name.string());
	}

	bool Element::hasElement(const char* name, bool excludeNullElements) const
	{
		return this->_ptr->hasElement(name, excludeNullElements);
	}
	bool Element::hasElement(const Name& name, bool excludeNullElements) const
	{
		return this->hasElement(name.string(), excludeNullElements);
	}
	
	bool Element::getElementAsBool(const char* name) const
	{
		return this->getElement(name).getValueAsBool(0);
	}
	bool Element::getElementAsBool(const Name& name) const
	{
		return this->getElementAsBool(name.string());
	}
	
	int Element::getElementAsInt32(const char* name) const
	{
		return this->_ptr->getElementAsInt32(name);
		//return this->getElement(name).getElementAsInt32(0);
	}
	int Element::getElementAsInt32(const Name& name) const
	{
		return this->getElementAsInt32(name.string());
	}
	
	long Element::getElementAsInt64(const char* name) const
	{
		return this->getElement(name).getValueAsInt64(0);
	}
	long Element::getElementAsInt64(const Name& name) const
	{
		return this->getElementAsInt64(name.string());
	}

	float Element::getElementAsFloat32(const char* name) const
	{
		return this->getElement(name).getValueAsFloat32(0);
	}
	float Element::getElementAsFloat32(const Name& name) const
	{
		return this->getElementAsFloat32(name.string());
	}

	double Element::getElementAsFloat64(const char* name) const
	{
		return this->getElement(name).getValueAsFloat64(0);
	}
	double Element::getElementAsFloat64(const Name& name) const
	{
		return this->getElementAsFloat64(name.string());
	}

	Datetime Element::getElementAsDatetime(const char* name) const
	{
		return this->getElement(name).getValueAsDatetime(0);
	}
	Datetime Element::getElementAsDatetime(const Name& name) const
	{
		return this->getElementAsDatetime(name.string());
	}

	const char* Element::getElementAsString(const char* name) const
	{
		return this->getElement(name).getValueAsString(0);
	}
	const char* Element::getElementAsString(const Name& name) const
	{
		return this->getElementAsString(name.string());
	}
}