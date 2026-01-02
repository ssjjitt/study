using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PP_lab1
{
    public class C4 : C3
    {
        private int _privateField3;
        private string _privateField4;

        public int PublicField3;
        public string PublicField4;

        protected int ProtectedField3;
        protected string ProtectedField4;

        private int PrivateProperty2
        {
            get { return _privateField3; }
            set { _privateField3 = value; }
        }

        public string PublicProperty2
        {
            get { return _privateField4; }
            set { _privateField4 = value; }
        }

        protected int ProtectedProperty2
        {
            get { return ProtectedField3; }
            set { ProtectedField3 = value; }
        }

        public C4() { }

        public C4(int field1, string field2, int field3, string field4) : base(field1, field2)
        {
            PublicField3 = field3;
            PublicField4 = field4;
        }

        private void PrivateMethod2()
        {
            Console.WriteLine("Пим пим вы вызвали приватный метод");
        }

        public void PublicMethod2()
        {
            Console.WriteLine("Пим пим вы вызвали публичный метод");
        }

        protected void ProtectedMethod2()
        {
            Console.WriteLine("Пим пим вы вызвали защищенный метод");
        }
    }
}
