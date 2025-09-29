using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace OOP_lab9
{
    public class Book
    {
        public string Title { get; set; }
        public string Author { get; set; }

        public Book(string title, string author)
        {
            Title = title;
            Author = author;
        }

        public override string ToString()
        {
            return $"\nНазвание: {Title}\nАвтор: {Author}\n\n-------------------------";
        }
    }

    public class BookCollection : IDictionary<string, Book>
    {
        private Dictionary<string, Book> books; // Хранение книг в виде словаря

        public BookCollection()
        {
            books = new Dictionary<string, Book>();
        }

        // Индексатор, позволяющий получать и задавать значение книги по ключу
        public Book this[string key]
        {
            get
            {
                books.TryGetValue(key, out Book book);
                return book;
            }
            set
            {
                books[key] = value;
            }
        }

        // Коллекция ключей в виде списка
        public ICollection<string> Keys => books.Keys;

        // Коллекция значений в виде списка всех книг
        public ICollection<Book> Values => books.Values;

        // Количество книг в коллекции
        public int Count => books.Count;

        // Всегда возвращает false, так как коллекция не является только для чтения
        public bool IsReadOnly => false;

        // Добавляет новую книгу в коллекцию
        public void Add(string key, Book value)
        {
            books.Add(key, value);
        }

        // Добавляет новую книгу в коллекцию
        public void Add(KeyValuePair<string, Book> item)
        {
            books.Add(item.Key, item.Value);
        }

        // Очищает коллекцию книг
        public void Clear()
        {
            books.Clear();
        }

        // Проверяет, содержит ли коллекция указанную пару ключ-значение
        public bool Contains(KeyValuePair<string, Book> item)
        {
            return books.Contains(item);
        }

        // Проверяет, содержит ли коллекция указанный ключ
        public bool ContainsKey(string key)
        {
            return books.ContainsKey(key);
        }

        // Копирует элементы коллекции в массив, начиная с указанного индекса
        public void CopyTo(KeyValuePair<string, Book>[] array, int arrayIndex)
        {
            if (array == null)
            {
                throw new ArgumentNullException(nameof(array));
            }

            if (arrayIndex < 0 || arrayIndex >= array.Length)
            {
                throw new ArgumentOutOfRangeException(nameof(arrayIndex));
            }

            if (array.Length - arrayIndex < Count)
            {
                throw new ArgumentException("The number of elements in the collection is greater than the available space from arrayIndex to the end of the destination array.");
            }

            int i = arrayIndex;
            foreach (KeyValuePair<string, Book> item in this)
            {
                array[i] = item;
                i++;
            }
        }

        // Возвращает перечислитель, осуществляющий перебор всех книг в коллекции
        public IEnumerator<KeyValuePair<string, Book>> GetEnumerator()
        {
            return books.GetEnumerator();
        }

        // Удаляет книгу с указанным ключом из коллекции
        public bool Remove(string key)
        {
            return books.Remove(key);
        }

        // Удаляет указанную пару ключ-значение из коллекции
        public bool Remove(KeyValuePair<string, Book> item)
        {
            return books.Remove(item.Key);
        }

        // Пытается получить значение книги по указанному ключу
        public bool TryGetValue(string key, out Book value)
        {
            return books.TryGetValue(key, out value);
        }

        // Возвращает перечислитель, осуществляющий перебор всех книг в коллекции
        IEnumerator IEnumerable.GetEnumerator()
        {
            return books.GetEnumerator();
        }
    }

}
