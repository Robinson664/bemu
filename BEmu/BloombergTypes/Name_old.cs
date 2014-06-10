//------------------------------------------------------------------------------
// <copyright project="BEmu_csh" file="BloombergTypes/Name.cs" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

//This is my own implementation of Name

//namespace Bloomberglp.Blpapi
//{
//    using System;
//    using System.Collections.Generic;
//    using System.Linq;
//    using System.Text;

//    public class Name
//    {
//        private readonly bool _isNull;
//        private readonly string _name;
//        private readonly static Dictionary<string, Name> _globalNameTable = new Dictionary<string, Name>();
        
//        //Note that as implemented in the actual BB API, a user *can* overwrite Name.NullName.
//        //  They should have made Name.NullName a static property with a private setter.
//        public static Name NullName = new Name();

//        public Name()
//        {
//            this._name = null;
//            this._isNull = true;
//        }

//        public Name(string nameString)
//        {
//            if (nameString == null)
//                throw new ArgumentNullException("nameString");

//            this._name = nameString;
//            this._isNull = false;

//            Name existing;
//            if (!Name._globalNameTable.TryGetValue(nameString, out existing))
//                Name._globalNameTable.Add(nameString, this);
//        }

//        /// <summary>
//        /// Finds the Name in the Global Name Table and returns it or  returns null if the Name doesn't exist.
//        /// </summary>
//        /// <param name="name"></param>
//        /// <returns>The Name if it already exists, or null otherwise</returns>
//        public static Name FindName(string nameString)
//        {
//            Name result;
//            if (Name._globalNameTable.TryGetValue(nameString, out result))
//                return result;
//            else
//                return null;
//        }

//        /// <summary>
//        /// Finds the Name in the Global Name Table, and returns it.
//        /// Creates a new Name in the Global Name Table if the Name doesn't always exist.
//        /// This works almost the same as the string contructor if the Name doesn't already exist (the hashcodes will be different)
//        /// </summary>
//        /// <param name="nameString"></param>
//        /// <returns>The Name</returns>
//        public static Name GetName(string nameString)
//        {
//            Name result;
//            if (!Name._globalNameTable.TryGetValue(nameString, out result))
//                result = new Name(nameString); //adds the Name to the Global Name Table
//            return result;
//        }

//        public static bool HasName(string nameString)
//        {
//            return Name._globalNameTable.ContainsKey(nameString);
//        }

//        public static void FreeGlobalNameTable()
//        {
//            Name._globalNameTable.Clear();
//        }

//        public override string ToString()
//        {
//            return this._name;
//        }

//        public override bool Equals(object obj)
//        {
//            return obj.ToString() == this._name;
//        }

//        // name.GetHashCode() != name.ToString().GetHashCode()
//        public override int GetHashCode()
//        {
//            if (this._isNull)
//                throw new NullReferenceException();
//            else
//                return base.GetHashCode();
//        }

//    }
//}
