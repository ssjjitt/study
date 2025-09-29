using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Lec03LibN.Interfaces;

namespace Lec03LibN.BonusClasses
{
    public class BonusB2 : IBonus
    {
        public float cost1hour { get; set; }
        public float a { get; set; } // повыш/пониж величина
        public float x { get; set; } // повыш/пониж коэф
        public float calc(float number_hours)
        {
            return (number_hours + a) * cost1hour * x;
        }
        public BonusB2(float cost1hour, float x, float a)
        {
            this.cost1hour = cost1hour;
            this.a = a;
            this.x = x;
        }
    }
}
