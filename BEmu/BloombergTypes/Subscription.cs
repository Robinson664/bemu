//------------------------------------------------------------------------------
//  This code comes from Bloomberg.Blpapi.dll
//------------------------------------------------------------------------------

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using System.Text.RegularExpressions;

namespace Bloomberglp.Blpapi
{
    public class Subscription
    {
        #region NOT PART OF DLL
        private readonly string _security;
        internal string Security { get { return this._security; } }

        private readonly List<string> _fields;
        internal List<string> Fields { get { return this._fields; } }

        private static string CheckSecurity(string security)
        {
            if (security.Contains(TOPIC_OPTIONS_SEPARATOR))
                throw new ArgumentNullException(security);
            return security;
        }

        private static string CheckField(string field)
        {
            if (field.Contains(OPTIONS_SEPARATOR))
                throw new ArgumentException(field);
            return field;
        }

        private int? ReadConflationInterval(IList<string> options)
        {
            int? result = null;
            foreach (var item in options)
            {
                if (item.StartsWith("interval="))
                {
                    int temp;
                    string strInterval = item.Substring(item.IndexOf('=') + 1);
                    if (int.TryParse(strInterval, out temp))
                        result = temp;
                }
            }
            return result;
        }

        private readonly int? _conflationInterval;
        internal int? ConflationInterval { get { return this._conflationInterval; } }
        #endregion

