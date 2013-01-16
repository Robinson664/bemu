using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace BEmu
{
    public class Name
    {
        private string _name { get; set; }

        public Name(string nameString)
        {
            this._name = nameString;
        }

        public override string ToString()
        {
            return this._name;
        }

        public override bool Equals(object obj)
        {
            return obj.ToString() == this._name;
        }

        public override int GetHashCode()
        {
            return this._name.GetHashCode();
        }

    }
}
