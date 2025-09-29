using System;
using System.Text;

namespace Lab1
{
    class Program
    {
        static void Main()
        {
            /* a. Определите переменные всех возможных примитивных типов С# и проинициализируйте их. Осуществите ввод и вывод их значений используя консоль. */
            Console.WriteLine("\nзадание 1(а)");
            bool boolVar = false;
            byte byteVar = 10;
            sbyte sbyteVar = 20;
            char charVar = 'A';
            decimal decimalVar = 123.456m;
            double doubleVar = 1.23456;
            float floatVar = 3.14f;
            int intVar = 30;
            uint uintVar = 40;
            nint nintVar = 50;
            nuint nuintVar = 60;
            long longVar = 70; 
            ulong ulongVar = 80;
            short shortVar = 90;
            ushort ushortVar = 100;
            string stringVar = "AaaAaAA";
            object objectVar = 10;
            Console.WriteLine("bool: " + boolVar);
            Console.WriteLine("byte: " + byteVar);
            Console.WriteLine("sbyte: " + sbyteVar);
            Console.WriteLine("char: " + charVar);
            Console.WriteLine("decimal: " + decimalVar);
            Console.WriteLine("double: " + doubleVar);
            Console.WriteLine("float: " + floatVar);
            Console.WriteLine("int: " + intVar);
            Console.WriteLine("uint: " + uintVar);
            Console.WriteLine("nint: " + nintVar);
            Console.WriteLine("nuint: " + nuintVar);
            Console.WriteLine("long: " + longVar);
            Console.WriteLine("ulong: " + ulongVar);
            Console.WriteLine("short: " + shortVar);
            Console.WriteLine("ushort: " + ushortVar);
            Console.WriteLine("string: " + stringVar);
            Console.WriteLine("object: " + objectVar);
            bool isValidInput1 = false;
            while (!isValidInput1)
            {
                Console.Write("введите bool: ");
                if (bool.TryParse(Console.ReadLine(), out boolVar))             ////////////////////////////////////////////////
                {
                    isValidInput1 = true;
                    Console.WriteLine("bool: " + boolVar);
                }
                else
                {
                    Console.WriteLine("некорректный ввод. пожалуйста, введите true или false.");
                }
            }
            isValidInput1 = false;
            while (!isValidInput1)
            {
                Console.Write("введите char: ");
                if (char.TryParse(Console.ReadLine(), out charVar))
                {
                    isValidInput1 = true;
                    Console.WriteLine("char: " + charVar);
                }
                else
                {
                    Console.WriteLine("некорректный ввод. пожалуйста, введите символ.");
                }
            }
            isValidInput1 = false;
            while (!isValidInput1)
            {
                Console.Write("введите int: ");
                if (int.TryParse(Console.ReadLine(), out intVar))
                {
                    isValidInput1 = true;
                    Console.WriteLine("int: " + intVar);
                }
                else
                {
                    Console.WriteLine("некорректный ввод. пожалуйста, введите целое число.");
                }
            }

            Console.Write("string: ");
            stringVar = Console.ReadLine();
            Console.WriteLine("string: " + stringVar);

            /* b. Выполните 5 операций явного и 5 неявного приведения. Изучите возможности класса Convert. */
            Console.WriteLine("\nзадание 1(b)");
            /////////////////////////////////////////
            double doubleVar1 = -42.12345678;
            float floatVar1 = (float)doubleVar1;
            int intVar1 = (int)floatVar1;
            uint uintVar1 = (uint)floatVar1;
            nuint nuintVar1 = (nuint)doubleVar1;
            byte byteVar1 = (byte)intVar1;
            Console.WriteLine("doubleVar1: " + doubleVar1);
            Console.WriteLine("floatVar1: " + floatVar1);
            Console.WriteLine("intVar1: " + intVar1);
            Console.WriteLine("uintVar1: " + uintVar1);
            Console.WriteLine("nuintVar1: " + nuintVar1);
            Console.WriteLine("byteVar1: " + byteVar1);
            ///////////////////////////////////////////
            char charVar1 = '9';
            int intVar2 = charVar1;
            uint uintVar2 = charVar1;
            float floatVar2 = intVar2;
            double doubleVar2 = intVar2;
            nuint nuintVar2 = charVar1;
            Console.WriteLine("charVar1: " + charVar1);
            Console.WriteLine("intVar2: " + intVar2);
            Console.WriteLine("uintVar2: " + uintVar2);
            Console.WriteLine("nuintVar2: " + nuintVar2);
            Console.WriteLine("floatVar2: " + floatVar2);
            Console.WriteLine("doubleVar2: " + doubleVar2);
            int newInteger = 0;
            isValidInput1 = false;
            do
            {
                try
                {
                    Console.WriteLine("введите целое число:");
                    string userInput = Console.ReadLine();

                    if (string.IsNullOrWhiteSpace(userInput))
                    {
                        Console.WriteLine("введена пустая строка. пожалуйста, введите число.");
                        continue;
                    }

                    newInteger = Convert.ToInt32(userInput);    //////////////////////////////////////////////////////////////////////////////////
                    isValidInput1 = true;
                }
                catch (FormatException)
                {
                    Console.WriteLine("введенная строка не состоит из необязательного знака, за которым следует последовательность цифр.");
                }
                catch (OverflowException)
                {
                    Console.WriteLine("произошло переполнение в процессе преобразования строки в целое число.");
                }
                catch (Exception ex)
                {
                    Console.WriteLine("произошла ошибка: " + ex.Message);
                }
            } while (!isValidInput1);
            Console.WriteLine("ваше число: " + newInteger);

            /*c. Выполните упаковку и распаковку значимых типов.*/
            Console.WriteLine("\nзадание 1(c)");
            int intVar3 = 123;      /////////////////////////////////
            object objVar1 = intVar3;
            Console.WriteLine("упаковка: ");
            Console.WriteLine("int: " + intVar3);
            Console.WriteLine("obj: " + objVar1);
            int intVar4 = (int)objVar1;     /////////////////////////////////
            Console.WriteLine("распаковка: ");
            Console.WriteLine("int: " + intVar4);
            Console.WriteLine("obj: " + objVar1);

            /*d. Продемонстрируйте работу с неявно типизированной переменной.*/
            Console.WriteLine("\nзадание 1(d)");
            var var1 = "AaAAAAaaaa";
            var var2 = 1412;
            var var3 = 'A';
            Console.WriteLine("неявно типизированные переменные: {0}, {1}, {2}", var1, var2, var3);

            /*e.Продемонстрируйте пример работы с Nullable переменной*/
            Console.WriteLine("\nзадание 1(e)");
            int? num = 123;     ///////////////////////////////
            if (num.HasValue)
                Console.WriteLine("num: " + num.Value);
            else
                Console.WriteLine("num равен null");
            Nullable<int> num2 = 23;    ////////////////////////////
            if (num2.HasValue)
                Console.WriteLine("num2: " + num2.Value);
            else
                Console.WriteLine("num2 равен null");
            int? num3 = null;
            if (num3.HasValue)
                Console.WriteLine("num3: " + num3.Value);
            else
                Console.WriteLine("num3 равен null");

            /*f. Определите переменную типа var и присвойте ей любое значение. Затем следующей инструкцией присвойте ей значение другого типа. Объясните причину ошибки.*/
            // var errorVar = 123;  
            // errorVar = 4.23f;     
            // Console.WriteLine("errorVar:" + errorVar);


            // СТРОКИ
            /*a. Объявите строковые литералы. Сравните их.*/
            Console.WriteLine("\nзадание 2(a)");
            string str1 = "солнце";     ///////////////////////////////////////////////////////////////////////////
            string str2 = "луна";
            string str3 = "солнце";
            Console.WriteLine("строковые литералы: {0}, {1}, {2}", str1, str2, str3);
            bool bool1 = (str1 == str2);    //////////////////////////////// 
            // Есть метод Equal - прочитаешь
            bool bool2 = (str1 == str3);
            Console.WriteLine("str1 == str2:" + bool1);
            Console.WriteLine("str1 == str3:" + bool2);

            /*b. Создайте три строки на основе String. Выполните: сцепление, копирование, выделение подстроки, разделение строки на слова, вставки подстроки в заданную позицию, удаление заданной подстроки. Продемонстрируйте интерполирование строк. */
            Console.WriteLine("\nзадание 2(b)");

            string str4 = "je";
            string str5 = "t'";
            string str6 = "aime";
            string str7 = str4 + " " + str5;//////////////////////////////////////////////
            string str8 = string.Concat(str7, str6);    ///////////////////////////////////////////////
            Console.WriteLine("объединенная строка: " + str8);

            string copyStr6 = str6; /////////////////////////////////////////////////
            Console.WriteLine("скопированная строка: " + copyStr6);

            string substr6 = str6.Substring(0, 2);  //////////////////////////////////////////
            Console.WriteLine("выделенная подстрока: " + substr6);

            Console.WriteLine("разделение строки на слова: ");
            string stringee = "соберу все еще раз и сломаю вновь";
            string[] words = stringee.Split(new char[] { ' ' });    ////////////////////////////////////
            foreach (string s in words) /////////////////////////////////////
            {
                Console.WriteLine(s);
            }

            string insstr6 = str6.Insert(3, "eeeee");   ///////////////////////////////////
            Console.WriteLine("вставка подстроки: " + insstr6);

            string remstr6 = str6.Remove(1, 3);///////////////////////////////////
            Console.WriteLine("удаление подстроки: " + remstr6);

            string smth = "глаза";
            string smth2 = "сказать";
            string smthMain = $"не успеваю запомнить {smth} что хотели мне что-то {smth2}";///////////////////////////////////
            Console.WriteLine("интерполирование строк: " + smthMain);///////////////////////////////////

            /*c. Создайте пустую и null строку. Продемонстрируйте использование метода string.IsNullOrEmpty. Продемонстрируйте что еще можно выполнить с такими строками*/
            Console.WriteLine("\nзадание 2(c)");
            string emptystr = string.Empty;
            string nullstr = null;
            Console.WriteLine("emptystr: " + string.IsNullOrEmpty(emptystr)); ///////////////////////////////////
            Console.WriteLine("nullstr: " + string.IsNullOrEmpty(nullstr)); ///////////////////////////////////
            Console.WriteLine("null or space: " + string.IsNullOrWhiteSpace(nullstr)); ///////////////////////////////////
            Console.WriteLine("длина строки: " + emptystr.Length);///////////////////////////////////

            /*d. Создайте строку на основе StringBuilder. Удалите определенные позиции и добавьте новые символы в начало и конец строки.*/
            StringBuilder stringBuilder = new StringBuilder("солнце умрет во тьме однозначно");
            stringBuilder.Remove(20, 11);///////////////////////////////////
            Console.WriteLine("удаление определенных позиций: " + stringBuilder.ToString());
            stringBuilder.Insert(0, "^");///////////////////////////////////
            Console.WriteLine("добавление символов в начало: " + stringBuilder.ToString());
            stringBuilder.Append("^");///////////////////////////////////
            Console.WriteLine("добавление символов в конец: " + stringBuilder.ToString());

            // МАССИВЫ
            /*a. Создайте целый двумерный массив и выведите его на консоль в отформатированном виде (матрица). */
            int rows, columns;
            bool isValidInput = false;
            do
            {
                Console.Write("введите количество строк: ");
                if (int.TryParse(Console.ReadLine(), out rows) && rows > 0)
                {
                    isValidInput = true;
                }
                else
                {
                    Console.WriteLine("некорректный ввод. пожалуйста, введите положительное целое число.");
                }
            } while (!isValidInput);
            isValidInput = false;
            do
            {
                Console.Write("введите количество столбцов: ");
                if (int.TryParse(Console.ReadLine(), out columns) && columns > 0)
                {
                    isValidInput = true;
                }
                else
                {
                    Console.WriteLine("некорректный ввод. пожалуйста, введите положительное целое число.");
                }
            } while (!isValidInput);
            int[,] matrix = new int[rows, columns]; ///////////////////////////////////
            for (int i = 0; i < rows; i++)
            {
                for (int j = 0; j < columns; j++)
                {
                    bool validInput = false;
                    int value = 0;
                    do
                    {
                        Console.Write($"введите значение для элемента [{i},{j}]: ");
                        if (int.TryParse(Console.ReadLine(), out value))
                        {
                            validInput = true;
                        }
                        else
                        {
                            Console.WriteLine("некорректный ввод. пожалуйста, введите целое число.");
                        }
                    } while (!validInput);
                    matrix[i, j] = value;
                }
            }
            Console.WriteLine("матрица:");
            for (int i = 0; i < rows; i++)
            {
                for (int j = 0; j < columns; j++)
                {
                    Console.Write(matrix[i, j] + " ");
                }
                Console.WriteLine();
            }
            /*b. Создайте одномерный массив строк. Выведите на консоль его содержимое, длину массива. Поменяйте произвольный элемент(пользователь определяет позицию и значение).*/
            string[] myArray = { "марс", "юпитер", "сатурн", "нептун", "венера" };  ///////////////////////////////////
            Console.WriteLine("содержимое массива:");
            foreach (string item in myArray)
            {
                Console.WriteLine(item);
            }
            Console.WriteLine($"длина массива: {myArray.Length}");///////////////////////////////////
            Console.Write("введите позицию элемента, который хотите изменить: ");
            int position = Convert.ToInt32(Console.ReadLine());
            if (position >= 0 && position < myArray.Length)
            {
                Console.Write("введите новое значение: ");
                string newValue = Console.ReadLine();
                myArray[position] = newValue;///////////////////////////////////
                Console.WriteLine("новое содержимое массива:");
                foreach (string item in myArray)
                {
                    Console.WriteLine(item);
                }
            }
            else
            {
                Console.WriteLine("вне диапазона массива!");
            }
            // c. Создайте ступечатый (не выровненный) массив вещественных чисел с 3 - мя строками, в каждой из которых 2, 3 и 4 столбцов соответственно.Значения массива введите с консоли
            double[][] jaggedArray = new double[3][];///////////////////////////////////
            bool tr = false;
            for (int i = 0; i < jaggedArray.Length; i++)
            {
                int col;
                do
                {
                    Console.Write($"введите количество столбцов для строки {i + 1}: ");
                    if (!int.TryParse(Console.ReadLine(), out col) || col <= 0)
                    {
                        Console.WriteLine("некорректный ввод.");
                    }
                    else
                    {
                        tr = true;
                    }
                } while (!tr);

                jaggedArray[i] = new double[col];
            }
            tr = false;
            for (int i = 0; i < jaggedArray.Length; i++)
            {
                for (int j = 0; j < jaggedArray[i].Length; j++)
                {
                    double value;

                    do
                    {
                        Console.Write($"введите значение для элемента [{i}][{j}]: ");
                        if (!double.TryParse(Console.ReadLine(), out value))
                        {
                            Console.WriteLine("некорректный ввод. введите числовое значение.");
                        }
                        else
                        {
                            tr = true;
                        }
                    } while (!tr);

                    jaggedArray[i][j] = value;
                }
            }
            
            Console.WriteLine("ступенчатый массив:");
            for (int i = 0; i < jaggedArray.Length; i++)
            {
                for (int j = 0; j < jaggedArray[i].Length; j++)
                {
                    Console.Write($"{jaggedArray[i][j]} ");
                }
                Console.WriteLine();
            }
            // d. Создайте неявно типизированные переменные для хранения массива и строки.
            var myArray1 = new[] { 1, 2, 3, 4, 5 };///////////////////////////////////
            var myString = "строка";///////////////////////////////////
            Console.WriteLine("содержимое неявно типизированного массива:");
            foreach (var item in myArray1)
            {
                Console.WriteLine(item);
            }
            Console.WriteLine("содержимое неявно типизированной строки:");
            Console.WriteLine(myString);

            // КОРТЕЖИ
            // a. Задайте кортеж из 5 элементов с типами int, string, char, string, ulong.
            (int, string, char, string, ulong) t1 = (4, "солнце", 'A', "смеётся", 4444);///////////////////////////////////
            Console.WriteLine("кортеж: " + t1);
            // b. Выведите кортеж на консоль целиком и выборочно ( например 1, 3, 4 элементы)
            Console.WriteLine("второй и четвертый: " + t1.Item2 + " " + t1.Item4);
            // c. Выполните распаковку кортежа в переменные. (_)
            var (numt1, stringt1, chart1, stringt2, ulongt1) = t1;///////////////////////////////////
            (_, string stringt3, _, string stringt4, _) = t1;///////////////////////////////////
            // ПРОЧИТАТЬ ПРО (_)
            // d. Сравните два кортежа
            var t2 = (5, "солнце");
            var t3 = (5, "луна");
            var t4 = (5, "солнце");
            Console.WriteLine("сравнение t2 и t3: " + (t2 == t3));///////////////////////////////////
            Console.WriteLine("сравнение t2 и t4: " + (t2 == t4));

            /* Создайте локальную функцию в main и вызовите ее. Формальные параметры функции – массив
            целых и строка. Функция должна вернуть кортеж, содержащий:
            максимальный и минимальный элементы массива, сумму элементов
            массива и первую букву строки. */
            int[] numbers;
            string inputString;
            do
            {
                Console.Write("введите элементы массива через пробел: ");
                string numbersInput = Console.ReadLine();
                string[] numbersArray = numbersInput.Split(' ');

                if (int.TryParse(numbersArray[0], out int firstNumber))
                {
                    numbers = new int[numbersArray.Length];
                    numbers[0] = firstNumber;

                    for (int i = 1; i < numbersArray.Length; i++)
                    {
                        if (!int.TryParse(numbersArray[i], out numbers[i]))
                        {
                            Console.WriteLine("ошибка! введите корректные элементы массива.");
                            numbers = null;
                            break;
                        }
                    }

                    if (numbers != null)
                        break;
                }
                else
                {
                    Console.WriteLine("ошибка! введите корректные элементы массива.");
                }

            } while (true);
            do
            {
                Console.Write("введите строку: ");
                inputString = Console.ReadLine();

                if (!string.IsNullOrWhiteSpace(inputString))
                    break;
                else
                    Console.WriteLine("ошибка! строка не может быть пустой.");
            } while (true);
            (int max, int min, int sum, char firstChar) result = CalculateValues(numbers, inputString);///////////////////////////////////
            Console.WriteLine($"максимальный: {result.max}");
            Console.WriteLine($"минимальный: {result.min}");
            Console.WriteLine($"сумма: {result.sum}");
            Console.WriteLine($"первая буква: {result.firstChar}");

            // Работа с checked/unchecked
            // c.Вызовите две функции.Проанализируйте результат.
            Console.WriteLine("использование checked:");
            CheckedFunction();///////////////////////////////////

            Console.WriteLine("\nиспользование unchecked:");
            UncheckedFunction();///////////////////////////////////

        }



