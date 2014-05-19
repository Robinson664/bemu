//------------------------------------------------------------------------------
// <copyright project="BEmu_csh" file="BloombergTypes/ConstraintsList.cs" company="Jordan Robinson">
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

    public class ConstraintsList : IDictionary<string, Constraint>, ICollection<KeyValuePair<string, Constraint>>, IEnumerable<KeyValuePair<string, Constraint>>, IEnumerable
    {
        private ConstraintsList() { }

        public void Add(string key, Constraint value)
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

        public bool TryGetValue(string key, out Constraint value)
        {
            throw new NotImplementedException();
        }

        public ICollection<Constraint> Values
        {
            get { throw new NotImplementedException(); }
        }

        public Constraint this[string key]
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

        public void Add(KeyValuePair<string, Constraint> item)
        {
            throw new NotImplementedException();
        }

        public void Clear()
        {
            throw new NotImplementedException();
        }

        public bool Contains(KeyValuePair<string, Constraint> item)
        {
            throw new NotImplementedException();
        }

        public void CopyTo(KeyValuePair<string, Constraint>[] array, int arrayIndex)
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

        public bool Remove(KeyValuePair<string, Constraint> item)
        {
            throw new NotImplementedException();
        }

        public IEnumerator<KeyValuePair<string, Constraint>> GetEnumerator()
        {
            throw new NotImplementedException();
        }

        IEnumerator IEnumerable.GetEnumerator()
        {
            throw new NotImplementedException();
        }
    }
}