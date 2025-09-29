using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Lec03LibN.Interfaces;

namespace Lec03LibN.BonusClasses
{
    public class BonusC2 : IBonus
    {
        public float cost1hour { get; set; }
        public float x { get; set; } // повыш/пониж коэф
        public float a { get; set; } // повыш/пониж коэф
        public float y { get; set; } // величина повыш/пониж
        public float calc(float number_hours)
        {
            return (number_hours + a) * cost1hour * x + y;
        }
        public BonusC2(float cost1hour, float a, float x, float y)
        {
            this.cost1hour = cost1hour;
            this.x = x;
            this.a = a;
            this.y = y;
        }
    }
}
