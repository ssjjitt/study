using Lec03LibN.BonusClasses;
using Lec03LibN.Interfaces;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lec03LibN.FactoryClasses
{
    public class L2Factory : IFactory
    {
        public float A { get; set; }
        public IBonus getA(float cost1hour)
        {
            return new BonusA2(cost1hour, A);
        }

        public IBonus getB(float cost1hour, float x)
        {
            return new BonusB2(cost1hour, x, A);
        }

        public IBonus getC(float cost1hour, float x, float y)
        {
            return new BonusC2(cost1hour, A, x, y);
        }

        public L2Factory(float a)
        {
            A = a;
        }
    }
}

