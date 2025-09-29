using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace OOP_lab5
{
    class Program
    {
       
        private static void Main(string[] args)
        {
            var sqr = new Square(1, 2, 2);
            var crc = new Circle(3, 1);
            var bat = new Button();
            var radbat = new Radiobutton();
            var UI = new UI(sqr, crc);
            UI.Add(bat);
            UI.Add(radbat);
            UI.show();
            var class3 = new Class3();
            class3.MyMethod();


            Console.WriteLine(Controller.GetFullArea(UI));
            Controller.CreateFromTextFile(UI);

            UI.show();
            Console.WriteLine(Controller.GetCountOfElements(UI));



            UserClass a = new UserClass();
            a.DoClone();    // из класса
            ICloneable Ia = a;
            Ia.DoClone();   // из интерфейса



            Shape circle = new Sphere();
            Shape rectangle = new Rectangle();
            DrawShape(circle);
            DrawShape(rectangle);
        }
        static void DrawShape(IShape shape) // Внутри метода производится идентификация типов объектов
        {
            if (shape is Sphere)
            {
                Sphere circle = shape as Sphere;
                circle.Draw();
            }
            else if (shape is Rectangle)
            {
                Rectangle rectangle = shape as Rectangle;
                rectangle.Draw();
            }
        }
    }
}