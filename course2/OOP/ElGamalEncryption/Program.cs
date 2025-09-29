using System;
using System.Security.Cryptography;
using System.Text;
using Org.BouncyCastle.Crypto;
using Org.BouncyCastle.Crypto.Generators;
using Org.BouncyCastle.Crypto.Parameters;
using Org.BouncyCastle.Security;

public class ElGamal
{
    public static void Main()
    {
        // Пример Эль-Гамаля
        Console.WriteLine("ElGamal Example:");

        // Генерация параметров
        ElGamalParametersGenerator generator = new ElGamalParametersGenerator();
        generator.Init(256, 20, new SecureRandom());
        ElGamalParameters parameters = generator.GenerateParameters();

        // Генерация ключей
        ElGamalKeyGenerationParameters keyGenParams = new ElGamalKeyGenerationParameters(new SecureRandom(), parameters);
        ElGamalKeyPairGenerator keyPairGenerator = new ElGamalKeyPairGenerator();
        keyPairGenerator.Init(keyGenParams);
        AsymmetricCipherKeyPair keyPair = keyPairGenerator.GenerateKeyPair();

        ElGamalPublicKeyParameters publicKey = (ElGamalPublicKeyParameters)keyPair.Public;
        ElGamalPrivateKeyParameters privateKey = (ElGamalPrivateKeyParameters)keyPair.Private;

        // Шифрование
        byte[] plaintextBytes = Encoding.UTF8.GetBytes("Hello, ElGamal!");
        byte[] encryptedBytes = ElGamalEncrypt(plaintextBytes, publicKey);

        // Расшифрование
        byte[] decryptedBytes = ElGamalDecrypt(encryptedBytes, privateKey);
        string decryptedText = Encoding.UTF8.GetString(decryptedBytes);

        Console.WriteLine("Original: " + Encoding.UTF8.GetString(plaintextBytes));
        Console.WriteLine("Encrypted: " + Convert.ToBase64String(encryptedBytes));
        Console.WriteLine("Decrypted: " + decryptedText);
    }

    private static byte[] ElGamalEncrypt(byte[] plaintext, ElGamalPublicKeyParameters publicKey)
    {
        IBufferedCipher cipher = CipherUtilities.GetCipher("ElGamal/None/NoPadding");
        cipher.Init(true, publicKey);

        return cipher.DoFinal(plaintext);
    }

    private static byte[] ElGamalDecrypt(byte[] ciphertext, ElGamalPrivateKeyParameters privateKey)
    {
        IBufferedCipher cipher = CipherUtilities.GetCipher("ElGamal/None/NoPadding");
        cipher.Init(false, privateKey);

        return cipher.DoFinal(ciphertext);
    }
}