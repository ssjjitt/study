using System;
using System.Data;
using System.Data.SqlClient;
using System.Data.SqlTypes;
using System.IO;
using Microsoft.SqlServer.Server;

namespace PhoneNumLogger
{
    public class PhoneNumberLogger
    {
        [SqlProcedure]
        public static void LogPhoneNumber(PhoneNumber phoneNumber)
        {
            if (phoneNumber.IsNull)
                throw new ArgumentNullException("phoneNumber");

            string path = @"D:\PhoneNumbers.txt"; 
            using (StreamWriter writer = new StreamWriter(path, true))
            {
                writer.WriteLine(phoneNumber.ToString());
            }
        }
    }
}
