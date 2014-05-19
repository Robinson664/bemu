//------------------------------------------------------------------------------
// <copyright project="BEmu_csh" file="BloombergTypes/Constant.cs" company="Jordan Robinson">
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
    using System.IO;

    public class Constant
    {
        private Constant() { }

        public Schema.Datatype Datatype { get { throw new NotImplementedException(); } }
        public string Description { get { throw new NotImplementedException(); } }
        public Name Name { get { throw new NotImplementedException(); } }
        public Schema.Status Status { get { throw new NotImplementedException(); } }
        
        public object UserData
        {
            get { throw new NotImplementedException(); }
            set { throw new NotImplementedException(); }
        }

        public char GetValueAsChar() { throw new NotImplementedException(); }
        [Obsolete("Deprecated since 3.2.1. Use GetValueAsDatetime() instead")]
        public Datetime GetValueAsDate() { throw new NotImplementedException(); }
        public Datetime GetValueAsDatetime() { throw new NotImplementedException(); }
        public float GetValueAsFloat32() { throw new NotImplementedException(); }
        public double GetValueAsFloat64() { throw new NotImplementedException(); }
        public int GetValueAsInt32() { throw new NotImplementedException(); }
        public long GetValueAsInt64() { throw new NotImplementedException(); }
        public string GetValueAsString() { throw new NotImplementedException(); }
        [Obsolete("Deprecated since 3.2.1. Use GetValueAsDatetime() instead")]
        public Datetime GetValueAsTime() { throw new NotImplementedException(); }
        public void Print(Stream output) { throw new NotImplementedException(); }
        public void Print(TextWriter writer) { throw new NotImplementedException(); }
    }
}