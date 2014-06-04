//------------------------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="headers/Types/ObjectType.h" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------------------------

#pragma once

#include "BloombergTypes/Datetime.h"
#include <boost/shared_ptr.hpp>

namespace BEmu
{
	namespace ReferenceDataRequest
	{
		class ReferenceElementArrayChainTickers;
	}

	class ObjectType
	{
		public:
			enum ObjectTypeEnum { eDouble, eInt, eBool, eString, eDatetime, eChainTickers, eNothing };

			ObjectType(); //null
			ObjectType(double arg);
			ObjectType(int arg);
			ObjectType(bool arg);
			ObjectType(const std::string& arg);
			ObjectType(const char * arg);
			ObjectType(const Datetime& arg);

			//ObjectType(ReferenceDataRequest::ReferenceElementArrayChainTickers * arg);
			ObjectType(boost::shared_ptr<ReferenceDataRequest::ReferenceElementArrayChainTickers> arg);

			~ObjectType();

			ObjectType& operator=(const ObjectType &rhs);
			ObjectType(const ObjectType& arg);

			ObjectTypeEnum GetType() const;
			bool TryGetDouble(double &arg) const;
			bool TryGetInt(int &arg) const;
			bool TryGetBool(bool &arg) const;
			bool TryGetString(std::string& arg) const;
			bool TryGetDatetime(Datetime& arg) const;

			//bool TryGetChainTickers(ReferenceDataRequest::ReferenceElementArrayChainTickers * arg) const;
			bool TryGetChainTickers(boost::shared_ptr<ReferenceDataRequest::ReferenceElementArrayChainTickers> arg) const;

			double ValueAsDouble() const;
			int ValueAsInt() const;
			bool ValueAsBool() const;
			std::string ValueAsString() const;
			Datetime ValueAsDatetime() const;

			//ReferenceDataRequest::ReferenceElementArrayChainTickers * ValueAsChainTickers() const;
			boost::shared_ptr<ReferenceDataRequest::ReferenceElementArrayChainTickers> ValueAsChainTickers() const;
			
			bool IsNull() const;
			std::string ToString() const;
			
			//I pass around ObjectTypes mostly by value. But the values may all point to the same _chainTickers instance.  Use DeleteMemory to delete _chainTickers.
			void deleteMemory();

			class ObjectTypeException: public std::exception
			{
				virtual const char* what() const throw()
				{
					return "My exception happened";
				}
			} objectTypeEx;

		private:
			ObjectTypeEnum _otype;

			double _dbl;
			int _int;
			bool _bool;
			std::string _str;
			Datetime _datetime;

			//ReferenceDataRequest::ReferenceElementArrayChainTickers * _chainTickers;
			boost::shared_ptr<ReferenceDataRequest::ReferenceElementArrayChainTickers> _chainTickers;
	};
}