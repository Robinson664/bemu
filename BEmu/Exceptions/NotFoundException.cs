//------------------------------------------------------------------------------
// <copyright project="BEmu_csh" file="Exceptions/NotFoundException.cs" company="Jordan Robinson">
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
    public class NotFoundException : ApplicationException
    {
        public NotFoundException() : base()
        {
        }

        public NotFoundException(string description) : base(description)
        {
        }

        public NotFoundException(string description, Exception cause) : base(description, cause)
        {
        }

        public string Description { get { return base.Message; } }
    }
}
