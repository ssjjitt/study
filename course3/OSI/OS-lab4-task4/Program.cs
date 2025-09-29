using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace OS_lab4_task4
{
    class Program
    {
        // Поток Z работает 10 секунд и выводит ID текущего
        static void ThreadZed()
        {
            for (int i = 0; i < 10; i++)
            {
                Console.Write(" (Z-{0}) ", Thread.CurrentThread.ManagedThreadId);
                Thread.Sleep(1000);
            }
            Console.WriteLine(" Поток Z завершается ");
        }
        // Поток работает 20 секунд, параметр - строка-идентификатор
        static void ThreadWithParam(object o)
        {
            for (int i = 0; i < 20; i++)
            {
                Console.Write(" ({0}-{1}) ", o.ToString(),
                Thread.CurrentThread.ManagedThreadId);
                Thread.Sleep(1000);
            }
        }
        // завершается основной - завершаются и фоновые
        // даже если они еще не завершили выполнение
        static void Main(string[] args)
        {
            var t1 = new Thread(ThreadZed);
            var t1a = new Thread(ThreadWithParam);
            var t1b = new Thread(ThreadWithParam);
            t1.IsBackground = true; // false для п.11
            t1a.IsBackground = false; // false для п.12
            t1b.IsBackground = true;
            t1.Start();
            t1a.Start("Дарья"); // Имя
            t1b.Start("Глухова"); // Фамилия
            // Главный поток работает 5 секунд
            for (int i = 0; i < 5; i++)
            {
                Console.Write(" (*-{0}) ", Thread.CurrentThread.ManagedThreadId);
                Thread.Sleep(1000);
            }
            Console.WriteLine("Главный поток завершается");
        }
    }
}
