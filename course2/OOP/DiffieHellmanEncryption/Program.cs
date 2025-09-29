using System.Security.Cryptography;
class Program
{
    static void Main()
    {
        // Создание объектов ECDiffieHellman для Алисы и Боба
        using (ECDiffieHellman alice = ECDiffieHellman.Create())
        using (ECDiffieHellman bob = ECDiffieHellman.Create())
        {
            // Генерация ключей для Алисы и Боба
            byte[] alicePublicKeyBytes = alice.PublicKey.ToByteArray();
            byte[] bobPublicKeyBytes = bob.PublicKey.ToByteArray();

            // Обмен публичными ключами и вычисление общего секрета
            using (ECDiffieHellmanPublicKey alicePublicKey = ECDiffieHellmanCngPublicKey.FromByteArray(alicePublicKeyBytes, CngKeyBlobFormat.EccPublicBlob))
            using (ECDiffieHellmanPublicKey bobPublicKey = ECDiffieHellmanCngPublicKey.FromByteArray(bobPublicKeyBytes, CngKeyBlobFormat.EccPublicBlob))
            {
                byte[] aliceSharedSecret = alice.DeriveKeyMaterial(bobPublicKey);
                byte[] bobSharedSecret = bob.DeriveKeyMaterial(alicePublicKey);

                // Проверка совпадения общих секретов
                bool sharedSecretsMatch = CompareByteArrays(aliceSharedSecret, bobSharedSecret);
                Console.WriteLine("Alice's public key: " + Convert.ToBase64String(alicePublicKeyBytes));
                Console.WriteLine("Bob's public key: " + Convert.ToBase64String(bobPublicKeyBytes));
                Console.WriteLine("Shared secrets match: " + sharedSecretsMatch);
            }
        }
    }
    private static bool CompareByteArrays(byte[] array1, byte[] array2)
    {
        if (array1.Length != array2.Length)
        {
            return false;
        }

        for (int i = 0; i < array1.Length; i++)
        {
            if (array1[i] != array2[i])
            {
                return false;
            }
        }

        return true;
    }
}