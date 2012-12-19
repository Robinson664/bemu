using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace BEmu3
{
    public abstract class Request
    {
        internal CorrelationID correlationId { get; set; }

        public virtual void Append(string name, string elementValue)
        {
            throw new NotImplementedException("BEmu3.Request.Append: Append is not implemented");
        }

        public virtual void Append(Name name, string elementValue)
        {
            this.Append(name.ToString(), elementValue);
        }

        public virtual void Set(Name name, string elementValue)
        {
            throw new NotImplementedException("BEmu3.Request.Set: string is not implemented");
        }

        public virtual void Set(Name name, bool elementValue)
        {
            throw new NotImplementedException("BEmu3.Request.Set: bool is not implemented");
        }

        public virtual void Set(Name name, int elementValue)
        {
            throw new NotImplementedException("BEmu3.Request.Set: int is not implemented");
        }

        public virtual Element this[Name name]
        {
            get { throw new NotImplementedException("BEmu3.Request.this[]: by name is not implemented"); }
        }

        public virtual Element this[string name]
        {
            get { throw new NotImplementedException("BEmu3.Request.this[]: by string is not implemented"); }
        }

        public virtual IEnumerable<Element> Elements
        {
            get { throw new NotImplementedException("BEmu3.Request: Elements is not implemented"); }
        }
    }
}
