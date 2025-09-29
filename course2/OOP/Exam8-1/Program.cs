using System;
using System.Collections;
using System.Collections.Generic;
using System.Runtime.InteropServices;

namespace Exam8_1
{
    class Item { 
        public string Name { get; set; }
        public int ID { get; set; }
        public double Price { get; set; }
        public Item(string name, int id, double price)
        {
            this.Name = name;
            this.ID = id;
            this.Price = price;
        }
        public override string ToString()
        {
            return $"Name: {Name} \nID: {ID} \nPrice: {Price}";
        }
        static public Item operator +(Item it, int add) {
            
            return new Item(it.Name, it.ID, it.Price + add);
        }
        static public Item operator -(Item it, int sale)
        {
            return new Item(it.Name, it.ID, it.Price - sale);
        }
    }
    class Shop
    {
        Queue<Item> queue = new Queue<Item>();
        public void AddElem(Item item)
        {
            queue.Enqueue(item);
        }
        public void RemoveElem()
        {
            queue.Dequeue();
        }
        public void Clear()
        {
            queue.Clear();
        }
        public Queue<Item> GetQueue()
        {
            return queue;
        }
    }
    class Manager
    {
        public delegate void SaleDelegatHandler(string message);
        public event SaleDelegatHandler? SaleEvent;
        public Item Sale(Item it, int sale)
        {
            SaleEvent?.Invoke($"скидончик {sale}");
            return it - sale;
        }
    }
    class Program
    {
        static void Main()
        {
            Item item = new Item("Ноутбук", 1, 123.5);
            Item item1 = new Item("Телефон", 2, 100);
            Item item2 = new Item("Провод USB", 3, 11.9);
            Item item3 = new Item("Мышь", 4, 15.3);
            Item item4 = new Item("Клавиатура", 5, 132.23);
            Shop s = new Shop();
            s.AddElem(item);
            s.AddElem(item1);
            s.AddElem(item2);
            s.AddElem(item3);
            s.AddElem(item4);
            Item item6 = new Item("Ррр", 4, 3);
            Item item7 = new Item("Ррр", 5, 23);
            s.AddElem(item6);
            s.AddElem(item7);
            Queue<Item> q = s.GetQueue();
            foreach(Item it in q)
            {
                Console.WriteLine(it.ToString());
            }
            
            Item operatorsItem = new Item("Хуй", 6, 11);
            int extraprice = 23;
            int sale = 3;
            Console.WriteLine("операторы: ");
            Console.WriteLine(operatorsItem + extraprice); // условие не дочитала да поебать мне 
            Console.WriteLine(operatorsItem - sale);
;
            Console.WriteLine("делегаты события: ");
            Item manItem = new Item("Пизда", 7, 110);
            int superMegaSale = (int)(manItem.Price / 2);
            Manager manager = new Manager();
            manager.SaleEvent += DisplayMessage;
            manItem = manager.Sale(manItem, superMegaSale);
            Console.WriteLine("новая цена ахуеть не встать: " + manItem.Price);

            string name = "Ррр";
            Console.WriteLine("linq: " + q.Where(item => item.Name == name).Sum(item => item.Price));
        }
        static void DisplayMessage(string message) => Console.WriteLine(message);
    }
}
