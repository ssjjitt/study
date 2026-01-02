using System;
using Lec03LibN.Interfaces;

namespace Lec03LibN
{
    public class Employee
    {
        public IBonus bonus {  get; set; }
        public Employee(IBonus bonus) {
            this.bonus = bonus;
        }
        public float calcBonus(float number_hours)
        {
            return bonus.calc(number_hours);
        }
    }
}
