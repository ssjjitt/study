using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace OOP_lab5
{
    class GeometryException : Exception
    {
        public GeometryException(string message) : base(message) { }
    }
    class CircleException : GeometryException
    {
        public CircleException(string message) : base(message) { }
    }
    class RectangleException : ArgumentException
    {
        public int Value { get; }
        public int Value2 { get; }
        public RectangleException(string message, int val, int val2) : base(message) {
            if (val <= 0 && val2 <= 0)
            {
                Value = val;
                Value2 = val2;
                throw this;
            }
            else if (val <= 0)
            {
                Value = val;
            }
            else if (val2 <= 0)
            {
                Value2 = val2;
            }
        }
    }
    class OutException : ArgumentOutOfRangeException
    {
        public int Value { get; }
        public int Value2 { get; }
        public OutException(string paramName, object actualValue, string message) : base(paramName, actualValue, message)
        {
        }
    }
    class ZeroException : DivideByZeroException
    {
        public int Value { get; }
        public int Value2 { get; }
        public ZeroException(string message) : base(message)
        {
        }
    }
}