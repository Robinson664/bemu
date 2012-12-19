using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace BEmu3.ReferenceDataRequest
{
    public class RequestReferenceElementOverride : Element
    {
        private ElementReferenceString _fieldId;
        private ElementReferenceObject _value;

        internal RequestReferenceElementOverride()
        {
            this._fieldId = new ElementReferenceString("fieldId", "");
            this._value = new ElementReferenceObject("value", "");
        }

        public override void SetElement(Name name, object value)
        {
            switch (name.ToString().ToUpper())
            {
                case "FIELDID":
                    this._fieldId = new ElementReferenceString(name.ToString(), value.ToString());
                    break;
                case "VALUE":
                    this._value = new ElementReferenceObject(name.ToString(), value);
                    break;
                default:
                    throw new ArgumentException();
            }            
        }

        public override Name Name { get { return new Name("overrides"); } }
        public override int NumValues { get { return 1; } }
        public override int NumElements { get { return 2; } }
        public override object this[int index] { get { return null; } }

        internal override StringBuilder PrettyPrint(int tabIndent)
        {
            string tabs = Types.IndentType.Indent(tabIndent);
            StringBuilder result = new StringBuilder();

            result.AppendFormat("{0}{1} = {{{2}", tabs, this.Name, Environment.NewLine);
            result.Append(this._fieldId.PrettyPrint(tabIndent + 1));
            result.Append(this._value.PrettyPrint(tabIndent + 1));
            result.AppendFormat("{0}}}{1}", tabs, Environment.NewLine);

            return result;
        }

        public override IEnumerable<Element> Elements
        {
            get
            {
                yield return this._fieldId;
                yield return this._value;
            }
        }
        
        public override Element this[string name]
        {
            get
            {
                switch (name.ToUpper())
                {
                    case "FIELDID":
                        return this._fieldId;
                    case "VALUE":
                        return this._value;
                }
                return base[name];
            }
        }

        public override object this[string name, int index]
        {
            get
            {
                if (index == 0)
                    return this[name].GetValue();
                return base[name, index];
            }
        }

    }
}
