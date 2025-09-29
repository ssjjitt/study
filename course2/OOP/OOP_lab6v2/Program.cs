using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Diagnostics;

namespace OOP_lab5
{
    class Program
    {
        private static void Main(string[] args)
        {
            Console.WriteLine("-----------------------------------------------------------------------\n");
            
            Exepts();

            bool bb = AssertTry(12);
            // Debug.Assert(bb, "testing"); // выявляет потенциальные ошибки в коде
        }

        static bool AssertTry(int x)
        {
            bool b;
            if(x > 10)
            {
                b = false;
            }
            else
            {
                b = true;
            }
            return b;
        }

        static void Exepts()
        {
            Console.WriteLine("----------------------------------LAB6---------------------------------\n");
            Console.WriteLine("-----------------------------------------------------------------------\n");
            try
            {
                Circle circle1 = new Circle(-1, 2);
            }
            catch (GeometryException ex)
            {
                Console.WriteLine("Ошибка при создании круга");
                Console.WriteLine($"Место: {ex.StackTrace}");
                Console.WriteLine($"Причина: {ex.Message}");
            }
            Console.WriteLine("\n-----------------------------------------------------------------------\n");
            try
            {
                Rectangle Rectangle1 = new Rectangle(-1, -2, 2);
            }
            catch (RectangleException ex)
            {
                Console.WriteLine("Ошибка при создании прямоугольника:");
                Console.WriteLine($"Место: {ex.StackTrace}");
                Console.WriteLine($"Причина: {ex.Message}");
                if (ex.Value <= 0)
                {
                    Console.WriteLine($"Некорректное значение стороны 1: {ex.Value}");
                }
                if (ex.Value2 <= 0)
                {
                    Console.WriteLine($"Некорректное значение стороны 2: {ex.Value2}");
                }
            }
            Console.WriteLine("\n-----------------------------------------------------------------------\n");
            try
            {
                Rectangle Rectangle2 = new Rectangle(2, 1001, 2);
            }
            catch (OutException ex)
            {
                Console.WriteLine($"Ошибка OutException: {ex.ParamName} = {ex.ActualValue}. {ex.Message}");
            }
            Console.WriteLine("\n-----------------------------------------------------------------------\n");
            try
            {
                Rectangle Rectangle3 = new Rectangle(2, 4, 0);
            }
            catch (ZeroException ex)
            {
                Console.WriteLine($"Ошибка ZeroException: {ex.Message}");
            }
            Console.WriteLine("\n-----------------------------------------------------------------------\n");
            try
            {
                Rectangle Rectangle3 = new Rectangle(-1, -13, 0);
            }
            catch (Exception ex)
            {
                Console.WriteLine($"Ошибка Exception: {ex.Message}");
                Console.WriteLine("Универсальный обработчик catch");
            }
            Console.WriteLine("\n-----------------------------------------------------------------------\n");
            try
            {
                try
                {
                    Rectangle Rectangle4 = new Rectangle(2, 3, 0);
                }
                catch (ZeroException ex)
                {
                    Console.WriteLine($"Ошибка ZeroException: {ex.Message}");
                    throw;
                }
            }
            catch (ZeroException ex)
            {
                Console.WriteLine($"Ошибка ZeroException: {ex.Message}");
            }
            finally 
            { 
                Console.WriteLine("Блок finally выполнен"); 
            }
            Console.WriteLine("\n-----------------------------------------------------------------------\n");
            // доп задание
            try
            {
                new Rectangle(-42, 6, 2);
            }
            catch (Exception e)
            {
                Logger.LogErrorinFile(e);
                Logger.LogErrorinConsole(e);
            }

        }
    }
}