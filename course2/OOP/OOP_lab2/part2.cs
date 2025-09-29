using System;
public partial class Airline
{
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

