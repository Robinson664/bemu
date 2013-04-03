//------------------------------------------------------------------------------
// <copyright project="BEmu" file="BloombergTypes/Request.cs" company="Jordan Robinson">
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

    public abstract class Request
    {
        internal CorrelationID correlationId { get; set; }

        public virtual void Append(string name, string elementValue)
        {
            throw new NotImplementedException("BEmu.Request.Append: Append is not implemented");
        }

        public virtual void Append(Name name, string elementValue)
        {
            this.Append(name.ToString(), elementValue);
        }

        public virtual void Set(string name, string elementValue)
        {
            throw new NotImplementedException("BEmu.Request.Set: string is not implemented");
        }

        public virtual void Set(string name, bool elementValue)
        {
            throw new NotImplementedException("BEmu.Request.Set: bool is not implemented");
        }

        public virtual void Set(string name, int elementValue)
        {
            throw new NotImplementedException("BEmu.Request.Set: int is not implemented");
        }

        public virtual void Set(string name, Datetime elementValue)
        {
            throw new NotImplementedException("BEmu.Request.Set: Datetime is not implemented");
        }

        public void Set(Name name, string elementValue)
        {
            this.Set(name.ToString(), elementValue);
        }

        public void Set(Name name, bool elementValue)
        {
            this.Set(name.ToString(), elementValue);
        }

        public void Set(Name name, int elementValue)
        {
            this.Set(name.ToString(), elementValue);
        }

        public void Set(Name name, Datetime elementValue)
        {
            this.Set(name.ToString(), elementValue);
        }

        public Element GetElement(Name name)
        {
            return this[name];
        }

        public Element GetElement(string name)
        {
            return this[name];
        }

        public virtual bool HasElement(string name)
        {
            throw new NotImplementedException("BEmu.Request.HasElement: string is not implemented");
        }

        public Element this[Name name]
        {
            get { return this[name.ToString()]; }
        }

        public virtual Element this[string name]
        {
            get { throw new NotImplementedException("BEmu.Request.this[]: by string is not implemented"); }
        }

        public virtual IEnumerable<Element> Elements
        {
            get { throw new NotImplementedException("BEmu.Request: Elements is not implemented"); }
        }
    }
}
