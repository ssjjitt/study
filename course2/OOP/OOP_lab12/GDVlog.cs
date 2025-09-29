using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace OOP_lab12
{
    class GDVlog
    {
        private string logPath;
        public GDVlog(string logFilePath)
        {
            logPath = logFilePath;
        }
        public void logWrite(string action, string info)
        {
            string logInfo = $"{DateTime.Now} - Action: {action}, Info: {info}";
            using (StreamWriter sw = new StreamWriter(logPath, true))
            {
                sw.WriteLine(logInfo);
            }
        }
        public string logRead()
        {
            using (StreamReader sr = new StreamReader(logPath))
            {
                return sr.ReadToEnd();
            }
        }
        public string logSearch(string srch)
        {
            using (StreamReader streamReader = new StreamReader(logPath))
            {
                string logString = streamReader.ReadToEnd();
                if (logString.Contains(srch))
                {
                    return $"{srch} найден в файле";
                }
                else
                {
                    return "Ничего не найдено!";
                }
            }
        }
    }
}