        static (int max, int min, int sum, char firstChar) CalculateValues(int[] numbers, string inputString)///////////////////////////////////
        {
            int max = numbers[0];
            int min = numbers[0];
            int sum = 0;

            foreach (int number in numbers)
            {
                if (number > max)
                    max = number;

                if (number < min)
                    min = number;

                sum += number;
            }

            char firstChar = inputString.Length > 0 ? inputString[0] : '\0';

            return (max, min, sum, firstChar);
        }
        // a.Определите две локальные функции.
        /* b. Разместите в одной из них блок checked, в котором определите
        переменную типа int с максимальным возможным значением
        этого типа.Во второй функции определите блок unchecked с
        таким же содержимым.*/
        static void CheckedFunction()///////////////////////////////////
        {
            try
            {
                checked/////////////////////////////////// ВНИМАНИЕ
                {
                    int maxValue = int.MaxValue;
                    Console.WriteLine($"максимальное int: {maxValue}");
                    maxValue++; // OverflowException
                    Console.WriteLine($"после инкремента: {maxValue}");
                }
            }
            catch (OverflowException ex)
            {
                Console.WriteLine($"исключение: {ex.Message}");
            }

        }

        static void UncheckedFunction()///////////////////////////////////
        {
            unchecked/////////////////////////////////// ВНИМАНИЕ
            {
                int maxValue = int.MaxValue;
                Console.WriteLine($"максимальное int: {maxValue}");
                maxValue++; // нет переполнения
                Console.WriteLine($"после инкремента: {maxValue}");
            }
        }
    }
}
