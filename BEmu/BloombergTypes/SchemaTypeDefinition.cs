//------------------------------------------------------------------------------
// <copyright project="BEmu_csh" file="BloombergTypes/SchemaTypeDefinition.cs" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Bloomberglp.Blpapi
{
    public class SchemaTypeDefinition
    {
        internal SchemaTypeDefinition(Schema.Datatype datatype)
        {
            this._datatype = datatype;
            this._name = new Name(this._datatype.ToString());
        }

        internal SchemaTypeDefinition(Schema.Datatype datatype, Name name)
        {
            this._datatype = datatype;
            this._name = name;
        }

        private readonly Schema.Datatype _datatype;
        private readonly Name _name;

        public Name Name { get { return this._name; } }

        public override string ToString()
        {
            return string.Format("Type {0}{1}", this._datatype.ToString(), Environment.NewLine);
        }
    }
}
