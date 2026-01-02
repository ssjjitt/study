using System;

namespace Lec03LibN.Interfaces
{
    public interface IFactory
    {
        IBonus getA(float cost1hour);
        IBonus getB(float cost1hour, float x);
        IBonus getC(float cost1hour, float x, float y);
    }
}