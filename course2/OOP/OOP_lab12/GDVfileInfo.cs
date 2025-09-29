using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace OOP_lab12
{
    class GDVfileInfo
    {
        private GDVlog log;

        public GDVfileInfo(GDVlog log)
        {
            this.log = log;
        }

        public void fullPath(string filePath)
        {
            log.logWrite("fullPath", $"Path: {filePath}");

            string fullPath = Path.GetFullPath(filePath);

            Console.WriteLine($"Путь: {fullPath}");
        }

        public void fileInfo(string filePath)
        {
            log.logWrite("fileInfo", $"Path: {filePath}");

            FileInfo fileInfo = new FileInfo(filePath);

            Console.WriteLine($"Имя: {fileInfo.Name}");
            Console.WriteLine($"Размер: {fileInfo.Length} bytes");
            Console.WriteLine($"Расширение: {fileInfo.Extension}");
        }

        public void fileDates(string filePath)
        {
            log.logWrite("fileDates", $"Path: {filePath}");

            FileInfo fileInfo = new FileInfo(filePath);

            Console.WriteLine($"Дата создания: {fileInfo.CreationTime}");
            Console.WriteLine($"Последнее обновление: {fileInfo.LastWriteTime}");
        }
    }
}
