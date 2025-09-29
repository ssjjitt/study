using System;
namespace OOP_lab8
{
    class Program
    {
        static void Main()
        {
            User user1 = new User();
            User user2 = new User();

            // Подписываем на события
            user1.Move += offset => Console.WriteLine($"Пользователь 1 сдвинулся на {offset} единиц.");
            user2.Move += offset => Console.WriteLine($"Пользователь 1 сдвинулся на {offset} единиц.");

            user1.Compress += factor => Console.WriteLine($"Пользователь 1 сжат в {factor} раз.");
            user2.Compress += factor => Console.WriteLine($"Пользователь 1 сжат в {factor} раз.");

            int number = ReadIntegerFromConsole();
            double dnumber = ReadDoubleFromConsole();
            // Вызываем события
            user1.OnMove(number);
            user2.OnCompress(dnumber);
            // Проверяем состояния объектов

            Console.WriteLine("Введите строку для изменений: ");
            string initialString = Console.ReadLine();

            // Создаем цепочку обработки строки
            Func<string, string>[] stringProcessors = new Func<string, string>[] // Создается массив лямбда-функций
            {
            StringProcessor.RemovePunctuation,
            str => StringProcessor.AddSymbols(str, "!!!"),
            StringProcessor.ToUpperCase,
            StringProcessor.RemoveExtraSpaces,
            StringProcessor.CustomMethod // Добавьте свой метод при необходимости
            };

            // Применяем цепочку обработки
            string result = initialString;
            foreach (var processor in stringProcessors) // применение цепочки обработки к исходной строке с помощью цикла
            {
                result = processor(result);
            }

            Console.WriteLine(result);
        }

        public static int ReadIntegerFromConsole()
        {
            int number = 0;
            try
            {
                bool isValidInput = false;
                do
                {
                    Console.WriteLine("Введите целое число:");
                    string input = Console.ReadLine();
                    isValidInput = int.TryParse(input, out number);
                    if (!isValidInput)
                    {
                        Console.WriteLine("Неправильный формат числа. Попробуйте снова.");
                    }

                } while (!isValidInput);
            }
            catch (FormatException)
            {
                throw new InvalidNumberInputException("Неправильный формат числа. Введите целое число.");
            }
            catch (Exception ex)
            {
                Console.WriteLine($"Произошла ошибка: {ex.Message}");
            }

            return number;
        }

        public static double ReadDoubleFromConsole()
        {
            double dnumber = 0;
            try
            {
                bool isValidInput = false;
                do
                {
                    Console.WriteLine("Введите число с плавающей точкой:");
                    string input = Console.ReadLine();
                    isValidInput = double.TryParse(input, out dnumber);
                    if (!isValidInput)
                    {
                        Console.WriteLine("Неправильный формат числа. Попробуйте снова.");
                    }

                } while (!isValidInput);
            }
            catch (FormatException)
            {
                throw new InvalidNumberInputException("Неправильный формат числа. Введите число с плавающей точкой.");
            }
            catch (Exception ex)
            {
                Console.WriteLine($"Произошла ошибка: {ex.Message}");
            }

            return dnumber;
        }
    }
}