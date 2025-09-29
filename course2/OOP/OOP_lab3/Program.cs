using System;
using System.Drawing;
using System.Linq;

public class CustomArray // Создать заданный в варианте класс. 
{
    public int[] Data;

    public CustomArray(int size)
    {
        Data = new int[size];
    }

    public int this[int index] // ИНДЕКСАТОР для доступа к элементам массива
    {
        get { return Data[index]; }
        set { Data[index] = value; }
    }

    public int Length
    {
        get { return Data.Length; }
    }

    // ПЕРЕГРУЗКИ
    public static CustomArray operator +(CustomArray arr1, CustomArray arr2) 
    {
        if (arr1.Length != arr2.Length)
            throw new InvalidOperationException("Длины массивов должны совпадать");

        CustomArray result = new CustomArray(arr1.Length);
        for (int i = 0; i < arr1.Length; i++)
        {
            result[i] = arr1[i] + arr2[i];
        }
        return result;
    }

    public static CustomArray operator -(CustomArray arr1, int scalar) 
    {
        CustomArray result = new CustomArray(arr1.Length);
        for (int i = 0; i < arr1.Length; i++)
        {
            result[i] = arr1[i] - scalar;
        }
        return result;
    }

    public static bool operator >(CustomArray arr1, CustomArray arr2)
    {
        return arr1.Length > arr2.Length;
    }

    public static bool operator <(CustomArray arr1, CustomArray arr2)
    {
        return arr1.Length < arr2.Length;
    }

    public static bool operator !=(CustomArray arr1, CustomArray arr2)
    {
        return !arr1.Equals(arr2);
    }

    public static bool operator ==(CustomArray arr1, CustomArray arr2)
    {
        if (ReferenceEquals(arr1, null) && ReferenceEquals(arr2, null))
            return true;
        if (ReferenceEquals(arr1, null) || ReferenceEquals(arr2, null))
            return false;
        if (arr1.Length != arr2.Length)
            return false;

        for (int i = 0; i < arr1.Length; i++)
        {
            if (arr1[i] != arr2[i])
                return false;
        }
        return true;
    }

    public class Production
    {
        public int Id { get; set; }
        public string OrganizationName { get; set; }

        public Production(int id, string organizationName)
        {
            Id = id;
            OrganizationName = organizationName;
        }
    }

    public class Developer
    {
        public int Id { get; set; }
        public string FullName { get; set; }
        public string Department { get; set; }

        public Developer(int id, string fullName, string department)
        {
            Id = id;
            FullName = fullName;
            Department = department;
        }
    }
}

public static class CustomArrayExtensions
{
    public static CustomArray RemoveFirstNElements(this CustomArray arr, int n)
    {
        if (n >= arr.Length)
            return new CustomArray(0);

        CustomArray result = new CustomArray(arr.Length - n);
        for (int i = n; i < arr.Length; i++)
        {
            result[i - n] = arr[i];
        }
        return result;
    }
}

public static class StringExtensions
{
    public static string RemoveVowels(this string str)
    {
        return new string(str.Where(c => !("AEIOUaeiouАЕЁИОУЫЭЮЯаеёиоуыэюя".Contains(c))).ToArray());
    }
}

public static class StatisticOperation
{
    public static int Sum(CustomArray arr)
    {
        if (arr.Length == 0)
            throw new InvalidOperationException("Массив пустой");
        return arr.Data.Sum();
    }

    public static int DifferenceBetweenMaxAndMin(CustomArray arr)
    {
        if (arr.Length == 0)
            throw new InvalidOperationException("Массив пустой");
        int min = arr.Data.Min();
        int max = arr.Data.Max();
        return max - min;
    }

    public static int CountElements(CustomArray arr)
    {
        return arr.Length;
    }
}

class Program
{
    static void Main(string[] args)
    {
        int arrSize = 5;
        int[] Array, Array2;
        Array = new int[arrSize];
        Array2 = new int[arrSize]; 

        for (int i = 0; i < arrSize; i++)
        {
            int element;
            do
            {
                Console.Write($"Введите {i} элемент для первого массива: ");
            } while (!int.TryParse(Console.ReadLine(), out element));

            Array[i] = element;
        }

        for (int i = 0; i < arrSize; i++)
        {
            int element;
            do
            {
                Console.Write($"Введите {i} элемент для второго массива: ");
            } while (!int.TryParse(Console.ReadLine(), out element));

            Array2[i] = element;
        }

        CustomArray arr1 = new CustomArray(arrSize) { [0] = Array[0], [1] = Array[1], [2] = Array[2], [3] = Array[3], [4] = Array[4] };
        CustomArray arr2 = new CustomArray(arrSize) { [0] = Array2[0], [1] = Array2[1], [2] = Array2[2], [3] = Array2[3], [4] = Array2[4] };
        CustomArray arr4 = new CustomArray(arrSize - 1) { [0] = Array[0], [1] = Array2[1], [2] = Array[2], [3] = Array2[3] };
        
        CustomArray sum = arr1 + arr2;
        CustomArray subtract = arr1 - 3;
        bool greater = arr1 > arr4;
        bool notEqual = arr1 != arr2;

        Console.WriteLine("Сумма: " + string.Join(", ", sum.Data));
        Console.WriteLine("Разность: " + string.Join(", ", subtract.Data));
        Console.WriteLine("Первый массив больше третьего: " + greater);
        Console.WriteLine("Массивы не равны: " + notEqual);

        string inputString;
        bool isValid = false;

        do
        {
            Console.Write("Введите строку: ");
            inputString = Console.ReadLine();

            if (string.IsNullOrEmpty(inputString))
            {
                Console.WriteLine("Строка пуста.");
            }
            else if (inputString.All(char.IsDigit))
            {
                Console.WriteLine("Строка состоит только из цифр.");
            }
            else if (inputString.All(char.IsWhiteSpace))
            {
                Console.WriteLine("Строка состоит только из пробелов.");
            }
            else
            {
                isValid = true;
            }

        } while (!isValid);

        Console.WriteLine("Вы ввели корректную строку: " + inputString);
        string resultString = inputString.RemoveVowels();
        Console.WriteLine("Строка после удаления гласных: " + resultString);

        CustomArray arr3 = new CustomArray(10) { [0] = 1, [1] = 2, [2] = 3, [3] = 4, [4] = 5, [5] = 6, [6] = 7, [7] = 8, [8] = 9, [9] = 10 };
        CustomArray newArr = arr3.RemoveFirstNElements(5);
        Console.WriteLine("Массив после удаления первых пяти элементов: " + string.Join(", ", newArr.Data));

        CustomArray.Production production = new CustomArray.Production(1, "THM");
        Console.WriteLine("Поля вложенного класса Production: ");
        Console.WriteLine(production.Id);
        Console.WriteLine(production.OrganizationName);

        CustomArray.Developer developer = new CustomArray.Developer(1, "Ivan", "depart");
        Console.WriteLine("Поля вложенного класса Developer: ");
        Console.WriteLine(developer.Id);
        Console.WriteLine(developer.Department);
        Console.WriteLine(developer.FullName);
    }
}
