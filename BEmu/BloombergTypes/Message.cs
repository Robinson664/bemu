//------------------------------------------------------------------------------
// <copyright project="BEmu_csh" file="BloombergTypes/Message.cs" company="Jordan Robinson">
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

    public abstract class Message
    {
        private readonly CorrelationID _correlationId;
        public CorrelationID CorrelationID { get { return this._correlationId; } }

        private readonly Name _messageType;
        public Name MessageType { get { return this._messageType; } }

        private readonly Service _service;
        public Service Service { get { return this._service; } }

        protected Message(Name messageType, CorrelationID corr, Service service)
        {
            this._correlationId = corr;
            this._messageType = messageType;
            this._service = service;
        }

        public Element GetElement(Name name)
        {
            return this.GetElement(name.ToString());
        }

        public Element GetElement(string name)
        {
            return this[name];
        }

        public virtual Element AsElement
        {
            get { throw new NotImplementedException("BEmu.Message.AsElement is not implemented for this message type"); }
        }

        public Element this[string name]
        {
            get
            {
                foreach (var item in this.Elements)
                {
                    if (item.Name.ToString() == name)
                        return item;
                }
                throw new IndexOutOfRangeException("name is case-sensitive");
            }
        }

        public virtual object this[string name, int index]
        {
            get { return this.GetElement(name).GetValue(index); }
        }

        public bool HasElement(Name name, bool excludeNullElements = false)
        {
            return this.HasElement(name.ToString(), excludeNullElements);
        }

        public bool HasElement(string name, bool excludeNullElements = false)
        {
            foreach (var item in this.Elements)
            {
                if (item.Name.ToString() == name)
                    return true;
            }
            return false;
        }

        public virtual int NumElements
        {
            get { throw new NotImplementedException("BEmu.Message.NumElements is not implemented for this message type"); }
        }

        public virtual string TopicName
        {
            get { throw new NotImplementedException("BEmu.Message.TopicName is not implemented for this message type"); }
        }

        public abstract IEnumerable<Element> Elements { get; }

        public double GetElementAsFloat64(Name name) { return this.GetElementAsFloat64(name.ToString()); }
        public double GetElementAsFloat64(string name)
        {
            return this[name].GetValueAsFloat64();
        }

        public float GetElementAsFloat32(Name name) { return this.GetElementAsFloat32(name.ToString()); }
        public float GetElementAsFloat32(string name)
        {
            return this[name].GetValueAsFloat32();
        }

        public long GetElementAsInt64(Name name) { return this.GetElementAsInt64(name.ToString()); }
        public long GetElementAsInt64(string name)
        {
            return this[name].GetValueAsInt64();
        }

        public int GetElementAsInt32(Name name) { return this.GetElementAsInt32(name.ToString()); }
        public int GetElementAsInt32(string name)
        {
            return this[name].GetValueAsInt32();
        }

        public string GetElementAsString(Name name) { return this.GetElementAsString(name.ToString()); }
        public string GetElementAsString(string name)
        {
            return this[name].GetValueAsString();
        }

        public Datetime GetElementAsDatetime(Name name) { return this.GetElementAsDatetime(name.ToString()); }
        public Datetime GetElementAsDatetime(string name)
        {
            return this[name].GetValueAsDatetime();
        }

        public Datetime GetElementAsTime(Name name) { return this.GetElementAsTime(name.ToString()); }
        public Datetime GetElementAsTime(string name)
        {
            return this[name].GetValueAsTime();
        }

        public Datetime GetElementAsDate(Name name) { return this.GetElementAsDate(name.ToString()); }
        public Datetime GetElementAsDate(string name)
        {
            return this[name].GetValueAsDate();
        }



    }
}
