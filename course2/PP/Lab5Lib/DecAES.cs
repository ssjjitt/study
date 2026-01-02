using Lab5Lib.Class;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Security.Cryptography;
using System.Text;
using System.Threading.Tasks;

namespace Lab5Lib
{
    public class DecAES : Decorator
    {
        public DecAES(IWriter writer) : base(writer) { }

        public override string? Save(string? message)
        {
            using (Aes aes = Aes.Create())
            {
                aes.GenerateKey();
                aes.GenerateIV();

                byte[] encryptedData;

                using (ICryptoTransform encryptor = aes.CreateEncryptor())
                {
                    byte[] dataBytes = Encoding.UTF8.GetBytes(message ?? string.Empty);
                    encryptedData = encryptor.TransformFinalBlock(dataBytes, 0, dataBytes.Length);
                }

                string encryptedMessage = Convert.ToBase64String(encryptedData);
                string key = Convert.ToBase64String(aes.Key);
                string iv = Convert.ToBase64String(aes.IV);

                string decoratedMessage = $"{message}{Constant.Delimiter}{encryptedMessage}{Constant.Delimiter}{key}{Constant.Delimiter}{iv}";

                return _writer?.Save(decoratedMessage);
            }
        }
    }
}
