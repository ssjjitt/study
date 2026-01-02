using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PP_lab1
{
    public class Program
    {
        static void Main(string[] args)
        {
            C1 c1 = new C1();
            c1.PublicField1 = 10;
            c1.PublicProperty = "прив как дела";

            C1 c2 = new C1(30, "мяу");
            c2.PublicProperty = "мяу";
            Console.WriteLine(c2.PublicField1);
            Console.WriteLine(c2.PublicProperty);

            C1 c3 = new C1(c2);
            Console.WriteLine(c3.PublicField1);

            c1.PublicMethod1();
            Console.WriteLine(c1.PublicMethod2(c1.PublicProperty));

            Console.WriteLine("====================");

            C2 с4 = new C2();

            с4.PublicField1 = 10;
            с4.PublicProperty = "пим";

            с4.PublicMethod1();
            Console.WriteLine(с4.PublicMethod2("Прив"));
            
            с4.Property = 100;
            с4.Method("Привяо интерфейс I1");
            с4.Event += (sender, e) => Console.WriteLine("событие!");
            C2 c21 = new C2();
            Console.WriteLine(c21[3]); // 99


            Console.WriteLine("====================");

            C4 c5 = new C4(10, "Pim", 20, "pimpim");
            c5.PublicProperty = "ого блин класс";
            Console.WriteLine(c5.PublicField1);
            Console.WriteLine(c5.PublicProperty);
            c5.PublicField3 = 20;
            c5.PublicProperty2 = "meow";
            c5.PublicMethod1();
        }
    }
}
