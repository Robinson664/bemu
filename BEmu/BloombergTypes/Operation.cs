//------------------------------------------------------------------------------
// <copyright project="BEmu_csh" file="BloombergTypes/Operation.cs" company="Jordan Robinson">
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

    public class Operation
    {
        internal Operation() { }

        public string Description { get { throw new NotImplementedException(); } }
        public Name Name { get { throw new NotImplementedException(); } }
        public int NumResponseDefinition { get { throw new NotImplementedException(); } }
        public SchemaElementDefinition RequestDefinition { get { throw new NotImplementedException(); } }

        [Obsolete("Deprecated as of 3.2.1, use RequestDefinition")]
        public SchemaTypeDefinition RequestType { get { throw new NotImplementedException(); } }

        public IEnumerable<SchemaElementDefinition> ResponseDefinitions { get { throw new NotImplementedException(); } }

        [Obsolete("Deprecated as of 3.2.1, use ResponseDefinition")]
        public SchemaTypeDefinition[] ResponseType { get { throw new NotImplementedException(); } }

        public Schema.Status Status { get { throw new NotImplementedException(); } }

        public SchemaElementDefinition GetResponseDefinition(int index)
        {
            throw new NotImplementedException();
        }
    }
}