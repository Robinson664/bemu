//------------------------------------------------------------------------------
// <copyright project="BEmu" file="BloombergTypes/CorrelationID.cs" company="Jordan Robinson">
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

    public class CorrelationID
    {
        private readonly bool _isInternal;
        public bool IsInternal { get { return this._isInternal; } }

        private readonly long _value;
        public long Value { get { return this._value; } }

        private static long _nextInternalCorrelationId = 1; //initial correlation ID

        public CorrelationID(long value)
        {
            this._value = value;
            this._isInternal = false;
        }

        internal CorrelationID()
        {
            this._value = CorrelationID._nextInternalCorrelationId++;
            this._isInternal = true;
        }

        public override string ToString()
        {
            return string.Format("{0}: {1}",
                this._isInternal ? "Internal" : "User",
                this._value);
        }
    }
}
