using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace OS_lab4_task5
{
    class Program
    {
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

        static void Main(string[] args)
        {
            Console.WriteLine("Запуск MySleep на 10 секунд...");
            MySleep(10000);
            Console.WriteLine("Завершено.");
        }
    }
}
