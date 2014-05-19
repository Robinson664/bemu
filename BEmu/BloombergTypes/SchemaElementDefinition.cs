//------------------------------------------------------------------------------
// <copyright project="BEmu_csh" file="BloombergTypes/SchemaElementDefinition.cs" company="Jordan Robinson">
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

    public class SchemaElementDefinition
    {
        public const int UNBOUNDED = -1;

        private SchemaElementDefinition() { }

        public IEnumerable<Name> AlternateNames { get { throw new NotImplementedException(); } }
        public ConstraintsList Constraints { get { throw new NotImplementedException(); } }
        public string Description { get { throw new NotImplementedException(); } }
        public int MaxValues { get { throw new NotImplementedException(); } }
        public int MinValues { get { throw new NotImplementedException(); } }
        public Name Name { get { throw new NotImplementedException(); } }
        public int NumAlternateNames { get { throw new NotImplementedException(); } }
        public Schema.Status Status { get { throw new NotImplementedException(); } }
        public SchemaTypeDefinition TypeDefinition { get { throw new NotImplementedException(); } }
        
        public object UserData
        {
            get { throw new NotImplementedException(); }
            set { throw new NotImplementedException(); }
        }

        public Name GetAlternateName(int index)
        {
            throw new NotImplementedException();
        }
    }
}