using System;
using System.Data.SqlTypes;
using Microsoft.SqlServer.Server;
using System.IO;

namespace PhoneNumLogger
{
    [Serializable]
    [SqlUserDefinedType(Format.UserDefined, IsByteOrdered = true, MaxByteSize = 8000)]
    public struct PhoneNumber : IBinarySerialize, INullable
    {
        private string number;
        private bool isNull;

        public bool IsNull => isNull;

        public static PhoneNumber Null => new PhoneNumber { isNull = true };

        public string Number
        {
            get { return number; }
            set { number = value; }
        }

        public void Read(BinaryReader r)
        {
            if (r != null)
            {
                number = r.ReadString();
            }
        }

        public void Write(BinaryWriter w)
        {
            if (w != null)
            {
                w.Write(number);
            }
        }

        public override string ToString()
        {
            return isNull ? "NULL" : number;
        }

        public static PhoneNumber Parse(SqlString s)
        {
            if (s.IsNull)
                return Null;

            var phoneNumber = new PhoneNumber();
            phoneNumber.Number = s.Value;
            return phoneNumber;
        }
    }
}