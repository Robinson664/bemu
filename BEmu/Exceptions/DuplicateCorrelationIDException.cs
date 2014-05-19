//------------------------------------------------------------------------------
// <copyright project="BEmu_csh" file="Exceptions/DuplicateCorrelationIDException.cs" company="Jordan Robinson">
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
    public class DuplicateCorrelationIDException : ApplicationException
    {
        public DuplicateCorrelationIDException() : base()
        {
        }

        public DuplicateCorrelationIDException(string description) : base(description)
        {
        }

        public DuplicateCorrelationIDException(string description, Exception cause) : base(description, cause)
        {
        }

        public string Description { get { return base.Message; } }
    }
}
