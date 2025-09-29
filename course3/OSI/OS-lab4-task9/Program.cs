using System;
using System.Diagnostics;
using System.Diagnostics.CodeAnalysis;
using System.Runtime.CompilerServices;
using System.Threading.Tasks;
class Program
{
    const int TaskCount = 30;
    const int ThreadLifeTime = 10;
    const int ObservationTime = 30;
    static int[,] Matrix = new int[TaskCount, ObservationTime];
    static DateTime StartTime = DateTime.Now;
    static void Work(object o)
    {
        int id = (int)o;
        for (int i = 0; i < ThreadLifeTime * 20; i++)
        {
            DateTime CurrentTime = DateTime.Now;
            int ElapsedSeconds = (int)Math.Round(CurrentTime.Subtract(StartTime).TotalSeconds - 0.49);
            if (ElapsedSeconds >= 0 && ElapsedSeconds < ObservationTime)
            {
                Matrix[id, ElapsedSeconds] += 50;
            }

            MySleep(50); // Из задания 5
        }
    }
    static void Main(string[] args)
    {
        Task[] t = new Task[TaskCount];
        int[] numbers = new int[TaskCount];
        for (int i = 0; i < TaskCount; i++)
            numbers[i] = i;
        Console.WriteLine("A student ... is creating tasks...");
        t[0] = Task.Run(() => { Work(0); });
        t[1] = Task.Run(() => { Work(1); });
        t[2] = Task.Run(() => { Work(2); });
        t[3] = Task.Run(() => { Work(3); });
        t[4] = Task.Run(() => { Work(4); });
        t[5] = Task.Run(() => { Work(5); });
        t[6] = Task.Run(() => { Work(6); });
        t[7] = Task.Run(() => { Work(7); });
        t[8] = Task.Run(() => { Work(8); });
        t[9] = Task.Run(() => { Work(9); });
        t[10] = Task.Run(() => { Work(10); });
        t[11] = Task.Run(() => { Work(11); });
        t[12] = Task.Run(() => { Work(12); });
        t[13] = Task.Run(() => { Work(13); });
        t[14] = Task.Run(() => { Work(14); });
        t[15] = Task.Run(() => { Work(15); });
        t[16] = Task.Run(() => { Work(16); });
        t[17] = Task.Run(() => { Work(17); });
        t[18] = Task.Run(() => { Work(18); });
        t[19] = Task.Run(() => { Work(19); });
        t[20] = Task.Run(() => { Work(20); });
        t[21] = Task.Run(() => { Work(21); });
        t[22] = Task.Run(() => { Work(22); });
        t[23] = Task.Run(() => { Work(23); });
        t[24] = Task.Run(() => { Work(24); });
        t[25] = Task.Run(() => { Work(25); });
        t[26] = Task.Run(() => { Work(26); });
        t[27] = Task.Run(() => { Work(27); });
        t[28] = Task.Run(() => { Work(28); });
        t[29] = Task.Run(() => { Work(29); });


        Console.WriteLine("A student ... is waiting for tasks to finish...");
        Task.WaitAll(t);
        for (int s = 0; s < ObservationTime; s++)
        {
            Console.Write("{0,3}: ", s);
            for (int th = 0; th < TaskCount; th++)
                Console.Write(" {0,5}", Matrix[th, s]);
            Console.WriteLine();
        }
    }

    static Double MySleep(int ms)
    {
        Double Sum = 0, Temp;
        for (int t = 0; t < ms; ++t)
        {
            Temp = 0.711 + (Double)t / 10000.0;
            Double a, b, c, d, e, nt;
            for (int k = 0; k < 5500; ++k)
            {
                nt = Temp - k / 27000.0;
                a = Math.Sin(nt);
                b = Math.Cos(nt);
                c = Math.Cos(nt / 2.0);
                d = Math.Sin(nt / 2);
                e = Math.Abs(1.0 - a * a - b * b) + Math.Abs(1.0 - c * c - d * d);
                Sum += e;
            }
        }
        return Sum;
    }

}