        private const char OPTIONS_SEPARATOR = '&';
		private const char TOPIC_OPTIONS_SEPARATOR = '?';
		private const char FIELDS_SEPARATOR = ',';
		private const string FIELDS_OPTION = "fields=";
		private string d_subscriptionString;
		private CorrelationID d_correlationId;
		private Session.SubscriptionStatus d_subscriptionStatus = Session.SubscriptionStatus.UNSUBSCRIBED;
		private bool d_isResolved;
		private static readonly Regex utsReg = new Regex("^//[^/]+/[^/]+/[^?]+([?](.)+)?$", RegexOptions.None);
		private static readonly Regex topicReg = new Regex("^[^?]+([?](.)+)?$", RegexOptions.None);
		public string SubscriptionString
		{
			get
			{
				return this.d_subscriptionString;
			}
			set
			{
				if (value == null)
				{
					throw new ArgumentNullException();
				}
				if (value.Length <= 0)
				{
					throw new ArgumentException("An empty subscription string");
				}
				this.d_subscriptionString = value;
			}
		}
		public CorrelationID CorrelationID
		{
			get
			{
				return this.d_correlationId;
			}
			set
			{
				if (value == null)
				{
					throw new ArgumentNullException();
				}
				this.d_correlationId = value;
			}
		}
		public Session.SubscriptionStatus SubscriptionStatus
		{
			get
			{
				return this.d_subscriptionStatus;
			}
		}
		public bool IsResolved
		{
			get
			{
				return this.d_isResolved;
			}
		}
		internal Subscription(string subscriptionString, CorrelationID correlationID, Session.SubscriptionStatus status)
		{
			this.d_subscriptionString = subscriptionString;
			this.d_correlationId = correlationID;
			this.d_subscriptionStatus = status;
		}
		public Subscription(string subscriptionString) : this(subscriptionString, new CorrelationID())
		{
		}
		public Subscription(string subscriptionString, CorrelationID correlationID) : this(subscriptionString, correlationID, false)
		{
		}
		public Subscription(string subscriptionString, bool isResolved) : this(subscriptionString, new CorrelationID(), isResolved)
		{
		}
		public Subscription(string subscriptionString, CorrelationID correlationID, bool isResolved)
		{
			if (subscriptionString == null || correlationID == null)
			{
				throw new ArgumentNullException();
			}
			if (!Subscription.isValidSubscriptionString(subscriptionString))
			{
				throw new ArgumentException("An empty subscription string");
			}
			this.d_subscriptionString = subscriptionString;
			this.d_correlationId = correlationID;
			this.d_isResolved = isResolved;

            //set security and fields
		}
		public Subscription(string security, string fields) : this(security, fields, "", new CorrelationID())
		{
		}
		public Subscription(string security, string fields, CorrelationID correlationId) : this(security, fields, "", correlationId)
        {
		}
		public Subscription(string security, string fields, string options) : this(security, fields, options, new CorrelationID())
        {
		}
		public Subscription(string security, string fields, string options, CorrelationID correlationID)
		{
            if (security == null || security.Length <= 0 || security.IndexOf(TOPIC_OPTIONS_SEPARATOR) >= 0)
			{
				throw new ArgumentNullException("Invalid security: " + security);
			}
			if (options == null)
			{
				options = "";
			}
			if (fields == null)
			{
				fields = "";
			}
            if (fields.IndexOf(OPTIONS_SEPARATOR) >= 0)
			{
				throw new ArgumentException("Invalid fields: " + fields);
			}
			if (correlationID == null)
			{
				correlationID = new CorrelationID();
			}
			StringBuilder stringBuilder = new StringBuilder(security.Length + fields.Length + options.Length);
			stringBuilder.Append(security);
			bool flag = fields.Length > 0;
			bool flag2 = options.Length > 0;
			if (flag || flag2)
			{
                stringBuilder.Append(TOPIC_OPTIONS_SEPARATOR);
				if (flag)
				{
                    stringBuilder.Append(FIELDS_OPTION);
					stringBuilder.Append(fields);
				}
				if (flag && flag2)
				{
                    stringBuilder.Append(OPTIONS_SEPARATOR);
				}
				if (flag2)
				{
					stringBuilder.Append(options);
				}
			}
			this.d_subscriptionString = stringBuilder.ToString();
			this.d_correlationId = correlationID;



            this._security = security;
            this._fields = new List<string>(fields.Split(FIELDS_SEPARATOR).Select(s => Subscription.CheckField(s)));
            this._conflationInterval = this.ReadConflationInterval(new List<string>(options.Split(FIELDS_SEPARATOR)));
		}
		public Subscription(string security, IList<string> fields) : this(security, fields, null, new CorrelationID())
		{
		}
		public Subscription(string security, IList<string> fields, CorrelationID correlationID) : this(security, fields, null, correlationID)
		{
		}
		public Subscription(string security, IList<string> fields, IList<string> options) : this(security, fields, options, new CorrelationID())
		{
		}
        public Subscription(string security, IList<string> fields, IList<string> options, CorrelationID correlationID)
		{
            if (security == null || security.Length <= 0 || security.IndexOf(TOPIC_OPTIONS_SEPARATOR) >= 0)
			{
				throw new ArgumentNullException("Invalid security: " + security);
			}
			if (correlationID == null)
			{
				throw new ArgumentException("Null argument");
			}
			StringBuilder stringBuilder = new StringBuilder(64);
			stringBuilder.Append(security);
			bool hasFields = fields != null && fields.Count != 0;
			bool hasOptions = options != null && options.Count != 0;
			bool separatorsAppended = false;
			if (hasFields)
			{
				foreach (string current in fields)
				{
					if (current != null && current.Length > 0)
					{
						if (!separatorsAppended)
						{
                            stringBuilder.Append(TOPIC_OPTIONS_SEPARATOR);
                            stringBuilder.Append(FIELDS_OPTION);
							separatorsAppended = true;
						}
						else
						{
                            stringBuilder.Append(FIELDS_SEPARATOR);
						}
						stringBuilder.Append(current);
					}
				}
			}
			if (hasOptions)
			{
				foreach (string current2 in options)
				{
					if (current2 != null && current2.Length > 0)
					{
						if (!separatorsAppended)
						{
                            stringBuilder.Append(TOPIC_OPTIONS_SEPARATOR);
							separatorsAppended = true;
						}
						else
						{
                            stringBuilder.Append(OPTIONS_SEPARATOR);
						}
						stringBuilder.Append(current2);
					}
				}
			}
			this.d_subscriptionString = stringBuilder.ToString();
			this.d_correlationId = correlationID;
            this._security = Subscription.CheckSecurity(security);

            if (fields != null)
                this._fields = new List<string>(fields.Select(s => Subscription.CheckField(s)));

            if (options != null)
                this._conflationInterval = this.ReadConflationInterval(options);
		}
		public override string ToString()
		{
			StringBuilder stringBuilder = new StringBuilder();
			stringBuilder.Append("[");
			stringBuilder.Append(this.d_subscriptionString);
			stringBuilder.Append(" CorrelationID = {");
			stringBuilder.Append(this.d_correlationId.ToString());
			stringBuilder.Append("}");
			stringBuilder.Append(" Status = {");
			stringBuilder.Append(this.d_subscriptionStatus.ToString());
			stringBuilder.Append("}");
			stringBuilder.Append("]");
			return stringBuilder.ToString();
		}
		internal void setSubscriptionStatus(Session.SubscriptionStatus status)
		{
			this.d_subscriptionStatus = status;
		}
		internal static bool isValidSubscriptionString(string subscriptionString)
		{
			if (subscriptionString.StartsWith("//"))
			{
                return Subscription.utsReg.IsMatch(subscriptionString);
			}
            return Subscription.topicReg.IsMatch(subscriptionString);
		}
    }
}
