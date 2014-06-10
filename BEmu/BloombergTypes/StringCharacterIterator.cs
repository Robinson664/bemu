//------------------------------------------------------------------------------
//  This code comes from Bloomberg.Blpapi.dll
//------------------------------------------------------------------------------

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Bloomberglp.Blpapi
{
    internal class StringCharacterIterator
    {
        public const char DONE = '￿';
        private string d_text;
        private int d_begin;
        private int d_end;
        private int d_pos;
        public StringCharacterIterator(string text)
            : this(text, 0, text.Length, 0)
        {
        }
        public StringCharacterIterator(string text, int begin, int end, int pos)
        {
            this.d_text = text;
            if (begin < 0)
            {
                this.d_begin = 0;
            }
            else
            {
                this.d_begin = begin;
            }
            if (this.d_end > text.Length)
            {
                this.d_end = text.Length;
            }
            else
            {
                this.d_end = end;
            }
            this.d_pos = pos;
        }
        public char current()
        {
            if (this.d_pos < this.d_begin || this.d_pos >= this.d_end)
            {
                return '￿';
            }
            return this.d_text[this.d_pos];
        }
        public char next()
        {
            this.d_pos++;
            return this.current();
        }
        public char previous()
        {
            this.d_pos--;
            return this.current();
        }
    }
}
