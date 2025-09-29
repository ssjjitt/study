using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab6Lib
{
    public class Publisher : IPublisher
    {
        public int State { get; set; } = -0;
        private List<ISubscriber> _observers = new List<ISubscriber>();
        private string eventname;
        public string Eventname { get => eventname; }

        public Publisher(string eventname) {
            this.eventname = eventname;
        }

        public void subscribe(ISubscriber subscriber)
        {
            Console.WriteLine($"Subscribe: {eventname}.");
            this._observers.Add(subscriber);
        }

        public bool unsubscribe(ISubscriber subscriber)
        {
            bool unsubscribe = this._observers.Remove(subscriber);
            Console.WriteLine($"Unsubscribe: {eventname}.");
            return unsubscribe;
        }

        public int notify()
        {
            int k = 0;
            foreach (var observer in _observers)
            {
                k++;
                observer.Update($"{eventname}");
            }
            return k;
        }

        public void SomeBusinessLogic()
        {
            Console.WriteLine("\nI'm doing something important.");
            this.State = new Random().Next(0, 10);

            Thread.Sleep(15);

            Console.WriteLine("My state has just changed to: " + this.State);
            this.notify();
        }
    }
}
