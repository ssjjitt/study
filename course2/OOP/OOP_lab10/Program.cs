using System;
using System.ComponentModel.DataAnnotations;
using System.Linq;

namespace OOP_lab10
{
    class Programm
    {
        static void Main()
        {
            string[] months = { "Январь", "Февраль", "Март", "Апрель", "Май", "Июнь", "Июль", "Август", "Сентябрь", "Октябрь", "Ноябрь", "Декабрь" };

            // последовательность с длиной n
            Console.WriteLine("Длина строки: ");
            int n = Convert.ToInt32(Console.ReadLine());
            IEnumerable<string> selectMonths =
                from month in months
                where month.Length == n
                select month;
            Console.WriteLine("-----------------------------------------------------------------");
            Console.WriteLine($"Месяцы с длиной строки {n}:");
            foreach (string month in selectMonths)
            {
                Console.WriteLine(month);
            }


            // только летние и зимние
            IEnumerable<string> selectMonths1 =
                from month in months
                where IsSummerMonth(month) || IsWinterMonth(month)
                select month;

            Console.WriteLine("-----------------------------------------------------------------");
            Console.WriteLine("Только летние и зимние месяцы:");
            foreach (var month in selectMonths1)
            {
                Console.WriteLine(month);
            }


            // алфавитный порядок, содержит "И", длина не менее 4
            int length = 4;
            IEnumerable<string> selectMonths2 =
                from month in months
                where (month.ToLower().Contains("и") && month.Length >= length)
                orderby month
                select month;
            Console.WriteLine("-----------------------------------------------------------------");
            Console.WriteLine($"Месяцы, которые содержат 'И' и длина которых не менее {length}, в алфавитном порядке:");
            foreach (var month in selectMonths2)
            {
                Console.WriteLine(month);
            }


            // ВАРИАНТ
            List<Airline> flights = new List<Airline>
            {
                new Airline("Нью-Йорк", 101, "Boeing 747", new DateTime(2023, 9, 15, 10, 30, 0), DayOfWeek.Monday),
                new Airline("Лондон", 202, "Airbus A320", new DateTime(2023, 9, 26, 12, 45, 0), DayOfWeek.Tuesday),
                new Airline("Париж", 303, "Boeing 777", new DateTime(2023, 9, 17, 14, 15, 0), DayOfWeek.Wednesday),
                new Airline("Токио", 404, "Boeing 787", new DateTime(2023, 9, 28, 16, 30, 0), DayOfWeek.Thursday),
                new Airline("Берлин", 505, "Airbus A330", new DateTime(2023, 9, 19, 18, 15, 0), DayOfWeek.Monday),
                new Airline("Москва", 606, "Boeing 737", new DateTime(2023, 9, 20, 20, 0, 0), DayOfWeek.Saturday),
                new Airline("Санкт-Петербург", 707, "Airbus A380", new DateTime(2023, 9, 21, 9, 30, 0), DayOfWeek.Sunday),
                new Airline("Киев", 808, "Boeing 767", new DateTime(2023, 9, 22, 14, 0, 0), DayOfWeek.Monday),
                new Airline("Варшава", 909, "Airbus A350", new DateTime(2023, 9, 23, 16, 45, 0), DayOfWeek.Tuesday),
                new Airline("Рим", 1010, "Boeing 737", new DateTime(2023, 9, 24, 19, 15, 0), DayOfWeek.Wednesday),
                 new Airline("Нью-Йорк", 1111, "Boeing 757", new DateTime(2023, 9, 23, 15, 00, 0), DayOfWeek.Thursday),
                new Airline("Лондон", 1212, "Airbus B140", new DateTime(2023, 9, 4, 6, 45, 0), DayOfWeek.Saturday),
                new Airline("Лондон", 1313, "Boeing 897", new DateTime(2023, 9, 8, 7, 15, 0), DayOfWeek.Wednesday),
            };


            // список рейсов для заданного пункта назначения
            string destination = "Рим";
            var selectDestination =
                from flight in flights
                where flight.Destination == destination
                select flight;
            Console.WriteLine("-----------------------------------------------------------------");
            Console.WriteLine($"Рейсы в {destination}:");
            foreach (var flight in selectDestination)
            {
                flight.PrintFlightInfo();
            }


            // количество рейсов для заданного дня недели
            DayOfWeek day = DayOfWeek.Monday;
            var selectDay =
                (from flight in flights
                 where flight.DayOfWeek == day
                 select flight).Count();
            Console.WriteLine("-----------------------------------------------------------------");
            Console.WriteLine($"Количество рейсов для дня недели - {day}: " + selectDay);


            //Рейс который вылетает в понедельник раньше всех
            var earliestMondayFlight = flights
            .Where(f => f.DayOfWeek == DayOfWeek.Monday)
            .OrderBy(f => f.DepartureTime)
            .FirstOrDefault();
            Console.WriteLine("-----------------------------------------------------------------");
            Console.WriteLine($"Рейс, который вылетает в {day} раньше всех: ");
            earliestMondayFlight.PrintFlightInfo();


            //Рейс который вылетает в среду или пятницу позже всех
            var latestFlight = flights
            .Where(f => f.DayOfWeek == DayOfWeek.Wednesday || f.DayOfWeek == DayOfWeek.Friday)
            .OrderBy(f => f.DepartureTime)
            .LastOrDefault();
            Console.WriteLine("-----------------------------------------------------------------");
            Console.WriteLine($"Рейс, который вылетает в среду или пятницу позже всех: ");
            latestFlight.PrintFlightInfo();


            //Список рейсов, упорядоченных по времени вылета
            var orderFlights = flights
            .OrderBy(f => f.DepartureTime);
            Console.WriteLine("-----------------------------------------------------------------");
            Console.WriteLine("Список рейсов, упорядоченных по времени вылета: ");
            foreach (var flight in orderFlights)
            {
                flight.PrintFlightInfo();
            }


            // 5 операторов: условие, проекция, упорядочивание, группировка, агрегирование, кванторы, разбиение
            var query = flights
            .Where(f => f.DepartureTime.Year == 2023) // Условие
            .OrderByDescending(f => f.DepartureTime) // Упорядочивание
            .GroupBy(f => f.Destination) // Группировка
            .Select(g => new
            {
                Destination = g.Key,
                TotalFlights = g.Count(), // Агрегирование
                EarliestFlight = g.Min(f => f.DepartureTime), 
                LatestFlight = g.Max(f => f.DepartureTime) 
            })
            .Where(g => g.TotalFlights >= 2) // Условие
            .Take(3); // Разбиение
            Console.WriteLine("-----------------------------------------------------------------");
            Console.WriteLine($"Использование пяти операторов: ");
            foreach (var group in query)
            {
                Console.WriteLine($"Пункт назначения: {group.Destination}");
                Console.WriteLine($"Общее количество рейсов: {group.TotalFlights}");
                Console.WriteLine($"Самый ранний рейс: {group.EarliestFlight}");
                Console.WriteLine($"Самый поздний рейс: {group.LatestFlight}");
                Console.WriteLine();
            }


            // запрос с оператором Join
            var airports = new List<Airport>
            {
                new Airport("Лондон", "ABC"),
                new Airport("Санкт-Петербург", "DEF"),
                new Airport("Киев", "GHI"),
            };
            var query1 = from airline in flights
                        join airport in airports on airline.Destination equals airport.City
                        select new { airline.FlightNumber, airline.Destination, airport.Code };

            Console.WriteLine("-----------------------------------------------------------------");
            Console.WriteLine($"Использование оператора join: ");
            foreach (var item in query1)
            {
                Console.WriteLine($"Номер: {item.FlightNumber}, Пункт: {item.Destination}, ID: {item.Code}");
            }
        }
        static bool IsSummerMonth(string month)
        {
            return month == "Июнь" || month == "Июль" || month == "Август";
        }

        static bool IsWinterMonth(string month)
        {
            return month == "Декабрь" || month == "Январь" || month == "Февраль";
        }
    }
}
