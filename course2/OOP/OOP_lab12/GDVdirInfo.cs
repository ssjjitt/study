using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace OOP_lab12
{
    class GDVdirInfo
    {
        private GDVlog log;

        public GDVdirInfo(GDVlog log)
        {
            this.log = log;
        }

        public void fileCount(string directoryPath)
        {
            log.logWrite("fileCount", $"Path: {directoryPath}");

            int fileCount = Directory.GetFiles(directoryPath).Length;

            Console.WriteLine($"\nДиректория: {directoryPath}");
            Console.WriteLine($"Количество: {fileCount}");
        }

        public void createTime(string directoryPath)
        {
            log.logWrite("createTime", $"Path: {directoryPath}");

            DirectoryInfo directoryInfo = new DirectoryInfo(directoryPath);

            Console.WriteLine($"Время создания: {directoryInfo.CreationTime}");
        }

        public void subdirectoryCount(string directoryPath)
        {
            log.logWrite("subdirectoryCount", $"Path: {directoryPath}");

            string[] subdirectoryCount = Directory.GetDirectories(directoryPath);
            Console.WriteLine("Список поддиректориев: ");
            foreach(string subdirectory in subdirectoryCount) {
                Console.WriteLine(subdirectory);
            }

            Console.WriteLine($"Количество поддиректориев: {subdirectoryCount.Length}");
        }

        public void parentDirectories(string directoryPath)
        {
            log.logWrite("parentDirectories", $"Path: {directoryPath}");

            DirectoryInfo directoryInfo = new DirectoryInfo(directoryPath);

            Console.WriteLine("Родительские директории:");

            DirectoryInfo parentDirectory = directoryInfo.Parent;
            while (parentDirectory != null)
            {
                Console.WriteLine(parentDirectory.FullName);
                parentDirectory = parentDirectory.Parent;
            }
        }
    }
}
