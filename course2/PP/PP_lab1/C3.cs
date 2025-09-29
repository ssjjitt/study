using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PP_lab1
{
    public class C3
    {
        private int _privateField1;
        private string _privateField2;

        public int PublicField1;
        public string PublicField2;

        protected int ProtectedField1;
        protected string ProtectedField2;

        private int PrivateProperty
        {
            get { return _privateField1; }
            set { _privateField1 = value; }
        }

        public string PublicProperty
        {
            get { return _privateField2; }
            set { _privateField2 = value; }
        }

        protected int ProtectedProperty
        {
            get { return ProtectedField1; }
            set { ProtectedField1 = value; }
        }

        public C3() { }

        public C3(int field1, string field2)
        {
            PublicField1 = field1;
            PublicField2 = field2;
        }

        private void PrivateMethod1()
        {
            Console.WriteLine("Пим пим вы вызвали приватный метод");
        }

        public void PublicMethod1()
        {
            Console.WriteLine("Пим пим вы вызвали публичный метод");
        }

        protected void ProtectedMethod1()
        {
            Console.WriteLine("Пим пим вы вызвали защищенный метод");
        }
    }
}
