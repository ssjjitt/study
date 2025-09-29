using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace OOP_lab10
{
    public class Airport
    {
        public string City { get; set; }
        public string Code { get; set; }

        public Airport(string city, string code)
        {
            City = city;
            Code = code;
        }
    }
}
