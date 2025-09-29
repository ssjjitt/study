using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;

namespace OOP_lab5
{
    public class Logger
    {
        public static void LogErrorinFile(Exception e)
        {
            var str = $"Time: {DateTime.Now}" + "\n" + $"Info: {e.GetType()} - {e.Message}\n";
            File.AppendAllText(@"E:\уник\c\OOP_lab6\log.txt", str);
        }

        public static void LogErrorinConsole(Exception e)
        {
            Console.WriteLine("LOGGER");
            Console.WriteLine($"Time: {DateTime.Now}");
            Console.WriteLine($"Info: {e.GetType()} - {e.Message}");
        }
    }
}