using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace OOP_lab5
{
    partial class GeometricFigure
    {
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
}
