using System;
using System.Diagnostics.Metrics;

namespace Exam3_3
{
    class SomeString
    {
        private string str;
        public string Str { get { return str; } set { str = value; } }
        public SomeString(string value)
        {
            this.str = value;
        }
        public override bool Equals(object? obj)
        {
            if (obj is SomeString some)
            {
                return this.str.Length == some.str.Length && this.str[0] == some.str[0] && this.str[this.str.Length - 1] == some.str[some.str.Length - 1];
            }
            return base.Equals(obj);
        }
        public override int GetHashCode()
        {
            return this.str.GetHashCode();
        }
        static public string operator +(SomeString? x, char y) 
        {
            x.str = x.str + "новая гоd";
            return string.Concat(x.str, y); 
        }
        static public string operator -(SomeString? x, SomeString? y)
        {
            return x.str.Remove(x.str.Length);
        }
    }
    class MyPersonalSuperMegaComparer : IComparer<SomeString>
    {
        public int Compare(SomeString? x, SomeString? y)
        {
            return x.Str.CompareTo(y.Str);
        }
    }
    static class StringExtensions
    {
        public static int CharCount(this SomeString str)
        {
            int counter = 0;
            for (int i = 0; i < str.Str.Length; i++)
            {
                if (str.Str[i] == ' ')
                    counter++;
            }
            return counter;
        }
        public static string RemovePunctuation(this SomeString str)
        {
            return new string(str.Str.Where(c => !(".,!;:-".Contains(c))).ToArray());
        }
    }
    /*
     public static string RemoveVowels(this string str)
    {
        return new string(str.Where(c => !("AEIOUaeiouАЕЁИОУЫЭЮЯаеёиоуыэюя".Contains(c))).ToArray());
    }
     */
    class Program
    {
        static void Main(string[] args)
        {
            SomeString s1 = new SomeString("пиздос");
            SomeString s2 = new SomeString("пиздец");
            SomeString s3 = new SomeString("пиздас");
            SomeString s4 = new SomeString("пиздос");
            Console.WriteLine(s1.Equals(s2)); 
            Console.WriteLine(s1.Equals(s3));
            MyPersonalSuperMegaComparer myPersonalSuperMegaComparer = new MyPersonalSuperMegaComparer();
            Console.WriteLine(myPersonalSuperMegaComparer.Compare(s1,s3));
            Console.WriteLine(myPersonalSuperMegaComparer.Compare(s1,s4));

            Console.WriteLine(s1 + 'А');
            Console.WriteLine(s1 - s1);

            SomeString s5 = new SomeString("п из до с");
            Console.WriteLine(s5.CharCount());
            SomeString s6 = new SomeString("п !из -до .с");
            Console.WriteLine(s6.RemovePunctuation());

            int count = 0;
            SomeString[] someStrings = {
               s5, s6
            };
            foreach (SomeString s in someStrings)
            {
                count += s.Str.Where(c => c == ' ').Count();
            }
            Console.WriteLine(count);
            // на запись в файлы похуй, у меня новая года
        }
    }
}