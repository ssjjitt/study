using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Lec03LibN.Interfaces;

namespace Lec03LibN.BonusClasses
{
    public class BonusA : IBonus
    {
        // wH*cH
        public float cost1hour { get; set; } // cH
        public float calc(float number_hours /* wH */)
        {
            return (number_hours) * cost1hour; 
        }
        public BonusA(float cost1hour)
        {
            this.cost1hour = cost1hour;
        }
    }
}
