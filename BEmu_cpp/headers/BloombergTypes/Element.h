//------------------------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="headers/BloombergTypes/Element.h" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------------------------

#pragma once

#include "bemu_headers.h"
#include <exception>

namespace BEmu
{
	class Name;
	class ElementPtr;
	class Datetime;

	class Element
	{
		private:
			const ElementPtr * _ptr;

		public:
			Element(const ElementPtr* arg);

			DLL_EXPORT Element();
			DLL_EXPORT Element(const Element& arg);
			DLL_EXPORT Element& operator=(const Element &rhs);

			class ElementException: public std::exception
			{
				virtual const char* what() const throw()
				{
					return "My exception happened";
				}
			} elementEx;

			DLL_EXPORT Name name() const;
			DLL_EXPORT int numValues() const;
			DLL_EXPORT int numElements() const;
		
			DLL_EXPORT bool isNull() const;
			DLL_EXPORT bool isArray() const;
			DLL_EXPORT bool isComplexType() const;

			//The C++ version of the code doesn't have a getValue() function (Java and C# do)

			DLL_EXPORT bool getValueAsBool(int index) const;
			DLL_EXPORT int getValueAsInt32(int index) const;
			DLL_EXPORT long getValueAsInt64(int index) const;
			DLL_EXPORT float getValueAsFloat32(int index) const;
			DLL_EXPORT double getValueAsFloat64(int index) const;
			DLL_EXPORT Datetime getValueAsDatetime(int index) const;
			DLL_EXPORT char* getValueAsString(int index) const;
			DLL_EXPORT Element getValueAsElement(int index) const;
		
			DLL_EXPORT Element getElement(int position) const;
			DLL_EXPORT bool hasElement(const char* name, bool excludeNullElements = false) const;
			DLL_EXPORT bool hasElement(const Name& name, bool excludeNullElements = false) const;
			
			DLL_EXPORT Element getElement(const char* name) const;
			DLL_EXPORT Element getElement(const Name& name) const;

			DLL_EXPORT bool getElementAsBool(const char* name) const;
			DLL_EXPORT bool getElementAsBool(const Name& name) const;

			DLL_EXPORT int getElementAsInt32(const char* name) const;
			DLL_EXPORT int getElementAsInt32(const Name& name) const;

			DLL_EXPORT long getElementAsInt64(const char* name) const;
			DLL_EXPORT long getElementAsInt64(const Name& name) const;

			DLL_EXPORT float getElementAsFloat32(const char* name) const;
			DLL_EXPORT float getElementAsFloat32(const Name& name) const;

			DLL_EXPORT double getElementAsFloat64(const char* name) const;
			DLL_EXPORT double getElementAsFloat64(const Name& name) const;

			DLL_EXPORT Datetime getElementAsDatetime(const char* name) const;
			DLL_EXPORT Datetime getElementAsDatetime(const Name& name) const;

			DLL_EXPORT const char* getElementAsString(const char* name) const;
			DLL_EXPORT const char* getElementAsString(const Name& name) const;

			DLL_EXPORT std::ostream& print(std::ostream& stream, int level = 0, int spacesPerLevel = 4) const;
	};

	inline std::ostream& operator<< (std::ostream& out, const Element& mc)
	{
		mc.print(out);
		return out;
	}

}