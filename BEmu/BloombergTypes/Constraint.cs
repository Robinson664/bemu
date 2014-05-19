//------------------------------------------------------------------------------
// <copyright project="BEmu_csh" file="BloombergTypes/Constraint.cs" company="Jordan Robinson">
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

    public class Constraint
    {
        private Constraint() { }

        public Name ConstraintType { get { throw new NotImplementedException(); } }
        public ConstantsList Values { get { throw new NotImplementedException(); } }

        public void Print(Stream output)
        {
            throw new NotImplementedException();
        }

        public void Print(TextWriter writer)
        {
            throw new NotImplementedException();
        }
    }
}