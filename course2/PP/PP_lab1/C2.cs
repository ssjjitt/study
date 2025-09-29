using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PP_lab1
{
    public class C2 : I1
    {
        private const int _privateConst1 = 1;
        private const string _privateConst2 = "хай герл";

        public const double PublicConst1 = 3.14;
        public const bool PublicConst2 = true;

        protected const int ProtectedConst1 = 10;
        protected const string ProtectedConst2 = "бай герл";

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

        public C2() { }

        public C2(int field1, string field2)
        {
            PublicField1 = field1;
            PublicField2 = field2;
        }

        public C2(C2 other)
        {
            PublicField1 = other.PublicField1;
            PublicField2 = other.PublicField2;
        }

        private void PrivateMethod1()
        {
            Console.WriteLine("Пим пим вы вызвали приватный метод");
        }

        private string PrivateMethod2(int param)
        {
            return $"Пим пим вы вызвали второй приватный метод с параметрами: {param}";
        }

        public void PublicMethod1()
        {
            Console.WriteLine("Пим пим вы вызвали публичный метод");
        }

        public string PublicMethod2(string param)
        {
            return $"Пим пим вы вызвали второй публичный метод: {param}";
        }

        protected void ProtectedMethod1()
        {
            Console.WriteLine("Пим пим вы вызвали защищенный метод");
        }

        protected string ProtectedMethod2(int param)
        {
            return $"Пим пим вы вызвали второй защищенный метод: {param}";
        }

        public int Property { get; set; }

        public void Method(string param)
        {
            Console.WriteLine($"Пим пим вы вызвали метод интерфейса: {param}");
        }

        public event EventHandler Event;

        public int this[int index]
        {
            get { return index * 33; }
            set { Console.WriteLine("Установлено значение " + value + " для индекса " + index); }
        }

    }
}
