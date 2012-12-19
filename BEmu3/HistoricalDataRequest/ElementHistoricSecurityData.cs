using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace BEmu3.HistoricalDataRequest
{
    public class ElementHistoricSecurityData : Element
    {
        private readonly ElementHistoricString _elmSecurityName;
        private readonly ElementHistoricFieldDataArray _elmFieldDataArray;
        private readonly ElementReferenceInt _elmSequenceNumber;

        internal ElementHistoricSecurityData(string securityName, Dictionary<DateTime, Dictionary<string, object>> fieldData, int sequenceNumber)
        {
            this._elmSecurityName = new ElementHistoricString("security", securityName);
            this._elmFieldDataArray = new ElementHistoricFieldDataArray(fieldData);
            this._elmSequenceNumber = new ElementReferenceInt("sequenceNumber", sequenceNumber);
        }

        public override Name Name { get { return new Name("securityData"); } }
        public override int NumValues { get { return 1; } }
        public override int NumElements { get { return 3; } }
        public override bool IsComplexType { get { return true; } }
        public override bool IsArray { get { return false; } }
        public override object this[int index] { get { return null; } }

        public override object this[string name, int index]
        {
            get
            {
                switch (name.ToUpper())
                {
                    case "FIELDDATA":
                        return this._elmFieldDataArray[index];
                    default:
                        if (index == 0)
                            return this[name];
                        break;
                }

                return base[name, index];
            }
        }

        public override Element GetElement(string name)
        {
            switch (name.ToUpper())
            {
                case "FIELDDATA":
                    return this._elmFieldDataArray;
                case "SECURITY":
                    return this._elmSecurityName;
                case "SEQUENCENUMBER":
                    return this._elmSequenceNumber;
            }
            return base.GetElement(name);
        }

        public override string GetElementAsString(string name)
        {
            if (name.ToUpper() == this._elmSecurityName.Name.ToString().ToUpper())
                return (string)this._elmSecurityName.GetValue();
            else
                return base.GetElementAsString(name);
        }

        public override int GetElementAsInt32(string name)
        {
            if (name.ToUpper() == this._elmSequenceNumber.Name.ToString().ToUpper())
                return (int)this._elmSequenceNumber.GetValue();
            else
                return base.GetElementAsInt32(name);
        }

        public override Element this[string name] { get { return this.GetElement(name); } }

        internal override StringBuilder PrettyPrint(int tabIndent)
        {
            string tabs = Types.IndentType.Indent(tabIndent);
            StringBuilder result = new StringBuilder();

            result.AppendFormat("{0}{1} = {{{2}", tabs, this.Name, Environment.NewLine);
            result.Append(this._elmSecurityName.PrettyPrint(tabIndent + 1));
            result.Append(this._elmSequenceNumber.PrettyPrint(tabIndent + 1));
            result.Append(this._elmFieldDataArray.PrettyPrint(tabIndent + 1));
            result.AppendFormat("{0}}}{1}", tabs, Environment.NewLine);

            return result;
        }
    }
}
