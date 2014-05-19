//------------------------------------------------------------------------------
// <copyright project="BEmu_csh" file="BloombergTypes/Schema.cs" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

namespace Bloomberglp.Blpapi
{
    using System;
    using System.Collections.Generic;
    using System.Linq;
    using System.Text;

    public class Schema
    {
        public enum Datatype
        {
            BOOL = 0,
            CHAR = 1,
            DATE = 2,
            DATETIME = 3,
            FLOAT32 = 5,
            FLOAT64 = 6,
            INT32 = 7,
            INT64 = 8,
            STRING = 9,
            TIME = 10,
            BYTEARRAY = 256,
            ENUMERATION = 257,
            SEQUENCE = 258,
            CHOICE = 259,
        }

        public enum Status
        {
            ACTIVE = 0,
            DEPRECATED = 1,
            INACTIVE = 2,
            PENDING_DEPRECATION = 3,
        }
    }
}
