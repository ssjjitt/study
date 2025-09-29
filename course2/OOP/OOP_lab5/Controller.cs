using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace OOP_lab5
{
    internal static class Controller
    {
        public static int GetCountOfElements(UI UI)
        {
            return UI.CurrentCapacity;
        }

        public static double GetFullArea(UI UI)
        {
            double sum = 0;
            foreach (GeometricFigure A in UI.GMlist)
            {
                sum += A.Area;
            }
            return sum;
        }



        public static void CreateFromTextFile(UI UI)
        {
            string text;
            var constr = new int[3];
            int z = 0;
            string[] lines = System.IO.File.ReadAllLines(@"E:\уник\c\OOP_lab5\INfile.txt");
            for (int i = 0; i < lines.Length; i++)
            {
                if (lines[i].Contains("Circle"))
                {
                    z = 0;
                    text = lines[i + 1];
                    string[] strings = text.Split(' ');
                    foreach (string parm in strings)
                    {
                        bool isNumber = int.TryParse(parm, out int numericValue);
                        if (isNumber)
                        {
                            constr[z++] = Convert.ToInt32(parm);
                        }
                    }

                    UI.Add(new Circle(constr[0], constr[1]));
                }
                if (lines[i].Contains("Square"))
                {
                    z = 0;
                    text = lines[i + 1];
                    string[] strings2 = text.Split(' ');
                    foreach (string parm in strings2)
                    {
                        if (int.TryParse(parm, out int _))
                        {
                            constr[z++] = Convert.ToInt32(parm);
                        }
                    }

                    UI.Add(new Square(constr[0], constr[1], constr[2]));
                }
            }
        }
    }
}