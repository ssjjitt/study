using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace OOP_lab5
{
    internal abstract class ControlElement : IControl
    {
        protected bool state;
        protected string type;
        protected string content;
        protected int size;

        public void show()
        {
            Console.WriteLine($"Метод show вызван для элемента управления {this}");
        }

        public void input(string cont)
        {
            content = cont;
        }

        public void resize(int sz)
        {
            size = sz;
        }
    }



    internal interface IControl
    {
        void show();

        void input(string cnt);

        void resize(int sz);
    }

    internal class Checkbox : ControlElement
    {
        public Checkbox() { Console.WriteLine("Create Checkbox"); }
    }

    internal class Radiobutton : ControlElement
    {
        public Radiobutton() { Console.WriteLine("Create Radiobutton"); }
    }

    internal class Button : ControlElement
    {
        public Button() { Console.WriteLine("Create Button"); }
    }
}