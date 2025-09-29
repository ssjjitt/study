using System;
using System.Diagnostics;
using System.Diagnostics.CodeAnalysis;
using System.Runtime.CompilerServices;
using System.Threading.Tasks;
class Program
{
    const int TaskCount = 16;
    const int ThreadLifeTime = 30;
    const int ObservationTime = 30;
    static int[,] Matrix = new int[TaskCount, ObservationTime];
    static DateTime StartTime = DateTime.Now;

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
        t[0] = new Task(() => { Work(0); });
        t[0].Start();
        t[1] = t[0].ContinueWith(delegate { Work(1); });
        t[2] = new Task(() => { Work(2); });
        t[2].Start();
        t[3] = t[1].ContinueWith(delegate { Work(3); });
        t[4] = new Task(() => { Work(4); });
        t[4].Start();
        t[5] = t[3].ContinueWith(delegate { Work(5); });
        t[6] = new Task(() => { Work(6); });
        t[6].Start();
        t[7] = t[5].ContinueWith(delegate { Work(7); });
        t[8] = new Task(() => { Work(8); });
        t[8].Start();
        t[9] = t[7].ContinueWith(delegate { Work(9); });
        t[10] = new Task(() => { Work(10); });
        t[10].Start();
        t[11] = t[9].ContinueWith(delegate { Work(11); });
        t[12] = new Task(() => { Work(12); });
        t[12].Start();
        t[13] = t[11].ContinueWith(delegate { Work(13); });
        t[14] = new Task(() => { Work(14); });
        t[14].Start();
        t[15] = t[13].ContinueWith(delegate { Work(15); });

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

}
