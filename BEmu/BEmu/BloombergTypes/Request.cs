using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace BEmu
{
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

        public virtual void Set(Name name, string elementValue)
        {
            throw new NotImplementedException("BEmu.Request.Set: string is not implemented");
        }

        public virtual void Set(Name name, bool elementValue)
        {
            throw new NotImplementedException("BEmu.Request.Set: bool is not implemented");
        }

        public virtual void Set(Name name, int elementValue)
        {
            throw new NotImplementedException("BEmu.Request.Set: int is not implemented");
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
