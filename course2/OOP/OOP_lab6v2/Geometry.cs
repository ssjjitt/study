using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace OOP_lab5
{

    internal class Printer
    {
        public void IAmPrinting(GeometricFigure obj)
        {
            Console.WriteLine($" {obj.ToString()}");
        }
    }
    
    partial class GeometricFigure
    {
        protected enum Colors : int
        {
            Red = 1,
            Green,
            Blue,
            Yellow,
            Pink
        }
        protected Colors Color;
        protected static int count = 0;
        public double Area { get; set; }
        public GeometricFigure() 
        {
            count++;
        }
        public void ShowC() 
        {
            Console.WriteLine($"{count}");
        }
        public override string ToString() => $"\nЦвет: {Color}\nКоличество обьектов: {count} \nПлощадь: {Area} \n\n";
        public override int GetHashCode() => count;
        public override bool Equals(object obj) => GetType().Name == obj.ToString();
    }

    internal class Circle : GeometricFigure
    {
        private int Radius { get; set; }
        public Circle(int rad, int color)
           : base()
        {
            if (rad <= 0)
                throw new CircleException("ошибка вызвана попыткой ввести отрицательное число");
            else
            { Radius = rad; }
            Color = (Colors)color;
            Area = (Math.PI) * Radius * Radius;
        }
        private struct very_important
        {
            public void SaySomethingImportant()
            {
                Console.WriteLine("Bruh");
            }
        }
        public override string ToString() => $"круг\nРадиус : {Radius} " + base.ToString();
    }



    sealed internal class Rectangle : GeometricFigure
    {
        private int Side { get; set; }
        private int Side2 { get; set; }
        public Rectangle(int side, int side2, int color)
    : base()
        {
            if (side <= 0 || side2 <=0)
                throw new RectangleException("Ошибка вызвана попыткой ввести отрицательное число", side, side2);
            
            if (side <= 0 || side >= 1000)
                throw new OutException(nameof(side), side, "Некорректное число");

            if (side2 <= 0 || side2 >= 1000)
                throw new OutException(nameof(side2), side2, "Некорректное число");

            if (color < 1 || color > 5)
                throw new ZeroException("Значение цвета принимает неверное значение");
            { 
                Side = side;
                Side2 = side2;
                Color = (Colors)color;
            }
            Area = Side * Side2;
        }
        public override string ToString() => $"квадрат\nСтороны: {Side}, {Side2} " + base.ToString();
    }



    interface ICloneable
    {
        bool DoClone();
    }
    abstract class BaseClone
    {
        public abstract bool DoClone();
    }
    class UserClass : BaseClone, ICloneable
    {
        bool ICloneable.DoClone() // реализация метода
        {
            Console.WriteLine("Успешное клонирование\n");
            return true;
        }
        public override bool DoClone() // переопределение
        {
            Console.WriteLine("Не успешное клонирование\n");
            return false;
        }
    }


    interface IShape
    {
        void Draw();
    }
    abstract class Shape : IShape
    {
        public virtual void Draw()
        {
            Console.WriteLine("Drawing a shape");
        }
    }
    class Sphere : Shape
    {
        public override void Draw()
        {
            Console.WriteLine("Drawing a Sphere");
        }
    }
}