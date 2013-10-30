//------------------------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="src/BloombergTypes/ElementPtr.cpp" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------------------------

#include "BloombergTypes/ElementPtr.h"
#include "BloombergTypes/Datetime.h"
#include "Types/IndentType.h"
#include "BloombergTypes/Name.h"

namespace BEmu
{
	void ElementPtr::prettyPrintHelper(std::ostream& stream, int tabIndent, int spacesPerTab, const std::string value) const
	{
		std::string tabs = IndentType::Indent(tabIndent, spacesPerTab);
		stream << tabs << this->name().string() << " = " << value << std::endl;
	}
	
	void ElementPtr::prettyPrintHelper(std::ostream& stream, int tabIndent, int spacesPerTab, const int value) const
	{
		std::string tabs = IndentType::Indent(tabIndent, spacesPerTab);
		stream << tabs << this->name().string() << " = " << value << std::endl;
	}
	
	void ElementPtr::prettyPrintHelper(std::ostream& stream, int tabIndent, int spacesPerTab, const double value) const
	{
		std::string tabs = IndentType::Indent(tabIndent, spacesPerTab);
		stream << tabs << this->name().string() << " = " << value << std::endl;
	}

	void ElementPtr::prettyPrintHelper(std::ostream& stream, int tabIndent, int spacesPerTab, const Datetime* value) const
	{
		std::string tabs = IndentType::Indent(tabIndent, spacesPerTab);
		stream << tabs << this->name().string() << " = " << *value << std::endl;
	}

	char* ElementPtr::toCharPointer(const char* arg, int length)
	{
		if(length < 0)
			length = strlen(arg) + 1;

		char* result = new char[length];
		strncpy(result, arg, length); //Visual Studio complains about this call, but the strncpy_s replacement is not portable.

		return result;
	}

	char* ElementPtr::toCharPointer(std::string& arg)
	{
		const char* ch = arg.c_str();
		int length = arg.length() + 1;
		char* result = ElementPtr::toCharPointer(ch, length);
		return result;
	}

	char* ElementPtr::toCharPointer(const std::string& arg)
	{
		const char* ch = arg.c_str();
		int length = arg.length() + 1;
		char* result = ElementPtr::toCharPointer(ch, length);
		return result;
	}

	char* ElementPtr::toCharPointer(std::stringstream& arg)
	{
		std::string str = arg.str();
		char* result = ElementPtr::toCharPointer(str);
		return result;
	}

	char* ElementPtr::toCharPointer(int arg)
	{
		std::stringstream ss;
		ss << arg;
		char* result = ElementPtr::toCharPointer(ss);
		return result;
	}

	char* ElementPtr::toCharPointer(double arg)
	{
		std::stringstream ss;
		ss << arg;
		char* result = ElementPtr::toCharPointer(ss);
		return result;
	}

	char* ElementPtr::toCharPointer(Datetime *arg)
	{
		std::stringstream ss;
		ss << *arg;
		char* result = ElementPtr::toCharPointer(ss);
		return result;
	}

	char* ElementPtr::toCharPointer(const Datetime& arg)
	{
		std::stringstream ss;
		ss << arg;
		char* result = ElementPtr::toCharPointer(ss);
		return result;
	}

	std::ostream& ElementPtr::print(std::ostream& stream, int level, int spacesPerLevel) const
	{
		throw elementPtrEx;
	}

	bool ElementPtr::isNull() const { return false; }
	bool ElementPtr::isArray() const { throw elementPtrEx; }
	bool ElementPtr::isComplexType() const { throw elementPtrEx; }
	
	int ElementPtr::numValues() const { throw elementPtrEx; }
	int ElementPtr::numElements() const { throw elementPtrEx; }
	Name ElementPtr::name() const { throw elementPtrEx; }

	bool ElementPtr::getValueAsBool(int index = 0) const { throw elementPtrEx; }
	int ElementPtr::getValueAsInt32(int index = 0) const { throw elementPtrEx; }
	long ElementPtr::getValueAsInt64(int index = 0) const { throw elementPtrEx; }
	float ElementPtr::getValueAsFloat32(int index = 0) const { throw elementPtrEx; }
	double ElementPtr::getValueAsFloat64(int index = 0) const { throw elementPtrEx; }
	Datetime ElementPtr::getValueAsDatetime(int index = 0) const { throw elementPtrEx; }
	char* ElementPtr::getValueAsString(int index = 0) const { throw elementPtrEx; }
	ElementPtr * ElementPtr::getValueAsElement(int index = 0) const { throw elementPtrEx; }

	ElementPtr * ElementPtr::getElement(int position) const { throw elementPtrEx; }
	ElementPtr * ElementPtr::getElement(const char* name) const { throw elementPtrEx; }
	
	ElementPtr * ElementPtr::getElement(const Name& name) const
	{
		return this->getElement(name.string());
	}

	bool ElementPtr::hasElement(const Name& name, bool excludeNullElements) const
	{
		return this->hasElement(name.string(), excludeNullElements);
	}

	bool ElementPtr::hasElement(const char* name, bool excludeNullElements) const
	{
		throw elementPtrEx;
	}

	bool ElementPtr::getElementAsBool(const char* name) const
	{
		return this->getElement(name)->getValueAsBool(0);
	}

	int ElementPtr::getElementAsInt32(const char* name) const
	{
		return this->getElement(name)->getValueAsInt32(0);
	}

	long ElementPtr::getElementAsInt64(const char* name) const
	{
		return this->getElement(name)->getValueAsInt64(0);
	}

	float ElementPtr::getElementAsFloat32(const char* name) const
	{
		return this->getElement(name)->getValueAsFloat32(0);
	}

	double ElementPtr::getElementAsFloat64(const char* name) const
	{
		return this->getElement(name)->getValueAsFloat64(0);
	}

	Datetime ElementPtr::getElementAsDatetime(const char* name) const
	{
		return this->getElement(name)->getValueAsDatetime(0);
	}

	const char* ElementPtr::getElementAsString(const char* name) const
	{
		return this->getElement(name)->getValueAsString(0);
	}
}