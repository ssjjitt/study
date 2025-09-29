using Lec03LibN.BonusClasses;
using Lec03LibN.Interfaces;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lec03LibN.FactoryClasses
{
    internal class L3Factory : IFactory
    {
        public float A { get; set; }
        public float B { get; set; }
        public IBonus getA(float cost1hour)
        {
            return new BonusA3(cost1hour, A, B);
        }

        public IBonus getB(float cost1hour, float x)
        {
            return new BonusB3(cost1hour, x, B, A);
        }

        public IBonus getC(float cost1hour, float x, float y)
        {
            return new BonusC3(cost1hour, A, B, x, y);
        }

        public L3Factory(float a, float b)
        {
            A = a;
            B = b;
        }
    }
}
