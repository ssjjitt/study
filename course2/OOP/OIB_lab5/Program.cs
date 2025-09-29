using System;
using System.Security.Cryptography;
using System.Text;

public class RSADigitalSignatureExample
{
    public static void Main()
    {
        try
        {
            // Создание экземпляра класса RSA для генерации ключей
            using (var rsa = new RSACryptoServiceProvider())
            {
                // Генерация открытого и закрытого ключей
                var publicKey = rsa.ExportParameters(false);
                var privateKey = rsa.ExportParameters(true);

                // Сообщение, которое требуется подписать
                var message = "мяу";

                // Получение хеш-значения сообщения
                var hash = GetHash(message); // С использованием алгоритма SHA256

                // Создание подписи
                var signature = CreateSignature(hash, privateKey); // Результатом является подпись, представленная в виде массива байтов.
                // Вывод подписи в шестнадцатеричном формате
                Console.WriteLine("Подпись: " + BitConverter.ToString(signature).Replace("-", ""));
                // Проверка подписи
                //Внутри функции также создается экземпляр RSACryptoServiceProvider и импортируются параметры открытого ключа.
                //Затем вызывается метод VerifyHash(), который проверяет подлинность подписи, 
                //сравнивая ее с хеш-значением сообщения при использовании открытого ключа и определенного алгоритма хеширования и заполнения.
                //Результатом является логическое значение, указывающее, является ли подпись действительной.
                var isValid = VerifySignature(hash, signature, publicKey);

                // Вывод результата проверки подписи
                Console.WriteLine("Проверка подписи: " + (isValid ? "Действительна" : "Недействительна"));
            }
        }
        catch (CryptographicException e)
        {
            Console.WriteLine("Ошибка шифрования: " + e.Message);
        }
    }

    // Функция для получения хеш-значения сообщения
    static byte[] GetHash(string message)
    {
        using (var sha256 = SHA256.Create())
        {
            return sha256.ComputeHash(Encoding.UTF8.GetBytes(message));
        }
    }

    // Функция для создания подписи
    static byte[] CreateSignature(byte[] hash, RSAParameters privateKey)
    {
        using (var rsa = new RSACryptoServiceProvider())
        {
            rsa.ImportParameters(privateKey);
            return rsa.SignHash(hash, HashAlgorithmName.SHA256, RSASignaturePadding.Pkcs1);
        }
    }

    // Функция для проверки подписи
    static bool VerifySignature(byte[] hash, byte[] signature, RSAParameters publicKey)
    {
        using (var rsa = new RSACryptoServiceProvider())
        {
            rsa.ImportParameters(publicKey);
            return rsa.VerifyHash(hash, signature, HashAlgorithmName.SHA256, RSASignaturePadding.Pkcs1);
        }
    }
}