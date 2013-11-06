//------------------------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="headers/BloombergTypes/ElementPtr.h" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------------------------

#pragma once

#include "BloombergTypes/Datetime.h"
#include <exception>
#include <sstream>

namespace BEmu
{
	class Name;

	class ElementPtr
	{
		protected:
			void prettyPrintHelper(std::ostream& stream, int tabIndent, int spacesPerTab, const std::string value) const;
			void prettyPrintHelper(std::ostream& stream, int tabIndent, int spacesPerTab, const int value) const;
			void prettyPrintHelper(std::ostream& stream, int tabIndent, int spacesPerTab, const double value) const;
			void prettyPrintHelper(std::ostream& stream, int tabIndent, int spacesPerTab, const Datetime& value) const;
			
			static const char * toCharPointer(std::string& arg);
			static const char * toCharPointer(std::stringstream& arg);
			static const char * toCharPointer(int arg);
			static const char * toCharPointer(double arg);
			static const char * toCharPointer(const Datetime& arg);
			
			static std::string toString(int i);

		public:

			class ElementPtrException: public std::exception
			{
				virtual const char* what() const throw()
				{
					return "My exception happened";
				}
			} elementPtrEx;

			virtual Name name() const;
			virtual size_t numValues() const;
			virtual size_t numElements() const;
		
			virtual bool isNull() const;
			virtual bool isArray() const;
			virtual bool isComplexType() const;

			//The C++ version of the code doesn't have a getValue() function

			virtual bool getValueAsBool(int index) const;
			virtual int getValueAsInt32(int index) const;
			virtual long getValueAsInt64(int index) const;
			virtual float getValueAsFloat32(int index) const;
			virtual double getValueAsFloat64(int index) const;
			virtual Datetime getValueAsDatetime(int index) const;
			virtual const char * getValueAsString(int index) const;
			virtual ElementPtr * getValueAsElement(int index) const;
		
			virtual ElementPtr * getElement(int position) const;
			virtual bool hasElement(const char* name, bool excludeNullElements = false) const;
			bool hasElement(const Name& name, bool excludeNullElements = false) const;
			
			virtual ElementPtr * getElement(const char* name) const;
			ElementPtr * getElement(const Name& name) const;

			virtual bool getElementAsBool(const char* name) const;
			bool getElementAsBool(const Name& name) const;

			virtual int getElementAsInt32(const char* name) const;
			int getElementAsInt32(const Name& name) const;

			virtual long getElementAsInt64(const char* name) const;
			long getElementAsInt64(const Name& name) const;

			virtual float getElementAsFloat32(const char* name) const;
			float getElementAsFloat32(const Name& name) const;

			virtual double getElementAsFloat64(const char* name) const;
			double getElementAsFloat64(const Name& name) const;

			virtual Datetime getElementAsDatetime(const char* name) const;
			Datetime getElementAsDatetime(const Name& name) const;

			virtual const char* getElementAsString(const char* name) const;
			const char* getElementAsString(const Name& name) const;

			virtual std::ostream& print(std::ostream& stream, int level = 0, int spacesPerLevel = 4) const;
	};

	inline std::ostream& operator<< (std::ostream& out, const ElementPtr& mc)
	{
		mc.print(out);
		return out;
	}
}