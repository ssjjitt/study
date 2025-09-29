using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace OOP_lab5
{
    internal class UI
    {
        public List<GeometricFigure> GMlist { get; private set; }
        public static int CurrentCapacity { get; set; }
        public List<ControlElement> CElist { get; private set; }

        public UI()
        {
            CurrentCapacity = 0;

            GMlist = new List<GeometricFigure>();
            CElist = new List<ControlElement>();
        }

        public UI(params object[] obj) : this()
        {
            var lst = obj.ToList();
            foreach (object A in lst)
            {
                if (A is GeometricFigure)
                {
                    GMlist.Add((GeometricFigure)(A));
                }
                if (A is ControlElement)
                {
                    CElist.Add((ControlElement)(A));
                }
            }
            CurrentCapacity = GMlist.Count() + CElist.Count();
        }

        public void Add(params object[] obj)
        {
            var lst = obj.ToList();
            foreach (object A in lst)
            {
                if (A is GeometricFigure)
                {
                    GMlist.Add((GeometricFigure)(A));
                }
                if (A is ControlElement)
                {
                    CElist.Add((ControlElement)(A));
                }
            }
            CurrentCapacity = GMlist.Count() + CElist.Count();
        }

        public void Remove(object A)
        {
            {
                if (A is GeometricFigure)
                {
                    GMlist.Remove((GeometricFigure)(A));
                }
                if (A is ControlElement)
                {
                    CElist.Remove((ControlElement)(A));
                }
            }
            CurrentCapacity = GMlist.Count() + CElist.Count();
        }

        public void show()
        {
            foreach (GeometricFigure A in GMlist)
            {
                Console.WriteLine("метод show для " + A);
            }
            foreach (ControlElement A in CElist)
            {
                Console.WriteLine("метод show для " + A);
            }
        }
    }
}