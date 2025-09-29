using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;

namespace OOP_lab9
{
    public class Program
    {
        public static void Main()
        {
            BookCollection bookCollection = new BookCollection();
            bookCollection.Add("1", new Book("Призрак Оперы", "Гастон Леру"));
            bookCollection.Add("2", new Book("Бесы", "Федор Достоевский"));
            bookCollection.Add("3", new Book("Граф Монте-Кристо", "Александр Дюма"));
            bookCollection.Add("4", new Book("Морфий", "Михаил Булгаков"));
            bookCollection.Add("5", new Book("Пьяный корабль", "Артюр Рембо"));

            // Вывод всех книг
            Console.WriteLine("Коллекция: ");
            foreach (KeyValuePair<string, Book> book in bookCollection)
            {
                Console.WriteLine(book.Value);
            }
            Console.WriteLine();

            // Поиск книги по ключу
            Console.WriteLine("Введите ключ для поиска:");
            string searchKey = Console.ReadLine();
            Console.WriteLine($"Поиск по ключу {searchKey}:");
            if (bookCollection.ContainsKey(searchKey))
            {
                Book foundBook = bookCollection[searchKey];
                Console.WriteLine(foundBook);
            }
            else
            {
                Console.WriteLine("Не найдено");
            }
            Console.WriteLine();

            // Удаление книги
            Console.WriteLine("Введите ключ для удаления:");
            string removeKey = Console.ReadLine();
            Console.WriteLine($"Удаление книги с ключом {removeKey}:");
            if (bookCollection.Remove(removeKey))
            {
                Console.WriteLine($"Книга с ключом {removeKey} удалена успешно");
            }
            else
            {
                Console.WriteLine("Не найдено");
            }
            Console.WriteLine();

            // Вывод оставшихся книг
            Console.WriteLine("Оставшиеся книги:");
            foreach (KeyValuePair<string, Book> book in bookCollection)
            {
                Console.WriteLine(book.Value);
            }


            Console.WriteLine("\n\n\n\n");


            // Создание и заполнение первой коллекции типа List<int>
            List<int> collection1 = new List<int> { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

            // Вывод первой коллекции на консоль
            Console.WriteLine("Первая коллекция:");
            foreach (int item in collection1)
            {
                Console.WriteLine(item);
            }
            Console.WriteLine();

            // Удаление n последовательных элементов из первой коллекции
            int n = 0;
            bool validInput = false;
            while (!validInput)
            {
                Console.Write("Введите целое число для удаления n элементов: ");
                string input = Console.ReadLine();

                if (int.TryParse(input, out n))
                {
                    validInput = true;
                }
                else
                {
                    Console.WriteLine("Некорректный ввод. Попробуйте ещё раз.");
                }
            }
            collection1.RemoveRange(0, n);

            // Вывод первой коллекции после удаления элементов
            Console.WriteLine($"Первая коллекция после удаления {n} элементов:");
            foreach (int item in collection1)
            {
                Console.WriteLine(item);
            }
            Console.WriteLine();

            // Добавление других элементов в первую коллекцию
            int n1 = 0;
            validInput = false;
            while (!validInput)
            {
                Console.Write("Введите целое число для добавления в конец: ");
                string input = Console.ReadLine();

                if (int.TryParse(input, out n1))
                {
                    validInput = true;
                }
                else
                {
                    Console.WriteLine("Некорректный ввод. Попробуйте ещё раз.");
                }
            }
            collection1.Add(n1);
            collection1.Insert(0, 0);

            // Вывод первой коллекции после добавления элементов
            Console.WriteLine("Первая коллекция после добавления элементов:");
            foreach (int item in collection1)
            {
                Console.WriteLine(item);
            }
            Console.WriteLine();

            // Создание второй коллекции типа LinkedList<int> и заполнение ее данными из первой коллекции
            LinkedList<int> collection2 = new LinkedList<int>(collection1);

            // Вывод второй коллекции на консоль
            Console.WriteLine("Вторая коллекция:");
            foreach (int item in collection2)
            {
                Console.WriteLine(item);
            }
            // Значение для поиска
            int searchValue = 7;

            // Поиск значения во второй коллекции с использованием метода Contains
            bool containsValue = collection2.Contains(searchValue);
            Console.WriteLine($"Значение {searchValue} {(containsValue ? "найдено" : "не найдено")} во второй коллекции.");


            // Создание объекта наблюдаемой коллекции типа ObservableCollection<MyClass>
            ObservableCollection<Book> collection = new ObservableCollection<Book>();

            // Регистрация метода на событие CollectionChanged
            collection.CollectionChanged += CollectionChangedHandler;

            // Добавление элементов
            collection.Add(new Book("Алиса в Стране чудес", "Льюис Кэрролл"));
            collection.Add(new Book("Война миров", "Герберт Уэллс"));
            collection.Add(new Book("Над пропастью во ржи", "Джером Д. Сэлинджер"));
            collection.Add(new Book("Три товарища", "Эрих Мария Ремарк"));
            collection.Add(new Book("Анна Каренина", "Лев Толстой"));

            // Удаление элемента
            collection.RemoveAt(0);

            // Демонстрация текущего состояния коллекции
            Console.WriteLine("Текущая коллекция:");
            foreach (Book item in collection)
            {
                Console.WriteLine($"Название: {item.Title}, Автор: {item.Author}");
            }
        }

        // Метод-обработчик события CollectionChanged
        private static void CollectionChangedHandler(object sender, System.Collections.Specialized.NotifyCollectionChangedEventArgs e)
        {
            Console.WriteLine("Событие CollectionChanged произошло.");
        }
    }
}