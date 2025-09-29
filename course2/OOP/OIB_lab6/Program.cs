using System;

class Program
{
    static void Main(string[] args)
    {
        long a = 5336161097;
        long b = 196210799;
        long primeNumber = 19;

        // Находим каноническое разложение чисел а и b
        Console.WriteLine($"Каноническое разложение числа а:");
        CanonicalFactorization(a);
        Console.WriteLine();

        Console.WriteLine($"Каноническое разложение числа b = {b}:");
        CanonicalFactorization(b);
        Console.WriteLine();

        // Находим НОД с использованием алгоритма Евклида
        long gcdByEuclidean = GCDByEuclidean(a, b);
        Console.WriteLine("НОД с использованием алгоритма Евклида: " + gcdByEuclidean);
        Console.WriteLine();

        // Находим НОД, используя разложение чисел на простые множители
        long gcdByPrimeFactorization = GCDByPrimeFactorization(a, b);
        Console.WriteLine("НОД с использованием разложения чисел на простые множители: " + gcdByPrimeFactorization);
        Console.WriteLine();

        // Находим целые u и v с помощью расширенного алгоритма Евклида
        long u, v;
        ExtendedEuclideanAlgorithm(a, b, out u, out v);
        Console.WriteLine("Целые u и v, удовлетворяющие соотношению Безу: au + bv = НОД");
        Console.WriteLine("u = " + u);
        Console.WriteLine("v = " + v);
        Console.WriteLine();

        // Находим остаток от деления числа 1998 в степени 2001 на 19
        long powerMod = CalculatePowerMod(1998, 2001, primeNumber);
        Console.WriteLine("Остаток от деления 1998^2001 на 19: " + powerMod);
    }

    static void CanonicalFactorization(long number)
    {
        long factor = 2;
        while (number > 1)
        {
            if (number % factor == 0)
            {

                Console.WriteLine($"{number}\t|" + factor + " ");
                number /= factor;
            }
            else
            {
                factor++;
            }
        }
    }

    static long GCDByEuclidean(long a, long b)
    {
        while (b != 0)
        {
            long temp = b;
            b = a % b;
            a = temp;
        }
        return a;
    }

    static long GCDByPrimeFactorization(long a, long b)
    {
        long gcd = 1;
        long factor = 2;
        while (a > 1 && b > 1)
        {
            if (a % factor == 0 && b % factor == 0)
            {
                gcd *= factor;
                a /= factor;
                b /= factor;
            }
            else if (a % factor == 0)
            {
                a /= factor;
            }
            else if (b % factor == 0)
            {
                b /= factor;
            }
            else
            {
                factor++;
            }
        }
        return gcd;
    }

    static void ExtendedEuclideanAlgorithm(long a, long b, out long u, out long v)
    {
        long u1 = 1, u2 = 0, u3 = a;
        long v1 = 0, v2 = 1, v3 = b;

        while (v3 != 0)
        {
            long q = u3 / v3;
            long t1 = u1 - q * v1;
            long t2 = u2 - q * v2;
            long t3 = u3 - q * v3;

            u1 = v1;
            u2 = v2;
            u3 = v3;

            v1 = t1;
            v2 = t2;
            v3 = t3;
        }

        u = u1;
        v = u2;
    }

    static long CalculatePowerMod(long baseNumber, long exponent, long modulus)
    {
        long result = 1;
        while (exponent > 0)
        {
            if (exponent % 2 == 1)
            {
                result = (result * baseNumber) % modulus;
            }
            baseNumber = (baseNumber * baseNumber) % modulus;
            exponent /= 2;
        }
        return result;
    }
}