using Lec03LibN.BonusClasses;
using Lec03LibN.Interfaces;
using System;

namespace Lec03LibN.FactoryClasses
{
    public class L1Factory : IFactory
    {
        public IBonus getA(float cost1hour)
        {
            return new BonusA(cost1hour);
        }

        public IBonus getB(float cost1hour, float x)
        {
            return new BonusB(cost1hour, x);
        }

        public IBonus getC(float cost1hour, float x, float y)
        {
            return new BonusC(cost1hour, x, y);
        }
    }
}
