using System;

public class Airline
{
    private string destination;
    private int flightNumber;
    private string aircraftType;
    private DateTime departureTime;
    private DayOfWeek dayOfWeek;

    /*поле - только для чтения;*/
    private readonly int id;

    //поле-константу;
    private const string airlineName = "MyAirline";

    /*создайте в классе статическое поле, хранящее количество созданных
    объектов(инкрементируется в конструкторе)*/
    private static int numberOfFlights;

    /*конструкторы*/
    public Airline(string destination, int flightNumber, string aircraftType, DateTime departureTime, DayOfWeek dayOfWeek)
    {
        this.destination = destination;
        this.flightNumber = flightNumber;
        this.aircraftType = aircraftType;
        this.departureTime = departureTime;
        this.dayOfWeek = dayOfWeek;
        this.id = this.GetHashCode();
        numberOfFlights++;
    }

    public Airline(string destination, int flightNumber, string aircraftType, DateTime departureTime)
        : this(destination, flightNumber, aircraftType, departureTime, DayOfWeek.Monday)
    {
    }

    /*статический конструктор*/
    static Airline()
    {
        numberOfFlights = 0;
    }
    /*закрытый конструктор*/
    private Airline()
    {
        destination = "Минск";
        flightNumber = 606;
        aircraftType = "Boeng 707";
        departureTime = new DateTime(2023, 9, 15, 10, 30, 0);
        dayOfWeek = DayOfWeek.Monday;
        numberOfFlights++;
    }
    /*вариант его вызова*/
    public static Airline CreateDefaultAirline()
    {
        return new Airline();
    }

    /*ref и out-параметры*/
    public void UpdateFlightNumber(ref int newFlightNumber)
    {
        flightNumber = newFlightNumber;
    }

    public bool TryGetFlightNumber(out int flightNumber)
    {
        flightNumber = FlightNumber;
        return true;
    }

    public static void PrintClassInfo()
    {
        Console.WriteLine($"Класс Airline. Количество созданных объектов: {numberOfFlights}");
    }

    public void PrintFlightInfo()
    {
        Console.WriteLine($"Пункт назначения: {Destination}");
        Console.WriteLine($"Номер рейса: {FlightNumber}");
        Console.WriteLine($"Тип самолета: {AircraftType}");
        Console.WriteLine($"Время вылета: {DepartureTime}");
        Console.WriteLine($"День недели: {DayOfWeek}");
        Console.WriteLine($"ID: {ID}");
    }

    /*переопределения*/
    public override string ToString()
    {
        return $"Рейс {FlightNumber} - {Destination}";
    }

    public override bool Equals(object obj)
    {
        if (obj == null || GetType() != obj.GetType())
            return false;

        Airline other = (Airline)obj;
        return this.FlightNumber == other.FlightNumber;
    }

    public override int GetHashCode()
    {
        return FlightNumber.GetHashCode();
    }
    public string Destination
    {
        get { return destination; }
        set
        {
            if (!string.IsNullOrEmpty(value))
                destination = value;
        }
    }

    public int FlightNumber
    {
        get { return flightNumber; }
        private set
        {
            if (value > 0)
                flightNumber = value;
        }
    }

    public string AircraftType
    {
        get { return aircraftType; }
        set
        {
            if (!string.IsNullOrEmpty(value))
                aircraftType = value;
        }
    }

    public DateTime DepartureTime
    {
        get { return departureTime; }
        set
        {
            if (value > DateTime.MinValue)
                departureTime = value;
        }
    }

    public DayOfWeek DayOfWeek
    {
        get { return dayOfWeek; }
        set { dayOfWeek = value; }
    }

    public int ID
    {
        get { return id; }
    }
}
