using Lec03LibN.FactoryClasses;
using Lec03LibN.Interfaces;
using System;

namespace Lec03LibN
{
    static public partial class Lec03BLib
    {
        static public IFactory getL1()
        {
            return new L1Factory();
        }
        static public IFactory getL2(float a)
        {
            return new L2Factory(a);
        }
        static public IFactory getL3(float a, float b)
        {
            return new L3Factory(a, b);
        }
    }
}
