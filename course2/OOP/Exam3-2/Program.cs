using System;

namespace Exam3_2
{
    class Location
    {
        private string lat;
        private string lon;
        private string speed;
        public string Lat {  get { return lat; } set {  lat = value; } }
        public string Lon {  get { return lon; } set {  lon = value; } }
        public string Speed {  get { return speed; } set {  speed = value; } }
    }
    class Taxi
    {
        private string number;
        public Location Location { get; set; }
        private enum status
        {
            busy = 1,
            free = 2,
        }
    }
    class Park<T>
    {
        private List<T> lists;
        public Park()
        {
            lists = new List<T>();
        }
        public void Add(T item)
        {
            lists.Add(item);
        }
        public void Remove(T item)
        {
            lists.Remove(item);
        }
        public void Clear()
        {
            lists.Clear();
        }
        public bool Find(Predicate<T> predicate)
        {
            return lists.Exists(predicate);
        }
        public List<T> GetAll()
        {
            return lists;
        }
       
    }
    class Program
    {
        static double Calc(Location location, Location myLoc)
        {
            double res = 0;
            if (location == null)
            {
                res = 0;
            }
            else if (myLoc == null) 
            {
                res = 0;
            }
            else
            {
                double res1 = Convert.ToDouble(myLoc.Lon) - Convert.ToDouble(location.Lon);
                double res2 = Convert.ToDouble(myLoc.Lat) - Convert.ToDouble(location.Lat);
                double res3 = Math.Pow(res1, 2);
                double res4 = Math.Pow(res2, 2);
                double res5 = res3 + res4;
                res = Math.Sqrt(res5);
            }
            return res;
        }
        static void Main()
        {
            Park<Taxi> uber = new Park<Taxi>();
            Taxi taxi = new Taxi { Location = new Location { Lat = "40,13", Lon = "321,23", Speed = "132" } };
            Taxi taxi1 = new Taxi { Location = new Location { Lat = "57,13", Lon = "111,23", Speed = "100" } };
            Taxi taxi2 = new Taxi { Location = new Location { Lat = "0,13", Lon = "-11,23", Speed = "120" } };
            Taxi taxi3 = new Taxi { Location = new Location { Lat = "-32,12", Lon = "23,23", Speed = "20" } };
            uber.Add(taxi);
            uber.Add(taxi1);
            uber.Add(taxi2);
            uber.Add(taxi3);
            List<Taxi> taxis = uber.GetAll();
            foreach(Taxi tax in taxis)
            {
                Console.WriteLine("Lat: " + tax.Location.Lat + " Lon: " + tax.Location.Lon + " Speed: " + tax.Location.Speed);
            }
            Location myLocation = new Location() { Lat = "0", Lon = "0", Speed = "0" };
            double distance = double.MaxValue;
            Taxi distTaxi = null;
            foreach(Taxi tax in taxis)
            {
                double dist = Calc(tax.Location, myLocation);
                if(dist < distance)
                {
                    distance = dist;
                    distTaxi = tax;
                }
            }
            var sortTax = taxis.OrderBy(tax => Calc(tax.Location, myLocation));
            Console.WriteLine("Отсортированные таксы: ");
            foreach (Taxi tax in sortTax)
            {
                Console.WriteLine("Lat: " + tax.Location.Lat + " Lon: " + tax.Location.Lon + " Speed: " + tax.Location.Speed);
            }
            Console.WriteLine("Ближайшая такса: ");
            Console.WriteLine("Lat: " + distTaxi.Location.Lat + " Lon: " + distTaxi.Location.Lon + " Speed: " + distTaxi.Location.Speed);
            using (StreamWriter streamWriter = new StreamWriter("../../../tax.txt"))
            {
                streamWriter.WriteLine("Lat: " + distTaxi.Location.Lat + " Lon: " + distTaxi.Location.Lon + " Speed: " + distTaxi.Location.Speed);
            }
        }
    }
}
