using System;

class Program
{
    static void Main(string[] args)
    {

        Airline[] flights = new Airline[]
        {
            new Airline("New York", 101, "Boeing 747", new DateTime(2023, 9, 15, 10, 30, 0), DayOfWeek.Monday),
            new Airline("London", 202, "Airbus A320", new DateTime(2023, 9, 16, 12, 45, 0), DayOfWeek.Tuesday),
            new Airline("Paris", 303, "Boeing 777", new DateTime(2023, 9, 17, 14, 15, 0), DayOfWeek.Wednesday),
            new Airline("Tokyo", 404, "Boeing 787", new DateTime(2023, 9, 18, 16, 30, 0), DayOfWeek.Thursday),
            new Airline("Berlin", 505, "Airbus A330", new DateTime(2023, 9, 19, 18, 15, 0), DayOfWeek.Friday),
        };

        foreach (var flight in flights)
        {
            flight.PrintFlightInfo();
            Console.WriteLine();
        }


        Console.WriteLine("Исходный номер рейса: " + flights[0].FlightNumber);
        int newFlightNumber;
        do
        {
            Console.Write("Введите новый номер рейса: ");
        } while (!int.TryParse(Console.ReadLine(), out newFlightNumber));
        flights[0].UpdateFlightNumber(ref newFlightNumber);
        

        int retrievedFlightNumber; 
        if (flights[0].TryGetFlightNumber(out retrievedFlightNumber))
        {
            Console.WriteLine("Новый номер рейса: " + retrievedFlightNumber);
        }
        else
        {
            Console.WriteLine("Не удалось получить номер рейса.");
        }
        flights[0].PrintFlightInfo();

        
        string destinationToSearch = "London";
        Console.WriteLine($"Список рейсов для пункта назначения '{destinationToSearch}':");
        foreach (var flight in flights)
        {
            if (flight.Destination == destinationToSearch)
            {
                flight.PrintFlightInfo();
                Console.WriteLine();
            }
        }


        DayOfWeek dayOfWeekToSearch = DayOfWeek.Wednesday;
        Console.WriteLine($"Список рейсов для дня недели '{dayOfWeekToSearch}':");
        foreach (var flight in flights)
        {
            if (flight.DayOfWeek == dayOfWeekToSearch)
            {
                flight.PrintFlightInfo();
                Console.WriteLine();
            }
        }


        var flightInfo = new
        {
            Destination = "Los Angeles",
            FlightNumber = 777,
            AircraftType = "Boeing 777",
            DepartureTime = new DateTime(2023, 9, 20, 14, 0, 0),
            DayOfWeek = DayOfWeek.Monday
        };

        Console.WriteLine("Информация о рейсе анонимного типа:");
        Console.WriteLine($"Пункт назначения: {flightInfo.Destination}");
        Console.WriteLine($"Номер рейса: {flightInfo.FlightNumber}");
        Console.WriteLine($"Тип самолета: {flightInfo.AircraftType}");
        Console.WriteLine($"Время вылета: {flightInfo.DepartureTime}");
        Console.WriteLine($"День недели: {flightInfo.DayOfWeek}");
        Console.WriteLine("-----------------------------------------------------");

        Airline defaultAirline = Airline.CreateDefaultAirline();
        Console.WriteLine("Информация о рейсе по умолчанию:");
        Console.WriteLine($"Пункт назначения: {defaultAirline.Destination}");
        Console.WriteLine($"Номер рейса: {defaultAirline.FlightNumber}");
        Console.WriteLine($"Тип самолета: {defaultAirline.AircraftType}");
        Console.WriteLine($"Время вылета: {defaultAirline.DepartureTime}");
        Console.WriteLine($"День недели: {defaultAirline.DayOfWeek}");
        Console.WriteLine("-----------------------------------------------------");

        Console.WriteLine("Equals номера рейса третьего рейса с первым рейсом: " + flights[2].Equals(flights[0]));
        Console.WriteLine("ToString: " + flights[2].ToString());

        Airline.PrintClassInfo();

    }
}
