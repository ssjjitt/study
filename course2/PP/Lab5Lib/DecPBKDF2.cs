using Lab5Lib.Class;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Security.Cryptography;
using System.Text;
using System.Threading.Tasks;

namespace Lab5Lib.Class
{
    public class DecPBKDF2 : Decorator
    {
        public DecPBKDF2(IWriter writer) : base(writer) { }

        public override string? Save(string? message)
        {
            byte[] salt = GenerateSalt();
            int iterations = 10000;
            int derivedKeyLength = 32; // 32 bytes = 256 bits

            byte[] derivedKey = DeriveKeyFromPassword(message, salt, iterations, derivedKeyLength);

            string saltBase64 = Convert.ToBase64String(salt);
            string derivedKeyBase64 = Convert.ToBase64String(derivedKey);

            string decoratedMessage = $"{message}{Constant.Delimiter}{saltBase64}{Constant.Delimiter}{iterations}{Constant.Delimiter}{derivedKeyBase64}";

            return _writer?.Save(decoratedMessage);
        }

        private byte[] GenerateSalt()
        {
            byte[] salt = new byte[16]; // 16 bytes = 128 bits
            using (var rng = new RNGCryptoServiceProvider())
            {
                rng.GetBytes(salt);
            }
            return salt;
        }

        public byte[] DeriveKeyFromPassword(string password, byte[] salt, int iterations, int derivedKeyLength)
        {
            using (var pbkdf2 = new Rfc2898DeriveBytes(password, salt, iterations))
            {
                return pbkdf2.GetBytes(derivedKeyLength);
            }
        }
    }
}
