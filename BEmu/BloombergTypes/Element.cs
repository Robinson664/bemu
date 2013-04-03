//------------------------------------------------------------------------------
// <copyright project="BEmu" file="BloombergTypes/Element.cs" company="Jordan Robinson">
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

    public abstract class Element
    {
        internal abstract StringBuilder PrettyPrint(int tabIndent);
        public abstract Name Name { get; }
        public abstract int NumValues { get; }
        public abstract int NumElements { get; }

        public override string ToString()
        {
            return this.PrettyPrint(0).ToString();
        }

        protected StringBuilder PrettyPrintHelper(int tabIndent, string value)
        {
            string tabs = Types.IndentType.Indent(tabIndent);
            StringBuilder result = new StringBuilder(string.Format("{0}{1} = {2}{3}", tabs, this.Name, value, Environment.NewLine));
            return result;
        }

        public virtual bool IsNull
        {
            get { throw new NotImplementedException("Element doesn't support IsNull"); }
        }

        public virtual bool IsArray
        {
            get { throw new NotImplementedException("Element doesn't support IsArray"); }
        }

        public virtual bool IsComplexType
        {
            get { throw new NotImplementedException("Element doesn't support IsComplexType"); }
        }

        public virtual object GetValue() { return this.GetValue(0); }
        public virtual object GetValue(int index)
        {
            throw new NotImplementedException("Element is not a simple object (index)");
        }

        public string GetElementAsString(Name name) { return this.GetElementAsString(name.ToString()); }
        public virtual string GetElementAsString(string name)
        {
            throw new NotImplementedException("Element doesn't support getting elements as strings");
        }

        public Datetime GetElementAsTime(Name name) { return this.GetElementAsTime(name.ToString()); }
        public virtual Datetime GetElementAsTime(string name)
        {
            throw new NotImplementedException("Element doesn't support getting elements as Times");
        }

        public Datetime GetElementAsDate(Name name) { return this.GetElementAsDate(name.ToString()); }
        public virtual Datetime GetElementAsDate(string name)
        {
            throw new NotImplementedException("Element doesn't support getting elements as Dates");
        }

        public Datetime GetElementAsDatetime(Name name) { return this.GetElementAsDatetime(name.ToString()); }
        public virtual Datetime GetElementAsDatetime(string name)
        {
            throw new NotImplementedException("Element doesn't support getting elements as Datetimes");
        }

        public int GetElementAsInt32(Name name) { return this.GetElementAsInt32(name.ToString()); }
        public virtual int GetElementAsInt32(string name)
        {
            throw new NotImplementedException("Element doesn't support getting elements as Int32");
        }

        public long GetElementAsInt64(Name name) { return this.GetElementAsInt64(name.ToString()); }
        public virtual long GetElementAsInt64(string name)
        {
            throw new NotImplementedException("Element doesn't support getting elements as Int64");
        }

        public double GetElementAsFloat64(Name name) { return this.GetElementAsFloat64(name.ToString()); }
        public virtual double GetElementAsFloat64(string name)
        {
            throw new NotImplementedException("Element doesn't support getting elements as Float64");
        }

        public bool GetElementAsBoolean(Name name) { return this.GetElementAsBool(name.ToString()); }
        public virtual bool GetElementAsBool(string name)
        {
            throw new NotImplementedException("Element doesn't support getting elements as bool");
        }

        public float GetElementAsFloat32(Name name) { return this.GetElementAsFloat32(name.ToString()); }
        public virtual float GetElementAsFloat32(string name)
        {
            throw new NotImplementedException("Element doesn't support getting elements as Float32");
        }

        public virtual Element GetValueAsElement() { return this.GetValueAsElement(0); }
        public virtual Element GetValueAsElement(int index)
        {
            throw new NotImplementedException("Element doesn't support getting values as elements (index)");
        }

        public virtual string GetValueAsString(int i)
        {
            throw new NotImplementedException("Element doesn't support GetValueAsString by index");
        }

        public virtual float GetValueAsFloat32()
        {
            throw new NotImplementedException("Element doesn't support GetValueAsFloat32");
        }

        public virtual double GetValueAsFloat64()
        {
            throw new NotImplementedException("Element doesn't support GetValueAsFloat64");
        }

        public virtual double GetValueAsFloat64(int index)
        {
            throw new NotImplementedException("Element doesn't support GetValueAsFloat64");
        }

        public virtual int GetValueAsInt32()
        {
            throw new NotImplementedException("Element doesn't support GetValueAsInt32");
        }

        public virtual int GetValueAsInt32(int index)
        {
            throw new NotImplementedException("Element doesn't support GetValueAsInt32");
        }

        public virtual long GetValueAsInt64()
        {
            throw new NotImplementedException("Element doesn't support GetValueAsInt64");
        }

        public virtual long GetValueAsInt64(int index)
        {
            throw new NotImplementedException("Element doesn't support GetValueAsInt64");
        }

        public virtual string GetValueAsString()
        {
            throw new NotImplementedException("Element doesn't support GetValueAsString");
        }

        public virtual Datetime GetValueAsDatetime()
        {
            throw new NotImplementedException("Element doesn't support GetValueAsDatetime");
        }

        public virtual Datetime GetValueAsDatetime(int index)
        {
            throw new NotImplementedException("Element doesn't support GetValueAsDatetime");
        }

        public virtual Datetime GetValueAsDate()
        {
            throw new NotImplementedException("Element doesn't support GetValueAsDate");
        }

        public virtual Datetime GetValueAsDate(int index)
        {
            throw new NotImplementedException("Element doesn't support GetValueAsDate");
        }

        public virtual Datetime GetValueAsTime()
        {
            throw new NotImplementedException("Element doesn't support GetValueAsTime");
        }

        public virtual Datetime GetValueAsTime(int index)
        {
            throw new NotImplementedException("Element doesn't support GetValueAsTime");
        }



        public Element GetElement(Name name)
        {
            return this.GetElement(name.ToString());
        }

        public virtual Element GetElement(string name)
        {
            throw new NotImplementedException("Element doesn't support getting elements by name");
        }

        public virtual Element GetElement(int index)
        {
            throw new NotImplementedException("Element doesn't support getting elements by index");
        }

        public virtual IEnumerable<Element> Elements
        {
            get { throw new NotImplementedException("Element doesn't support Elements getter"); }
        }

        public virtual object this[int index]
        {
            get { throw new NotImplementedException("Element doesn't support this[int index]"); }
        }

        public virtual Element this[string name]
        {
            get { throw new NotImplementedException("Element doesn't support this[string name]"); }
        }

        public Element this[Name name]
        {
            get { return this[name.ToString()]; }
        }

        public virtual object this[string name, int index]
        {
            get { throw new NotImplementedException("Element doesn't support this[string name, int index]"); }
        }

        public bool HasElement(Name name, bool excludeNullElements = false)
        {
            return this.HasElement(name.ToString(), excludeNullElements);
        }

        public virtual bool HasElement(string name, bool excludeNullElements = false)
        {
            throw new NotImplementedException("Element doesn't support HasElement");
        }

        public virtual Element AppendElement()
        {
            throw new NotImplementedException("Element doesn't support AppendElement");
        }

        public void SetElement(Name name, object value)
        {
            this.SetElement(name.ToString(), value);
        }

        public virtual void SetElement(string name, object value)
        {
            throw new NotImplementedException("Element doesn't support SetElement(Name name, string value)");
        }
        
    }
}
