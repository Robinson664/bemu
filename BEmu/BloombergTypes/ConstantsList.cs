//------------------------------------------------------------------------------
// <copyright project="BEmu_csh" file="BloombergTypes/ConstantsList.cs" company="Jordan Robinson">
//     Copyright (c) 2013 Jordan Robinson. All rights reserved.
//
//     The use of this software is governed by the Microsoft Public License
//     which is included with this distribution.
// </copyright>
//------------------------------------------------------------------------------

namespace Bloomberglp.Blpapi
{
    using System;
    using System.Collections;
    using System.Collections.Generic;
    using System.Linq;
    using System.Text;
    using System.IO;

    public class ConstantsList : IDictionary<string, Constant>, ICollection<KeyValuePair<string, Constant>>, IEnumerable<KeyValuePair<string, Constant>>, IEnumerable
    {
        private ConstantsList() { }

        public Schema.Datatype Datatype { get { throw new NotImplementedException(); } }
        public string Description { get { throw new NotImplementedException(); } }
        public Name Name { get { throw new NotImplementedException(); } }
        public Schema.Status Status { get { throw new NotImplementedException(); } }
        
        public object UserData
        {
            get { throw new NotImplementedException(); }
            set { throw new NotImplementedException(); }
        }

        public Constant this[Name name] { get { throw new NotImplementedException(); } }

        public bool ContainsKey(Name key)
        {
            throw new NotImplementedException();
        }

        public void Print(Stream output)
        {
            throw new NotImplementedException();
        }

        public void Print(TextWriter writer)
        {
            throw new NotImplementedException();
        }

        public bool TryGetValue(Name key, out Constant constant)
        {
            throw new NotImplementedException();
        }

        public void Add(string key, Constant value)
        {
            throw new NotImplementedException();
        }

        public bool ContainsKey(string key)
        {
            throw new NotImplementedException();
        }

        public ICollection<string> Keys
        {
            get { throw new NotImplementedException(); }
        }

        public bool Remove(string key)
        {
            throw new NotImplementedException();
        }

        public bool TryGetValue(string key, out Constant value)
        {
            throw new NotImplementedException();
        }

        public ICollection<Constant> Values
        {
            get { throw new NotImplementedException(); }
        }

        public Constant this[string key]
        {
            get
            {
                throw new NotImplementedException();
            }
            set
            {
                throw new NotImplementedException();
            }
        }

        public void Add(KeyValuePair<string, Constant> item)
        {
            throw new NotImplementedException();
        }

        public void Clear()
        {
            throw new NotImplementedException();
        }

        public bool Contains(KeyValuePair<string, Constant> item)
        {
            throw new NotImplementedException();
        }

        public void CopyTo(KeyValuePair<string, Constant>[] array, int arrayIndex)
        {
            throw new NotImplementedException();
        }

        public int Count
        {
            get { throw new NotImplementedException(); }
        }

        public bool IsReadOnly
        {
            get { throw new NotImplementedException(); }
        }

        public bool Remove(KeyValuePair<string, Constant> item)
        {
            throw new NotImplementedException();
        }

        public IEnumerator<KeyValuePair<string, Constant>> GetEnumerator()
        {
            throw new NotImplementedException();
        }

        IEnumerator IEnumerable.GetEnumerator()
        {
            throw new NotImplementedException();
        }
    }
}
