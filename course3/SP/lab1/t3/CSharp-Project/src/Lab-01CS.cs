using System;

class Program
{
    static void Main()
    {
        Console.Write("enter x: ");
        if (int.TryParse(Console.ReadLine(), out int x))
        {
            if (x < 100)
            {
                Console.WriteLine("error");
                return;
            }
            int k = (x / 100) % 10;
            Console.WriteLine($"third num: {k}");
        }
        else
        {
            Console.WriteLine("error");
        }
    }
}