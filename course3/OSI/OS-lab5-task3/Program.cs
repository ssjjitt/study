using System.Diagnostics;

class Program
{
    const int ThreadCount = 10;
    const int ThreadLifeTime = 10;
    const int ObservationTime = 30;
    static int[,] Matrix = new int[ThreadCount, ObservationTime];
    static DateTime StartTime = DateTime.Now;

    static void WorkThread(object o)
    {
        int id = (int)o;

        for (int i = 0; i < ThreadLifeTime * 20; i++)
        {
            DateTime CurrentTime = DateTime.Now;

            int ElapsedSeconds = (int)Math.Floor(CurrentTime.Subtract(StartTime).TotalSeconds);

            if (ElapsedSeconds >= 0 && ElapsedSeconds < ObservationTime)
            {
                Matrix[id, ElapsedSeconds] += 500;
            }

            MySleep(500);
        }
    }

    static void Main(string[] args)
    {
        Process.GetCurrentProcess().ProcessorAffinity = (System.IntPtr)15;
        Thread[] t = new Thread[ThreadCount];

        for (int i = 0; i < ThreadCount; ++i)
        {
            object o = i;
            t[i] = new Thread(WorkThread);
            if (i < 6) // здесь 2 - половина логических процессоров
                t[i].Priority = ThreadPriority.Lowest;
            else
                t[i].Priority = ThreadPriority.Highest;
            t[i].Start(o);
        }

        Console.WriteLine("A student ... is waiting for the threads to finish");

        for (int i = 0; i < ThreadCount; ++i)
            t[i].Join();

        for (int s = 0; s < ObservationTime; s++)
        {
            Console.Write("{0,3}: ", s);
            for (int th = 0; th < ThreadCount; th++)
            {
                Console.Write(" {0,5}", Matrix[th, s]);
            }
            Console.WriteLine();
        }
    }

    static double MySleep(int ms)
    {
        double sum = 0, Temp;

        for (int t = 0; t < ms; ++t)
        {
            Temp = 0.711 + (double)t / 10000.0;
            double a, b, c, d, e, nt;
            for (int k = 0; k < 5500; ++k)
            {
                nt = Temp - k / 27000.0;
                a = Math.Sin(nt);
                b = Math.Cos(nt);
                c = Math.Cos(nt / 2.0);
                d = Math.Sin(nt / 2);
                e = Math.Abs(1.0 - a * a - b * b) + Math.Abs(1.0 - c * c - d * d);
                sum += e;
            }
        }
        return sum;
    }
}