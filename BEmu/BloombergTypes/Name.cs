//------------------------------------------------------------------------------
// <copyright project="BEmu" file="BloombergTypes/Name.cs" company="Jordan Robinson">
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

    public class Name
    {
        private string _name { get; set; }

        public Name(string nameString)
        {
            this._name = nameString;
        }

        public override string ToString()
        {
            return this._name;
        }

        public override bool Equals(object obj)
        {
            return obj.ToString() == this._name;
        }

        public override int GetHashCode()
        {
            return this._name.GetHashCode();
        }

    }
}
