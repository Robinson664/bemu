//------------------------------------------------------------------------------
// <copyright project="BEmu" file="IntradayBarRequest/RequestIntradayBarElementBool.cs" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

namespace BEmu.IntradayBarRequest
{
    using System;
    using System.Collections.Generic;
    using System.Linq;
    using System.Text;

    internal class RequestIntradayBarElementBool : RequestIntradayBarElementString
    {
        private readonly bool _value;

        internal RequestIntradayBarElementBool(string elementName, bool value)
            : base(elementName, value.ToString().ToLower())
        {
            this._value = value;
        }

        //I can't override GetElementAsBool here because the Bloomberg Request object stores bools as strings, not bools.  You can't convert the string to a bool
        internal bool GetBool { get { return this._value; } } 
    }
}
