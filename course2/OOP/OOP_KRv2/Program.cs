using System;

namespace OOP_KRv2
{
    enum Meridiem
    {
        AM,
        PM
    }

    interface ICheck
    {
        void Check();
    }


    class Time : ICheck
    {
        public int Hours { get; set; }
        public int Minutes { get; set; }
        public int Seconds { get; set; }
        public Meridiem Meridiem { get; set; }
        public Time(int hours, int minutes, int seconds, Meridiem meridiem)
        {
            Hours = hours;
            Minutes = minutes;
            Seconds = seconds;
            Meridiem = meridiem;
        }
        public override string ToString()
        {
            return $"{Hours:D2}:{Minutes:D2}:{Seconds:D2} {Meridiem}";
        }
        public static bool operator <(Time t1, Time t2)
        {
            if (t1.Hours < t2.Hours)
                return true;
            if (t1.Hours > t2.Hours)
                return false;
            if (t1.Minutes < t2.Minutes)
                return true;
            if (t1.Minutes > t2.Minutes)
                return false;
            if (t1.Seconds < t2.Seconds)
                return true;
            if (t1.Seconds > t2.Seconds)
                return false;
            return false;
        }
        public static bool operator >(Time t1, Time t2)
        {
            return t2 < t1;
        }
        public static bool operator ==(Time t1, Time t2)
        {
            return t1.Hours == t2.Hours &&
                   t1.Minutes == t2.Minutes &&
                   t1.Seconds == t2.Seconds &&
                   t1.Meridiem == t2.Meridiem;
        }
        public static bool operator !=(Time t1, Time t2)
        {
            return !(t1 == t2);
        }
        public void Check()
        {
            if (Hours >= 6 && Hours < 12)
                Console.WriteLine("Утро");
            else if (Hours >= 12 && Hours < 18)
                Console.WriteLine("День");
            else if (Hours >= 18 && Hours < 22)
                Console.WriteLine("Вечер");
            else
                Console.WriteLine("Ночь");
        }
    }

    class FullTime : Time, ICheck
    {
        public FullTime(int hours, int minutes, int seconds, Meridiem meridiem) : base(hours, minutes, seconds, meridiem)
        {
        }

        public new void Check()
        {
            TimeSpan timeLeft = new TimeSpan(24, 0, 0) - new TimeSpan(Hours, Minutes, Seconds);
            Console.WriteLine($"Осталось до полуночи: {timeLeft.Hours:D2}:{timeLeft.Minutes:D2}:{timeLeft.Seconds:D2}");
        }
    }

    class Porgram
    {
        static void Main()
        {
            //A) Вывести максимально допустимое число типа short
            short maxShort = short.MaxValue;
            Console.WriteLine("Максимальное значение типа short: " + maxShort);
            //Б)Получить из массива чисел строку, где эти числа разделены запятой
            int[] numbers = { 1, 2, 3, 4, 5 };
            string numbersString = string.Join(",", numbers);
            Console.WriteLine(numbersString);

            Time time1 = new Time(10, 30, 45, Meridiem.AM);
            Time time2 = new Time(4, 15, 30, Meridiem.PM);
            Console.WriteLine("Время 1: " + time1);
            Console.WriteLine("Время 2: " + time2);
            Console.WriteLine("Время 1 < Время 2: " + (time1 < time2));
            Console.WriteLine("Время 1 > Время 2: " + (time1 > time2));
            Console.WriteLine("Время 1 == Время 2: " + (time1 == time2));

            var t = DateTime.Now;
            Time time = new Time(t.Hour, t.Minute, t.Second, Meridiem.AM);
            FullTime fullTime = new FullTime(t.Hour, t.Minute, t.Second, Meridiem.PM);
            Console.WriteLine("Время:");
            time.Check();
            Console.WriteLine();
            Console.WriteLine("Полное время:");
            fullTime.Check();

        }
    }
    

}