using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace BEmu3.ReferenceDataRequest
{
    public class ElementReferenceSecurityData : Element
    {
        private readonly ElementReferenceString _elmSecurityName;
        private readonly ElementReferenceInt _elmSequenceNumber;
        private readonly ElementReferenceFieldData _elmFieldData;

        internal ElementReferenceSecurityData(string securityName, Dictionary<string, object> fieldData, int sequenceNumber)
        {
            this._elmSecurityName = new ElementReferenceString("security", securityName);
            this._elmSequenceNumber = new ElementReferenceInt("sequenceNumber", sequenceNumber);
            this._elmFieldData = new ElementReferenceFieldData(fieldData);
        }

        public override int NumElements { get { return 3; } }
        public override int NumValues { get { return 0; } }
        public override Name Name { get { return new Name("securityData"); } }

        public override string GetElementAsString(string name)
        {
            if (name.ToUpper() == this._elmSecurityName.Name.ToString().ToUpper())
                return (string)this._elmSecurityName.GetValue();
            else
                return base.GetElementAsString(name);
        }

        public override object this[int index] { get { return null; } }

        public override Element GetElement(string name)
        {
            return this[name];
        }

        public override Element this[string name]
        {
            get
            {
                switch (name.ToUpper())
                {
                    case "FIELDDATA":
                        return this._elmFieldData;
                    case "SECURITY":
                        return this._elmSecurityName;
                    case "SEQUENCENUMBER":
                        return this._elmSequenceNumber;
                }
                return base[name];
            }
        }

        public override object this[string name, int index]
        {
            get
            {
                string strName = name.ToUpper();
                if (name == this._elmFieldData.Name.ToString().ToUpper())
                    return base[name, index];
                else if (index == 0)
                    return this[name].GetValue();
                else
                    return null;
            }
        }

        internal override StringBuilder PrettyPrint(int tabIndent)
        {
            string tabs = Types.IndentType.Indent(tabIndent);
            StringBuilder result = new StringBuilder();

            result.AppendFormat("{0}{1} = {{{2}", tabs, this.Name, Environment.NewLine);
            result.Append(this._elmSecurityName.PrettyPrint(tabIndent + 1));
            result.Append(this._elmSequenceNumber.PrettyPrint(tabIndent + 1));
            result.Append(this._elmFieldData.PrettyPrint(tabIndent + 1));
            result.AppendFormat("{0}}}{1}", tabs, Environment.NewLine);

            return result;
        }
    }
}
