//------------------------------------------------------------------------------------------------
// <copyright project="BEmu_cpp" file="headers/BloombergTypes/Request.h" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------------------------

#pragma once

#include "bemu_headers.h"
#include "BloombergTypes/RequestPtr.h"

namespace BEmu
{
	class Request
	{
		private:

			//The way I'm doing polymorphism is a little broken because actual Bloomberg API functions like Service.createRequest(...) returns a value rather than a reference.
			//  Because I use several derived Request classes to emulate the behavior of the API's *one* Request object, I have some work to do to ensure the caller is calling the right functions.
			//  When casting from a derived-Request to this parent Request, I internally keep a pointer to the derived-Request so that I know how to pass around function calls.
			//  If each Request object keeps a pointer to some internal RequestPtr object, the user doesn't have to know that I've implemented the Request type as a collection of derived classes.
			//One downside is that I don't know when to delete this->_ptr.  I can't do it in a ~Request() because that gets called often and at the wrong times.
			//  I could possibly delete this pointer in a ~Session() because once a caller closes a session, why not delete all related Requests.
			//  I'm not going to do that though because it is probably not how the actual Bloomberg API handles this.
			//  I'll leave this pointer allocated, meaning this is a memory leak.  As this emulator is not built for performance, it's probably ok.
			RequestPtr *_ptr;

		public:
			RequestPtr * getRequestPtr() const;

			DLL_EXPORT Request();
			DLL_EXPORT Request(RequestPtr *ptr);
			DLL_EXPORT Request(const Request& arg);
			DLL_EXPORT Request& operator=(const Request &rhs);
			
			DLL_EXPORT void append(const char* name, const char* value);
			DLL_EXPORT void append(const Name& name, const char* value);

			DLL_EXPORT void set(const char* name, const char* value);
			DLL_EXPORT void set(const Name& name, const char* value);

			DLL_EXPORT void set(const char* name, const Datetime& value);
			DLL_EXPORT void set(const Name& name, const Datetime& value);

			DLL_EXPORT void set(const char* name, bool value);
			DLL_EXPORT void set(const Name& name, bool value);

			DLL_EXPORT void set(const char* name, int value);
			DLL_EXPORT void set(const Name& name, int value);
	};
}