using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Lec03LibN.Interfaces;

namespace Lec03LibN.BonusClasses
{
    public class BonusA3 : IBonus
    {
        // (wH + a) * (cH + b)
        public float cost1hour { get; set; } // cH
        public float a { get; set; }
        public float b { get; set; }
        public float calc(float number_hours)
        {
            return (number_hours + a) * (cost1hour + b); // отработанные часы + величина повышения/понижения * стоимость часа
        }
        public BonusA3(float cost1hour, float a, float b)
        {
            this.cost1hour = cost1hour;
            this.a = a;
            this.b = b;
        }
    }
}
