using System;
using System.IO;
using System.Security.Cryptography;
using System.Text;

class Program
{
    static void Main()
    {
        try
        {
            string message = "gluhova daria";

            // Генерация и сохранение секретного ключа
            byte[] key = GenerateDESKey();
            SaveKeyToFile(key, @"E:\уник\c\OIB_lab8\key.txt");
            Console.WriteLine("Секретного ключ: " + Convert.ToBase64String(key));
            
            // Шифрование сообщения
            byte[] encryptedMessage = EncryptWithDES(message, key);
            Console.WriteLine("Зашифрованное сообщение: " + Convert.ToBase64String(encryptedMessage));

            // Вычисление и сохранение хэша
            byte[] hash = CalculateSHA256Hash(message);
            SaveHashToFile(hash, @"E:\уник\c\OIB_lab8\hash.txt");
            // Считывание ключа и хэша из файлов
            byte[] storedKey = ReadKeyFromFile(@"E:\уник\c\OIB_lab8\key.txt");
            byte[] storedHash = ReadHashFromFile(@"E:\уник\c\OIB_lab8\hash.txt");

            // Проверка целостности сообщения и хэша
            bool isMessageValid = VerifyMessageIntegrity(message, storedKey, encryptedMessage);
            bool isHashValid = VerifyHashIntegrity(message, storedHash);

            Console.WriteLine("Валидность сообщения: " + isMessageValid);
            Console.WriteLine("Валидность хэша: " + isHashValid);

            // Симуляция изменения хэша или сообщения
            bool isModifiedHash = true;
            bool isModifiedMessage = true;

            // Проверка целостности сообщения и хэша после модификации
            bool isModifiedMessageValid = VerifyMessageIntegrity(message, storedKey, encryptedMessage);
            bool isModifiedHashValid = VerifyHashIntegrity(message, storedHash);

            Console.WriteLine("Валидность измененного сообщения: " + isModifiedMessageValid);
            Console.WriteLine("Валидность измененного хэша: " + isModifiedHashValid);
        }
        catch (Exception ex)
        {
            Console.WriteLine("Ошибка: " + ex.Message);
        }
    }

    static byte[] GenerateDESKey()
    {
        using (DES des = DES.Create())
        {
            des.GenerateKey();
            return des.Key;
        }
    }

    static void SaveKeyToFile(byte[] key, string filePath)
    {
        File.WriteAllBytes(filePath, key);
        Console.WriteLine("Секретный ключ сохранен в файле: " + filePath);
    }

    static byte[] ReadKeyFromFile(string filePath)
    {
        return File.ReadAllBytes(filePath);
    }

    static byte[] EncryptWithDES(string message, byte[] key)
    {
        using (DES des = DES.Create())
        {
            des.Key = key;
            byte[] messageBytes = Encoding.UTF8.GetBytes(message);

            using (MemoryStream memoryStream = new MemoryStream())
            {
                using (CryptoStream cryptoStream = new CryptoStream(memoryStream, des.CreateEncryptor(), CryptoStreamMode.Write))
                {
                    cryptoStream.Write(messageBytes, 0, messageBytes.Length);
                    cryptoStream.FlushFinalBlock();
                    return memoryStream.ToArray();
                }
            }
        }
    }

    static byte[] CalculateSHA256Hash(string message)
    {
        using (SHA256 sha256 = SHA256.Create())
        {
            byte[] messageBytes = Encoding.UTF8.GetBytes(message);
            return sha256.ComputeHash(messageBytes);
        }
    }

    static void SaveHashToFile(byte[] hash, string filePath)
    {
        File.WriteAllBytes(filePath, hash);
        Console.WriteLine("Хэш сохранен в файле: " + filePath);
    }

    static byte[] ReadHashFromFile(string filePath)
    {
        return File.ReadAllBytes(filePath);
    }

    static bool VerifyMessageIntegrity(string message, byte[] key, byte[] encryptedMessage)
    {
        using (DES des = DES.Create())
        {
            des.Key = key;

            using (MemoryStream memoryStream = new MemoryStream(encryptedMessage))
            {
                using (CryptoStream cryptoStream = new CryptoStream(memoryStream, des.CreateDecryptor(), CryptoStreamMode.Read))
                {
                    using (StreamReader reader = new StreamReader(cryptoStream))
                    {
                        string decryptedMessage = reader.ReadToEnd();
                        return decryptedMessage == message;
                    }
                }
            }
        }
    }

    static bool VerifyHashIntegrity(string message, byte[] storedHash)
    {
        byte[] hash = CalculateSHA256Hash(message);
        return CompareHashes(hash, storedHash);
    }

    static bool CompareHashes(byte[] hash, byte[] storedHash)
    {
        if (hash.Length != storedHash.Length)
            return false;

        for (int i = 0; i < hash.Length; i++)
        {
            if (hash[i] != storedHash[i])
                return false;
        }

        return true;
    }
}