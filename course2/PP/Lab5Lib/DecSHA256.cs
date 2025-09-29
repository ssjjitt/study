using System;
using System.Collections.Generic;
using System.Linq;
using System.Security.Cryptography;
using System.Text;
using System.Threading.Tasks;

namespace Lab5Lib.Class
{
    public class DecSHA256 : Decorator
    {
        public DecSHA256(IWriter writer) : base(writer) { }

        public override string? Save(string? message)
        {
            using (var sha256 = SHA256.Create())
            {
                var dataBytes = Encoding.UTF8.GetBytes(message ?? string.Empty);
                var hashedData = sha256.ComputeHash(dataBytes);
                var hashedMessage = Convert.ToBase64String(hashedData);
                var decoratedMessage = $"{message}{Constant.Delimiter}{hashedMessage}";
                return _writer?.Save(decoratedMessage);
            }
        }
    }
}
