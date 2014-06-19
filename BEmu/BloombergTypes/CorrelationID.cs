//------------------------------------------------------------------------------
// <copyright project="BEmu_csh" file="BloombergTypes/CorrelationID.cs" company="Jordan Robinson">
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

    public class CorrelationID
    {
        //                                            IsInternal | IsObject | IsValue
        private const int CONSTRUCTED_OBJECT = 7; //      false  |  true    |  false
        private const int CONSTRUCTED_VALUE = 3;  //      false  |  false   |  true
        private const int INTERNAL_VALUE = 1;     //      true   |  false   |  true
        private const int UNINITIALIZED = 0;      //      true   |  false   |  true

        #region NOT PART OF DLL
        private const int IS_NOT_INTERNAL = 2;
        private const int IS_OBJECT = 4;
        #endregion

        private readonly int _corrType;

        public bool IsInternal { get { return (this._corrType & IS_NOT_INTERNAL) == 0; } }
        public bool IsObject { get { return (this._corrType & IS_OBJECT) != 0; } }
        public bool IsValue { get { return (this._corrType & IS_OBJECT) == 0; } }

        private readonly long _value;
        public long Value { get { return this._value; } }

        private readonly object _object;
        public object Object { get { return this._object; } }

        private static long _nextInternalCorrelationId = 1; //initial correlation ID

        public CorrelationID(object value)
        {
            if (value == null)
                throw new NullReferenceException(); //[sic]

            this._corrType = CorrelationID.CONSTRUCTED_OBJECT;
            this._value = 0L;
            this._object = value;
        }

        public CorrelationID(long value)
        {
            this._corrType = CorrelationID.CONSTRUCTED_VALUE;
            this._value = value;
            this._object = null;
        }

        public CorrelationID(CorrelationID value)
        {
            this._corrType = value._corrType;
            this._value = value._value;
            this._object = value._object;
        }

        internal CorrelationID()
        {
            this._corrType = CorrelationID.INTERNAL_VALUE;
            this._value = CorrelationID._nextInternalCorrelationId++;
            this._object = null;
        }

        public override bool Equals(object obj)
        {
            if (this == obj)
            {
                return true;
            }
            if (!(obj is CorrelationID))
            {
                return false;
            }
            CorrelationID correlationID = (CorrelationID)obj;

            if (this._corrType != correlationID._corrType)
            {
                return false;
            }
            if (this.IsValue)
            {
                return this._corrType == correlationID._corrType;
            }
            return this._object.Equals(correlationID._object);
        }

        public override int GetHashCode()
        {
            if (!this.IsValue)
                return this._object.GetHashCode();
            else
                return (int)(this._value ^ this._value >> 32);
        }

        public override string ToString()
        {
            switch (this._corrType)
            {
                case UNINITIALIZED: return "Uninitialized";
                case INTERNAL_VALUE: return "Internal: " + this._value;
                case CONSTRUCTED_VALUE: return "User: " + this._value;
            }
            return "User: " + this._object.ToString();
        }
    }
}
