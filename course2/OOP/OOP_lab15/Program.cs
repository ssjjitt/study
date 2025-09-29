using System;
using System.Collections.Concurrent;
using System.Diagnostics;

namespace OOP_lab15
{
    class Program {
        private static BlockingCollection<string> warehouse = new BlockingCollection<string>();
        static void Main(string[] args)
        {
            // 1 - задачи последовательно одна за одной
            Console.WriteLine("---------------1---------------");
            Task<double[]> multiplicationTask = Task.Run(() => MultiplyVectorByScalar(CreateVector(100000), 2.5));
            Console.WriteLine("id: " + multiplicationTask.Id);
            Console.WriteLine("статус задачи: " + multiplicationTask.Status);
            double[] result = multiplicationTask.Result;
            Console.WriteLine("результат(3 из 10000):");
            for (int i = 0; i < result.Length * 0.00003; i++)
            {
                Console.WriteLine(result[i]);
            }
            Stopwatch stopwatch = Stopwatch.StartNew(); // оценка производительности
            for (int i = 0; i < 10; i++)
            {
                multiplicationTask = Task.Run(() => MultiplyVectorByScalar(CreateVector(100000), 2.5));
                multiplicationTask.Wait();
            }
            stopwatch.Stop();
            Console.WriteLine("среднее время выполнения: " + stopwatch.Elapsed.TotalMilliseconds / 10 + " ms");
            // 2 - параллельно
            Console.WriteLine("---------------2---------------");
            CancellationTokenSource cancellationTokenSource = new CancellationTokenSource();
            CancellationToken cancellationToken = cancellationTokenSource.Token;
            Task<double[]> multiplicationTask2 = Task.Run(() => MultiplyVectorByScalar(CreateVector(100000), 2.5, cancellationToken));
            Console.WriteLine("id: " + multiplicationTask2.Id);
            Console.WriteLine("статус задачи: " + multiplicationTask2.Status);
            try
            {
                double[] result2 = multiplicationTask2.Result;
                Console.WriteLine("результат(3 из 10000):");
                for (int i = 0; i < result2.Length * 0.00003; i++)
                {
                    Console.WriteLine(result2[i]);
                }
            }
            catch (AggregateException ex)
            {
                if (ex.InnerException is TaskCanceledException)
                {
                    Console.WriteLine("задача отменена");
                }
            }
            Stopwatch stopwatch2 = Stopwatch.StartNew();
            for (int i = 0; i < 10; i++)
            {
                multiplicationTask2 = Task.Run(() => MultiplyVectorByScalar(CreateVector(100000), 2.5, cancellationToken));
                multiplicationTask2.Wait();
            }
            stopwatch2.Stop();
            Console.WriteLine("cреднее время выполнения: " + stopwatch2.Elapsed.TotalMilliseconds / 10 + " ms");
            cancellationTokenSource.Cancel();
            // 3
            Console.WriteLine("---------------3---------------");
            Async().GetAwaiter().GetResult();
            // 4.1 - полезен для множества сложных условий, более громоздкий 
            Console.WriteLine("---------------4.1---------------");
            Task<int> initialTask = Task.Run(() => CalculateInitialResult());
            Console.WriteLine("результат: " + initialTask.Result);
            Task<string> continuationTask = initialTask.ContinueWith(previousTask =>
            {
                int result = previousTask.Result;
                return "continuation task 1: " + result * 2;
            });
            Console.WriteLine(continuationTask.Result);
            // 4.2 - полезен, когда просто нужно ожидать и использовать результат предыдущей задачи
            Console.WriteLine("---------------4.2---------------");
            FourTask();
            // 5 
            Console.WriteLine("---------------5---------------");
            Parallel.For(1, 5, Square);
            void Square(int n)
            {
                Console.WriteLine($"задача {Task.CurrentId}");
                Console.WriteLine($"квадрат числа {n} равен {n * n}");
                Thread.Sleep(2000);
            }
            Console.WriteLine("\n");
            List<int> list = new List<int>() { 1, 2, 3, 4 };
            ParallelLoopResult result3 = Parallel.ForEach<int>(list, Square2);
            void Square2(int n)
            {
                Console.WriteLine($"задача {Task.CurrentId}");
                Console.WriteLine($"квадрат числа {n} равен {n * n}");
                Thread.Sleep(2000);
            }
            // 6
            Console.WriteLine("---------------6---------------");
            Parallel.Invoke( // метод Parallel.Invoke выполняет три метода
                Print,
                () =>
                {
                    Console.WriteLine($"задача {Task.CurrentId}");
                    Thread.Sleep(3000);
                },
                () => Square3(5)
            );
            void Print()
            {
                Console.WriteLine($"задача {Task.CurrentId}");
                Thread.Sleep(3000);
            }
            void Square3(int n)
            {
                Console.WriteLine($"задача {Task.CurrentId}");
                Thread.Sleep(3000);
                Console.WriteLine($"результат {n * n}");
            }
            // 7
            Console.WriteLine("---------------7---------------");
            Console.WriteLine("нажмите, чтобы запустить 7 задание. консоль будет очищена.");
            Console.ReadLine();
            Task7();
        }
        // 1
        static double[] CreateVector(int size)
        {
            double[] vector = new double[size];
            Random random = new Random();
            for (int i = 0; i < size; i++)
            {
                vector[i] = random.NextDouble();
            }
            return vector;
        }
        static double[] MultiplyVectorByScalar(double[] vector, double scalar)
        {
            double[] result = new double[vector.Length];
            for (int i = 0; i < vector.Length; i++)
            {
                result[i] = vector[i] * scalar;
            }
            return result;
        }
        // 2
        static double[] MultiplyVectorByScalar(double[] vector, double scalar, CancellationToken cancellationToken)
        {
            double[] result = new double[vector.Length];
            for (int i = 0; i < vector.Length; i++)
            {
                cancellationToken.ThrowIfCancellationRequested();

                result[i] = vector[i] * scalar;
            }
            return result;
        }
        // 3
        static async Task Async()
        {
            Task<string> task1 = ProcessDataAsync("1");
            Task<string> task2 = ProcessDataAsync("2");
            Task<string> task3 = ProcessDataAsync("3");
            string[] results = await Task.WhenAll(task1, task2, task3);
            string finalResult = string.Join(", ", results);
            Console.WriteLine("результат: " + finalResult);
        }
        static async Task<string> ProcessDataAsync(string input)
        {
            await Task.Delay(1000); // Имитация асинхронной операции
            return "мяу" + input;
        }
        // 4 
        static int CalculateInitialResult()
        {
            return 10;
        }
        // 4.2
        static async Task FourTask()
        {
            Task<int> initialTask = Task.Run(() => CalculateInitialResult());
            Console.WriteLine("результат: " + initialTask.Result);
            Task<string> continuationTask = Task.Run(async () =>
            {
                int result = await initialTask;
                return "continuation task 2: " + result * 2;
            });
            Console.WriteLine(continuationTask.GetAwaiter().GetResult());
        }
        // 7
        static void Task7()
        {
            BlockingCollection<string> bc = new BlockingCollection<string>(5);
            Task[] sellers = new Task[10];
            Task[] consumers = new Task[5];
            // циклы for тупо для создания и запуска задач 
            for (int i = 0; i < sellers.Length; i++)
            {
                int sellerId = i;
                sellers[i] = Task.Run(() =>
                {
                    while (true)
                    {
                        Thread.Sleep(700);
                        bc.Add(GetProductByIndex(sellerId));
                    }
                });
            }
            for (int i = 0; i < consumers.Length; i++)
            {
                consumers[i] = Task.Run(() =>
                {
                    while (true)
                    {
                        Thread.Sleep(GetConsumerSleepTime(i));
                        bc.Take();
                    }
                });
            }
            int count = 1; // чекаем изменения на складе
            while (true)
            {
                if (bc.Count != count && bc.Count != 0)
                {
                    count = bc.Count;
                    Thread.Sleep(500);
                    Console.Clear();
                    Console.WriteLine("---------------Склад---------------");
                    foreach (var item in bc)
                    {
                        Console.WriteLine(item);
                    }
                }
            }
        }
        static string GetProductByIndex(int index)
        {
            string[] products = { "Стол", "Шкаф", "Зеркало", "Бра", "Подоконник", "Микроволновка", "Кровать", "Дверь", "Вазон", "Стул" };
            return products[index];
        }

        static int GetConsumerSleepTime(int index)
        {
            int[] sleepTimes = { 300, 500, 500, 400, 250 };
            return sleepTimes[index];
        }
    }
}