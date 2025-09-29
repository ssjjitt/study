using System;


namespace OOP_KR
{
    //создать класс day с массивом строк содержащим названия дней недели и индексатором доступа ко дню по индексу(предусмотреть обработку исключения для некорректного индекса). переопределить 2 метода из Object
    class Day
    {
        private string[] daysOfWeek = { "Понедельник", "Вторник", "Среда", "Четверг", "Пятница", "Суббота", "Воскресенье" };
        public string this[int index]
        {
            get
            {
                if (index >= 0 && index < daysOfWeek.Length)
                {
                    return daysOfWeek[index];
                }
                else
                {
                    throw new IndexOutOfRangeException("Некорректный индекс.");
                }
            }
            set
            {
                if (index >= 0 && index < daysOfWeek.Length)
                {
                    daysOfWeek[index] = value;
                }
                else
                {
                    throw new IndexOutOfRangeException("Некорректный индекс.");
                }
            }
        }
        public override string ToString()
        {
            return string.Join(", ", daysOfWeek);
        }
        public override bool Equals(object obj)
        {
            if (obj is Day other)
            {
                return daysOfWeek.SequenceEqual(other.daysOfWeek);
            }
            return false;
        }
        public override int GetHashCode()
        {
            return daysOfWeek.GetHashCode();
        }
    }



    interface IMove
    {
        void Move();
    }

    abstract class Transport
    {
        public abstract void Move();
    }

    class Car : Transport, IMove
    {
        public override void Move()
        {
            Console.WriteLine("Автомобиль движется по дороге.");
        }

        void IMove.Move()
        {
            Console.WriteLine("Автомобиль перемещается.");
        }
    }
    class Program
    {
        static void Main(string[] args)
        {
            //ввести две строки проверить содержит ли одна строка в себе другую c#
            string str1 = "Пример СтроКа 1";
            string str2 = "СтрОка 1";
            if (str1.ToLower().Contains(str2.ToLower()))
            {
                Console.WriteLine("Строка 1 содержит строку 2");
            }
            else
            {
                Console.WriteLine("Строка 1 не содержит строку 2");
            }
            //создать одномерный массив строк поменять местами порядок строк на обратный
            string[] strings = { "строка 1", "строка 2", "строка 3", "строка 4", "строка 5" };
            Array.Reverse(strings);
            foreach (string str in strings)
            {
                Console.WriteLine(str);
            }
            // DAY
            Day days = new Day();
            Console.WriteLine(days[0]);
            days[0] = "Monday";
            Console.WriteLine(days[0]);
            Console.WriteLine(days);
            Day otherDays = new Day();
            otherDays[0] = "Monday";
            Console.WriteLine(days.Equals(otherDays));
            Console.WriteLine(days.GetHashCode());
            // MOVE
            Car car = new Car();
            // МЕТОДЫ
            car.Move(); // КЛАССА
            ((IMove)car).Move(); // ИНТЕРФЕЙСА
        }

    }
}