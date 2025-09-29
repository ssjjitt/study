//using System;
//using System.Linq;

//// Основной класс IntArray
//public class IntArray
//{
//    public int[] Data; // Массив целых чисел

//    // Конструктор класса, принимающий размер массива
//    public IntArray(int size)
//    {
//        Data = new int[size];
//    }

//    // Индексатор для доступа к элементам массива
//    public int this[int index]
//    {
//        get { return Data[index]; }
//        set { Data[index] = value; }
//    }

//    // Свойство для получения длины массива
//    public int Length
//    {
//        get { return Data.Length; }
//    }

//    // Перегрузка оператора + для сложения двух массивов
//    public static IntArray operator +(IntArray arr1, IntArray arr2)
//    {
//        if (arr1.Length != arr2.Length)
//            throw new InvalidOperationException("Длины массивов должны совпадать");

//        IntArray result = new IntArray(arr1.Length);
//        for (int i = 0; i < arr1.Length; i++)
//        {
//            result[i] = arr1[i] + arr2[i];
//        }
//        return result;
//    }

//    // Перегрузка оператора - для вычитания скаляра из массива
//    public static IntArray operator -(IntArray arr1, int scalar)
//    {
//        IntArray result = new IntArray(arr1.Length);
//        for (int i = 0; i < arr1.Length; i++)
//        {
//            result[i] = arr1[i] - scalar;
//        }
//        return result;
//    }

//    // Перегрузка операторов > и < для сравнения длин массивов
//    public static bool operator >(IntArray arr1, IntArray arr2)
//    {
//        return arr1.Length > arr2.Length;
//    }
//    public static bool operator <(IntArray arr1, IntArray arr2)
//    {
//        return arr1.Length < arr2.Length;
//    }

//    // Перегрузка операторов != и == для сравнения массивов
//    public static bool operator !=(IntArray arr1, IntArray arr2)
//    {
//        return !arr1.Equals(arr2);
//    }
//    public static bool operator ==(IntArray arr1, IntArray arr2)
//    {
//        if (ReferenceEquals(arr1, null) && ReferenceEquals(arr2, null))
//            return true;
//        if (ReferenceEquals(arr1, null) || ReferenceEquals(arr2, null))
//            return false;
//        if (arr1.Length != arr2.Length)
//            return false;

//        for (int i = 0; i < arr1.Length; i++)
//        {
//            if (arr1[i] != arr2[i])
//                return false;
//        }
//        return true;
//    }

//    // Вложенный класс Production
//    public class Production
//    {
//        public int Id { get; set; }
//        public string OrganizationName { get; set; }

//        // Конструктор вложенного класса Production
//        public Production(int id, string organizationName)
//        {
//            Id = id;
//            OrganizationName = organizationName;
//        }
//    }

//    // Вложенный класс Developer
//    public class Developer
//    {
//        public int Id { get; set; }
//        public string FullName { get; set; }
//        public string Department { get; set; }

//        // Конструктор вложенного класса Developer
//        public Developer(int id, string fullName, string department)
//        {
//            Id = id;
//            FullName = fullName;
//            Department = department;
//        }
//    }
//}

//// Класс с методами расширения для IntArray
//public static class IntArrayExtensions
//{
//    // Метод для удаления первых N элементов массива
//    public static IntArray RemoveFirstNElements(this IntArray arr, int n)
//    {
//        if (n >= arr.Length)
//            return new IntArray(0);

//        IntArray result = new IntArray(arr.Length - n);
//        for (int i = n; i < arr.Length; i++)
//        {
//            result[i - n] = arr[i];
//        }
//        return result;
//    }
//}

//// Класс с методами расширения для строк
//public static class StringExtensions
//{
//    // Метод для удаления гласных из строки
//    public static string RemoveVowels(this string str)
//    {
//        return new string(str.Where(c => !("AEIOUaeiou".Contains(c))).ToArray());
//    }
//}

//// Статический класс для операций над IntArray
//public static class StatisticOperation
//{
//    // Метод для вычисления суммы элементов массива
//    public static int Sum(IntArray arr)
//    {
//        if (arr.Length == 0)
//            throw new InvalidOperationException("Массив пустой");
//        return arr.Data.Sum();
//    }

//    // Метод для вычисления разницы между максимальным и минимальным элементами массива
//    public static int DifferenceBetweenMaxAndMin(IntArray arr)
//    {
//        if (arr.Length == 0)
//            throw new InvalidOperationException("Массив пустой");
//        int min = arr.Data.Min();
//        int max = arr.Data.Max();
//        return max - min;
//    }

//    // Метод для подсчета количества элементов массива
//    public static int CountElements(IntArray arr)
//    {
//        return arr.Length;
//    }
//}

//// Главный класс программы
//class Program
//{
//    static void Main(string[] args)
//    {
//        // Создание экземпляров IntArray
//        IntArray arr1 = new IntArray(5) { [0] = 1, [1] = 2, [2] = 3, [3] = 4, [4] = 5 };
//        IntArray arr2 = new IntArray(5) { [0] = 5, [1] = 4, [2] = 3, [3] = 2, [4] = 1 };

//        // Использование перегруженных операторов
//        IntArray sum = arr1 + arr2;
//        IntArray subtract = arr1 - 3;
//        bool greater = arr1 > arr2;
//        bool notEqual = arr1 != arr2;

//        // Вывод результатов
//        Console.WriteLine("Сумма: " + string.Join(", ", sum.Data));
//        Console.WriteLine("Разность: " + string.Join(", ", subtract.Data));
//        Console.WriteLine("Первый массив больше второго: " + greater);
//        Console.WriteLine("Массивы не равны: " + notEqual);

//        // Использование методов расширения
//        string inputString = "Hello World";
//        string resultString = inputString.RemoveVowels();
//        Console.WriteLine("Строка после удаления гласных: " + resultString);

//        IntArray arr3 = new IntArray(10) { [0] = 1, [1] = 2, [2] = 3, [3] = 4, [4] = 5, [5] = 6, [6] = 7, [7] = 8, [8] = 9, [9] = 10 };
//        IntArray newArr = arr3.RemoveFirstNElements(5);
//        Console.WriteLine("Массив после удаления первых пяти элементов: " + string.Join(", ", newArr.Data));

//        // Создание и использование объектов вложенных классов
//        IntArray.Production production = new IntArray.Production(1, "THM");
//        Console.WriteLine("Поля вложенного класса Production: ");
//        Console.WriteLine(production.Id);
//        Console.WriteLine(production.OrganizationName);

//        IntArray.Developer developer = new IntArray.Developer(1, "Ivan", "depart");
//        Console.WriteLine("Поля вложенного класса Developer: ");
//        Console.WriteLine(developer.Id);
//        Console.WriteLine(developer.Department);
//        Console.WriteLine(developer.FullName);
//    }
//}
