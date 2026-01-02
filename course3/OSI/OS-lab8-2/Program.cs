using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Threading;
using System.Threading.Tasks;

class Program
{
    static void Main(string[] args)
    {
        List<Big> bigObjects = new List<Big>();

        while (true)
        {
            // объект размером 128 МБ
            Big bigObject = new Big();
            bigObjects.Add(bigObject);

            Task.Run(() => bigObject.FillArray());

            // получаем объем используемой памяти
            long memoryUsed = GC.GetTotalMemory(true);
            Console.WriteLine("Используется {0} MB", (memoryUsed / (1024 * 1024)));

            Thread.Sleep(5000);
        }
    }
}

class Big
{
    public Int32[] IntArray;

    public Big()
    {
        // 128 МБ
        IntArray = new int[128 * 1024 * 1024 / sizeof(int)];
    }

    public void FillArray()
    {
        Random rand = new Random();
        for (int i = 0; i < IntArray.Length; i++)
        {
            IntArray[i] = rand.Next();
        }
    }
}

