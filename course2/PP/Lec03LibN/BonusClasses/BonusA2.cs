using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Lec03LibN.Interfaces;

namespace Lec03LibN.BonusClasses
{
    public class BonusA2 : IBonus
    {
        // (wH + a) * cH
        public float cost1hour { get; set; } // cH
        public float a { get; set; }
        public float calc(float number_hours)
        {
            return (number_hours + a) * cost1hour; // отработанные часы + величина повышения/понижения * стоимость часа
        }
        public BonusA2(float cost1hour, float a)
        {
            this.cost1hour = cost1hour;
            this.a = a;
        }
    }
}
