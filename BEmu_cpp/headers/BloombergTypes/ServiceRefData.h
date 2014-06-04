//------------------------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="headers/BloombergTypes/ServiceRefData.h" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------------------------

#pragma once

#include "BloombergTypes/Service.h"
#include <exception>
#include <boost/shared_ptr.hpp>

namespace BEmu
{
	class RequestPtr;
	class Request;

	class ServiceRefData : Service
	{
		public:
			/*DLL_EXPORT*/ virtual const char* name() const;
			/*DLL_EXPORT*/ RequestPtr* createRequestPtr(const char* operation) const;
			// /*DLL_EXPORT*/ virtual Request createRequest(const char* operation) const;

			/*DLL_EXPORT*/ boost::shared_ptr<RequestPtr> createRequestPtr2(const char* operation) const;
			/*DLL_EXPORT*/ Request createRequest2(const char* operation) const;

			class ServiceRefDataException: public std::exception
			{
				virtual const char* what() const throw()
				{
					return "My exception happened";
				}
			} serviceRefDataEx;
	};
}