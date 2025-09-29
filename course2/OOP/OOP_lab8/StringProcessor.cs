using System;
using System.Linq;

namespace OOP_lab8
{
    public class StringProcessor // Создайте пять методов пользовательской обработки строки
    {
        public static string RemovePunctuation(string input) =>
            new string(input.ToCharArray().Where(c => !char.IsPunctuation(c)).ToArray());

        public static string AddSymbols(string input, string symbols) => input + symbols;

        public static string ToUpperCase(string input) => input.ToUpper();

        public static string RemoveExtraSpaces(string input) =>
            string.Join(" ", input.Split(' ', StringSplitOptions.RemoveEmptyEntries));

        public static string CustomMethod(string input) =>
             new string(input.Where(c => !"AEIOUaeiouаеёиоуыэюяАЕЁИОУЫЭЮЯ".Contains(c)).ToArray());
    }
}
