using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace OOP_lab5
{
    public class Class1
    {
        public virtual int MyMethod() { Console.WriteLine("Метод наследуется"); return 0; }


    }
    public class Class2 : Class1
    {
        public sealed override int MyMethod() { Console.WriteLine("Метод наследуется у square"); return 0; }
    }
    public class Class3 : Class2
    
    {
        public Class3() { }
    }

    internal class Printer
    {
        public void IAmPrinting(GeometricFigure obj)
        {
            Console.WriteLine($" {obj.ToString()}");
        }
    }
    // Абстрактный класс
    partial class GeometricFigure
    {
        // перечисление
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
        public GeometricFigure() // конструктор
        {
            count++;
            // класс с методом 
        }
        public void ShowC() // вывод количества
        {
            Console.WriteLine($"{count}");
        }
        // переопределение методов object
        public override string ToString() => $"\nЦвет: {Color}\nКоличество обьектов: {count} \nПлощадь: {Area} \n\n";
        public override int GetHashCode() => count;
        public override bool Equals(object obj) => GetType().Name == obj.ToString();
    }



    sealed class Circle : GeometricFigure // sealed(ЗАПЕЧАТАННЫЙ КЛАСС) - не может быть унаследован 
    {
        private int Radius { get; set; }
        private struct very_important // структура
        {
            public void SaySomethingImportant()
            {
                Console.WriteLine("Bruh");
            }
        }
        public Circle(int rad, int color) // вызов конструктора класса Circle
            : base() // вызов конструктора базового класса и передача управления без аргументов
        {
            Radius = rad;
            Color = (Colors)color;
            Area = (Math.PI) * Radius * Radius;
        }
        public override string ToString() => $"круг\nРадиус : {Radius} " + base.ToString();
    }



    sealed internal class Square : GeometricFigure
    {
        private int Side { get; set; }
        private int Side2 { get; set; }
        public Square(int side, int side2, int color)
    : base()
        {
            Side = side;
            Side2 = side2;
            Color = (Colors)color;
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
    class Rectangle : Shape
    {
        public override void Draw()
        {
            Console.WriteLine("Drawing a rectangle");
        }
    }
}