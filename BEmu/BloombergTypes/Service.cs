//------------------------------------------------------------------------------
// <copyright project="BEmu" file="BloombergTypes/Service.cs" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

namespace BEmu
{
    using System;
    using System.Collections.Generic;
    using System.Linq;
    using System.Text;

    public abstract class Service
    {
        public abstract Request CreateRequest(string operationName);
        public abstract string Name { get; }
    }
}
