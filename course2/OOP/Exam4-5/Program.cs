using System;
using System.Collections.Generic;
using System.Text.Json;

namespace Exam4_5
{
    interface INumber
    {
        int Number { get; set; }
    }
    class Bill : INumber
    {
        private int number;
        public int Number
        {
            get
            {
                return number;
            }
            set
            {
                if (value <= 0)
                {
                    throw new ArgumentException();
                }
                else if (value == 5 || value == 10 || value == 20 || value == 50 || value == 100)
                {
                    number = value;
                }
                else
                {
                    throw new ArgumentException();
                }
            }
        }
    }
    class ToMuchMoney : Exception {
        public ToMuchMoney(string message)
            : base(message) { }
    }
    class NoBillInWallet : Exception
    {
        public NoBillInWallet(string message)
            : base(message) { }
    }
    class Wallet<T> where T : Bill
    {
        List<Bill> list;
        public Wallet()
        {
            list = new List<Bill>();
        }
        public void Add(Bill bill)
        {
            if (list.Count > 0)
            {
                int amount = list.Sum(b => b.Number); 
                if (amount + bill.Number > 200)
                {
                    throw new ToMuchMoney("денег дохуя у тя");
                }
            }
            list.Add(bill);
        }
        public void Remove()
        {
            Bill remBill = list.OrderBy(b => b.Number).FirstOrDefault(); 
            if (remBill == null)
            {
                throw new NoBillInWallet("ноль деняк");
            }
            list.Remove(remBill);
        }
        public List<Bill> GetAll()
        {
            return list;
        }
    }
    class Program
    {
        static void Main(string[] args)
        {
            Bill b1 = new Bill() { Number = 50 };
            Bill b2 = new Bill() { Number = 20 };
            Bill b3 = new Bill() { Number = 5 };
            Bill b5 = new Bill() { Number = 5 };
            Bill b6 = new Bill() { Number = 5 };
            Bill b4 = new Bill() { Number = 100 };
            Wallet<Bill> wallet = new Wallet<Bill>();
            List<Bill> listt = wallet.GetAll();
            wallet.Add(b1);
            wallet.Add(b2);
            wallet.Add(b3);
            wallet.Add(b4);
            wallet.Add(b5);
            wallet.Add(b6);
            Console.WriteLine();
            foreach(Bill b in listt)
            {
                Console.WriteLine(b.Number);
            }
            wallet.Remove();

            Console.WriteLine();
            foreach (Bill b in listt)
            {
                Console.WriteLine(b.Number);
            }
            Console.WriteLine();
            var counts = listt.GroupBy(b => b.Number).ToDictionary(g => g.Key, g => g.Count());
            foreach (var count in counts)
            {
                Console.WriteLine($"{count.Key}: {count.Value}");
            }
            string json = JsonSerializer.Serialize(listt);
            string path = "../../../listt.json";
            File.WriteAllText(path, json);
        }
    }
}