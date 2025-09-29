using System;
using System.Diagnostics;
using System.Reflection;
using System.Timers;

namespace OOP_lab14
{
    class Program
    {
        static ManualResetEvent pauseEvent = new ManualResetEvent(true);
        static object lockObject = new object();
        static bool isEvenPrinted = false;
        static bool isOddPrinted = true;
        static void Main()
        {
            // 1 
            var allProcesses = Process.GetProcesses();
            foreach (var process in allProcesses)
            {
                Console.WriteLine("id: " + process.Id);
                Console.WriteLine("имя: " + process.ProcessName);
                Console.WriteLine("приоритет: " + process.BasePriority);
                Console.WriteLine("текущее состояние: " + process.Responding);
                Console.WriteLine("выделенная виртуальная память: " + process.VirtualMemorySize64);
                Console.WriteLine();
            }
            Console.WriteLine();

            // 2
            AppDomain currentDomain = AppDomain.CurrentDomain;
            Console.WriteLine("Текущий домен:");
            Console.WriteLine("Имя: " + currentDomain.FriendlyName);
            Console.WriteLine("Базовый каталог приложения: " + currentDomain.BaseDirectory);
            Console.WriteLine("Настройка копирования файлов: " + currentDomain.ShadowCopyFiles);
            Console.WriteLine("Сборки загруженные в домен:");
            foreach (Assembly assembly in currentDomain.GetAssemblies())
            {
                Console.WriteLine(assembly.FullName);
            }
            Console.WriteLine();
            /* AppDomain newD = AppDomain.CreateDomain("newD");
            string assemblyPath = "OOP_lab14.dll";
            newD.Load(assemblyPath);
            AppDomain.Unload(newD); методы устарелі */

            // 5
            System.Timers.Timer timer = new System.Timers.Timer(1000);
            timer.Elapsed += TimerElapsed;
            timer.AutoReset = true;
            timer.Start();
            Console.WriteLine("Нажмите Enter для остановки таймера.");
            Console.ReadLine();
            timer.Stop();
            Console.WriteLine("Таймер остановлен.");

            // 3
            Console.WriteLine("Введите число n:");
            int n = int.Parse(Console.ReadLine());
            Thread calculationThread = new Thread(() => CalculateAndWritePrimes(n)); // новый поток и передачаs задачи в виде делегата
            calculationThread.Name = "CalculationThread";
            calculationThread.Priority = ThreadPriority.Normal;
            calculationThread.Start(); // Запуск потока
            Console.WriteLine("Имя: " + calculationThread.Name);
            Console.WriteLine("Приоритет: " + calculationThread.Priority);
            Console.WriteLine("ID: " + calculationThread.ManagedThreadId);
            Console.WriteLine("Статус: " + calculationThread.ThreadState);
            Thread.Sleep(3000); // стоп на 3 сек
            PauseThread();
            Console.WriteLine("Поток приостановлен.");
            Thread.Sleep(3000);
            ResumeThread(); // возобновление
            calculationThread.Join(); // ожидание завершения
            Console.WriteLine("Работа потока завершена.");

            // 4
            using (StreamWriter writer = new StreamWriter("numbers.txt"))
            {
                Console.WriteLine("Введите число n:");
                int n1 = int.Parse(Console.ReadLine());
                Thread evenThread = new Thread(() => PrintEvenNumbers(n1, writer));
                evenThread.Name = "EvenThread";
                evenThread.Priority = ThreadPriority.Normal;
                Thread oddThread = new Thread(() => PrintOddNumbers(n1, writer));
                oddThread.Name = "OddThread";
                oddThread.Priority = ThreadPriority.AboveNormal;
                evenThread.Start();
                oddThread.Start();
                evenThread.Join();
                oddThread.Join();
                Console.WriteLine("Работа потоков завершена.");
            }
        }

        // 3
        static void CalculateAndWritePrimes(int n)
        {
            string fileName = "../../../primes.txt";
            using (StreamWriter writer = new StreamWriter(fileName))
            {
                for (int i = 1; i <= n; i++)
                {
                    if (IsPrime(i))
                    {
                        Console.WriteLine(i);
                        writer.WriteLine(i);
                    }
                    Thread.Sleep(1000);
                    pauseEvent.WaitOne();// стоп если событие сброшено
                }
            }
        }
        static bool IsPrime(int number)
        {
            if (number < 2)
                return false;
            for (int i = 2; i <= Math.Sqrt(number); i++)
            {
                if (number % i == 0)
                    return false;
            }
            return true;
        }
        static void PauseThread()
        {
            pauseEvent.Reset();
        }
        static void ResumeThread()
        {
            pauseEvent.Set();
        }

        // 4
        static void PrintEvenNumbers(int n, StreamWriter writer)
        {
            lock (lockObject)
            {
                for (int i = 2; i <= n; i += 2)
                {
                    while (!isOddPrinted)
                    {
                        Monitor.Wait(lockObject);
                    }

                    Console.WriteLine("Четное: " + i);
                    writer.WriteLine("Четное: " + i);

                    isEvenPrinted = true;
                    isOddPrinted = false;

                    Monitor.PulseAll(lockObject);
                }
            }
        }

        static void PrintOddNumbers(int n, StreamWriter writer)
        {
            lock (lockObject)
            {
                for (int i = 1; i <= n; i += 2)
                {
                    while (!isEvenPrinted)
                    {
                        Monitor.Wait(lockObject);
                    }

                    Console.WriteLine("Нечетное: " + i);
                    writer.WriteLine("Нечетное: " + i);

                    isEvenPrinted = false;
                    isOddPrinted = true;

                    Monitor.PulseAll(lockObject);
                }
            }
        }

        // 5
        static void TimerElapsed(object sender, ElapsedEventArgs e)
        {
            Console.WriteLine("пiмпiм...");
        }
    }
}