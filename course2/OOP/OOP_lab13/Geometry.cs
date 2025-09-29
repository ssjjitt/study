using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Text.Json.Serialization;
using System.Threading.Tasks;
using System.Xml.Serialization;

namespace OOP_lab13
{
    public class Printer
    {
        public void IAmPrinting(GeometricFigure obj)
        {
            Console.WriteLine($" {obj.ToString()}");
        }
    }
    [Serializable]
    public class GeometricFigure
    {
        public enum Colors : int
        {
            Red = 1,
            Green,
            Blue
        }
        [JsonIgnore]
        public Colors Color;
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

    [Serializable]
    public class Circle : GeometricFigure  
    {
        private int Radius { get; set; }
        public Circle()
        {
        }
        public Circle(int rad, int color) 
            : base() 
        {
            Radius = rad;
            Color = (Colors)color;
            Area = (Math.PI) * Radius * Radius;
        }
        public override string ToString() => $"круг\nРадиус : {Radius} " + base.ToString();
    }

    [Serializable]
    public class Square : GeometricFigure
    {
        private int Side { get; set; }
        private int Side2 { get; set; }
        public Square()
        {
        }
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
        bool ICloneable.DoClone() 
        {
            Console.WriteLine("Успешное клонирование\n");
            return true;
        }
        public override bool DoClone() 
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