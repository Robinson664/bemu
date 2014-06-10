//------------------------------------------------------------------------------
//  This code comes from Bloomberg.Blpapi.dll
//------------------------------------------------------------------------------

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using System.Collections;
using System.Threading;

namespace Bloomberglp.Blpapi
{
    public class Name
    {
        private static Hashtable s_globalNameTable = new Hashtable();
		private static readonly object s_globalNameTableLock = new object();
		private static Random d_hashGenerator = new Random();
		private string d_name;
		private Name d_impl;
		private int d_hash;
		public static Name NullName = new Name(0);

		public Name()
		{
			this.d_name = Name.NullName.d_name;
			this.d_impl = Name.NullName.d_impl;
			this.d_hash = Name.NullName.d_hash;
		}
		private Name(int zero)
		{
			this.d_name = null;
			this.d_impl = this;
			this.d_hash = Name.d_hashGenerator.Next();
		}
		public Name(string nameString)
        {
            Name name = Name.GetName(nameString);
            this.d_impl = name;
            this.d_name = this.d_impl.d_name;
            this.d_hash = this.d_impl.d_hash;
		}
        private Name(string nameString, bool unUsed)
		{
			this.d_name = nameString;
			this.d_impl = this;
            Name.s_globalNameTable[nameString] = this;
            this.d_hash = Name.d_hashGenerator.Next();
		}
        public static Name GetName(string nameString)
		{
			if (nameString == null)
			{
                return Name.NullName;
			}
			object obj;
            Monitor.Enter(obj = Name.s_globalNameTableLock);
			Name result;
			try
			{
                Name name = (Name)Name.s_globalNameTable[nameString];
				if (name == null)
				{
                    name = new Name(nameString, true);
				}
				result = name;
			}
			finally
			{
				Monitor.Exit(obj);
			}
			return result;
		}
        public static Name FindName(string nameString)
		{
			if (nameString == null)
			{
                return Name.NullName;
			}
			object obj;
            Monitor.Enter(obj = Name.s_globalNameTableLock);
            Name result;
			try
			{
                result = (Name)Name.s_globalNameTable[nameString];
			}
			finally
			{
				Monitor.Exit(obj);
			}
			return result;
		}
		public static bool HasName(string nameString)
		{
			if (nameString == null)
			{
				return true;
			}
			object obj;
            Monitor.Enter(obj = Name.s_globalNameTableLock);
			bool result;
			try
			{
                result = Name.s_globalNameTable.ContainsKey(nameString);
			}
			finally
			{
				Monitor.Exit(obj);
			}
			return result;
		}
		public override bool Equals(object other)
		{
			if (other is string)
			{
				return this.d_name.Equals(other);
			}
            return other is Name && ((Name)other).d_impl == this.d_impl;
		}
		public override int GetHashCode()
		{
			return this.d_hash;
		}
		public override string ToString()
		{
			return this.d_name;
		}
		public static void FreeGlobalNameTable()
		{
			object obj;
            Monitor.Enter(obj = Name.s_globalNameTableLock);
			try
			{
                Name.s_globalNameTable.Clear();
			}
			finally
			{
				Monitor.Exit(obj);
			}
		}
    }
}
