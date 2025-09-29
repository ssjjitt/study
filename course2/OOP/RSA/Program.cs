//using System;
//using System.Numerics;
//using System.Security.Cryptography;
//using System.Text;

//public class RSA
//{
//    private BigInteger p; // простое число p
//    private BigInteger q; // простое число q
//    private BigInteger n; // модуль n = p * q
//    private BigInteger phi; // функция Эйлера от n
//    private BigInteger e; // открытая экспонента
//    private BigInteger d; // секретная экспонента

//    public RSA(int bitLength)
//    {
//        GenerateKeys(bitLength);
//    }

//    public BigInteger Encrypt(BigInteger message)
//    {
//        return BigInteger.ModPow(message, e, n);
//    }

//    public BigInteger Decrypt(BigInteger encryptedMessage)
//    {
//        return BigInteger.ModPow(encryptedMessage, d, n);
//    }

//    private void GenerateKeys(int bitLength)
//    {
//        // Генерируем два простых числа p и q заданной длины
//        p = 3557; // можно использовать GeneratePrimeNumber(bitLength / 2);
//        q = 2579; // GeneratePrimeNumber(bitLength / 2);

//        // Вычисляем модуль n = p * q
//        n = BigInteger.Multiply(p, q);

//        // Вычисляем функцию Эйлера от n
//        phi = BigInteger.Multiply(p - 1, q - 1);

//        // Выбираем открытую экспоненту e (обычно выбирается простое число, которое не делит phi)
//        e = 3; // Часто используется стандартное значение 65537

//        // Вычисляем секретную экспоненту d (обратное значение e по модулю phi)
//        d = ModInverse(e, phi);
//    }

//    private BigInteger GeneratePrimeNumber(int bitLength)
//    {
//        Random rand = new Random();
//        BigInteger prime;
//        do
//        {
//            prime = GenerateRandomBigInteger(bitLength, rand);
//        } while (!IsPrime(prime));
//        return prime;
//    }

//    private BigInteger GenerateRandomBigInteger(int bitLength, Random rand)
//    {
//        byte[] bytes = new byte[bitLength / 8];
//        rand.NextBytes(bytes);
//        bytes[bytes.Length - 1] &= 0x7F; // Устанавливаем старший бит в 0, чтобы получить положительное число
//        return new BigInteger(bytes);
//    }

//    private bool IsPrime(BigInteger number)
//    {
//        // проверка работает всегда, когда-нибудь дополню(вряд ли)
//        return true;
//    }

//    private BigInteger ModInverse(BigInteger a, BigInteger m)
//    {
//        BigInteger m0 = m;
//        BigInteger y = 0, x = 1;

//        if (m == 1)
//            return 0;
//        while (a > 1)
//        {
//            BigInteger q = a / m;
//            BigInteger t = m;
//            m = a % m;
//            a = t;
//            t = y;
//            y = x - q * y;
//            x = t;
//        }
//        if (x < 0)
//            x += m0;
//        return x;
//    }
//}
//public class Program
//{
//    static void Main()
//    {
//        Console.WriteLine("RSA: ");

//        BigInteger message = 111111;
//        RSA rsa = new RSA(1024);
//        BigInteger encryptedMessage = rsa.Encrypt(message);
//        BigInteger decryptedMessage = rsa.Decrypt(encryptedMessage);

//        Console.WriteLine("Сообщение: " + message);
//        Console.WriteLine("Зашифрованное сообщение: " + encryptedMessage);
//        Console.WriteLine("Расшифрованное сообщение: " + decryptedMessage);
//    }
//}

using System;
using System.Security.Cryptography;
using System.Text;
using Org.BouncyCastle.Crypto;
using Org.BouncyCastle.Crypto.Parameters;
using Org.BouncyCastle.Security;

public class RSA
{
    public static void Main()
    {
        // Пример RSA
        Console.WriteLine("RSA Example:");
        RSACryptoServiceProvider rsa = new RSACryptoServiceProvider();
        string rsaPlainText = "Hello, RSA!";
        byte[] rsaPlaintextBytes = Encoding.UTF8.GetBytes(rsaPlainText);

        // Шифрование
        byte[] rsaCiphertextBytes = rsa.Encrypt(rsaPlaintextBytes, true);
        string rsaCiphertextText = Convert.ToBase64String(rsaCiphertextBytes);

        // Расшифрование
        byte[] rsaDecryptedBytes = rsa.Decrypt(rsaCiphertextBytes, true);
        string rsaDecryptedText = Encoding.UTF8.GetString(rsaDecryptedBytes);

        Console.WriteLine("Original: " + rsaPlainText);
        Console.WriteLine("Ciphertext: " + rsaCiphertextText);
        Console.WriteLine("Decrypted: " + rsaDecryptedText);
    }
}