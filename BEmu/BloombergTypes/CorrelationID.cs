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
        private readonly bool _isInternal;
        public bool IsInternal { get { return this._isInternal; } }

        private readonly bool _isObject;
        public bool IsObject { get { return this._isObject; } }

        private readonly bool _isValue;
        public bool IsValue { get { return this._isValue; } }

        private readonly long _value;
        public long Value { get { return this._value; } }

        private readonly object _object;
        public object Object { get { return this._object; } }

        private static long _nextInternalCorrelationId = 1; //initial correlation ID

        public CorrelationID(object value)
        {
            if (value == null)
                throw new NullReferenceException(); //[sic]

            this._isValue = false;
            this._isObject = true;
            this._isInternal = false;
            this._object = value;
        }

        public CorrelationID(long value)
        {
            this._isValue = true;
            this._isObject = false;
            this._isInternal = false;
            this._value = value;
        }

        public CorrelationID(CorrelationID value)
        {
            this._isValue = value._isValue;
            this._isObject = value._isObject;
            this._isInternal = value._isInternal;
            this._value = value._value;
        }

        internal CorrelationID()
        {
            this._isValue = true;
            this._isObject = false;
            this._isInternal = true;
            this._value = CorrelationID._nextInternalCorrelationId++;
        }

        public override bool Equals(object obj)
        {
            var corr = obj as CorrelationID;

            if (corr == null) //either obj is null, or obj is not a CorrelationID
                return false;

            else if (this._isObject != corr._isObject)
                return false;

            else if (this._isObject)
                return object.ReferenceEquals(this._object, corr._object);

            else //value
                return this._value == corr._value;
        }

        public override int GetHashCode()
        {
            if (this._isObject)
                return this._object.GetHashCode();

            else if (this._isValue)
                return this._value.GetHashCode();

            else
                throw new NotImplementedException();
        }

        public override string ToString()
        {
            if (this._isValue)
                return string.Format("{0}: {1}",
                    this._isInternal ? "Internal" : "User",
                    this._value);

            else //object
                return string.Format("{0}: {1}",
                    this._isInternal ? "Internal" : "User",
                    this._object.ToString());
        }
    }
}
