using System;
using System.IO;

namespace OOP_lab12
{
    class Program
    {
        static void Main(string[] args)
        {
            // 1
            GDVlog log = new GDVlog(@"e:\уник\c\OOP_lab12\GDVlog.txt");
            log.logWrite("logWrite", "Файл: GDVlog.txt, Путь: e:/уник/c/OOP_lab12/GDVlog.txt");
            string logRead = log.logRead();
            // Console.WriteLine("Прочитанное из файла: " + logRead);
            string search = "logWrite";
            string searchRes = log.logSearch(search);
            Console.WriteLine("Результат поиска: " + searchRes + "\n");
            // 2
            GDVdiskInfo diskInfo = new GDVdiskInfo(log);
            diskInfo.freeDisk("C:");
            diskInfo.fileSystem("E:");
            diskInfo.driveInfo();
            // 3
            GDVfileInfo fileInfo = new GDVfileInfo(log);
            string filePath = @"e:\уник\c\OOP_lab12\GDVlog.txt";
            fileInfo.fullPath(filePath);
            fileInfo.fileInfo(filePath);
            fileInfo.fileDates(filePath);
            // 4
            GDVdirInfo dirInfo = new GDVdirInfo(log);
            string directoryPath = @"e:\уник\c";
            dirInfo.fileCount(directoryPath);
            dirInfo.createTime(directoryPath);
            dirInfo.subdirectoryCount(directoryPath);
            dirInfo.parentDirectories(directoryPath);
            // 5
            GDVFileManager fileManager = new GDVFileManager(log);
            string diskName = @"e:\уник\c\OOP_lab12";
            fileManager.GetDiskContents(diskName);
            string sourceDirectory = diskName;
            string targetDirectory = Path.Combine(diskName, "GDVInspect");
            string extension = "txt";
            fileManager.CopyFilesByExtension(sourceDirectory, targetDirectory, extension);
            string archivePath = Path.Combine(diskName, "GDVInspect", "archive.zip");
            fileManager.CreateArchive(Path.Combine(diskName, "GDVInspect", "GDVFiles"), archivePath);
            string targetDirectory2 = Path.Combine(diskName, "GDVInspect", "ExtractedFiles");
            fileManager.ExtractArchive(archivePath, targetDirectory2);
            // 6
            SearchInFile searchInFile = new SearchInFile(filePath);
            DateTime startDate = new DateTime(2023, 11, 12, 13, 48, 47);
            DateTime endDate = new DateTime(2023, 11, 12, 13, 48, 50);
            searchInFile.SearchByDate(startDate, endDate);
            string keyword = "logWrite";
            searchInFile.SearchByKeyword(keyword);
            searchInFile.FilterCurrentHour(); 
        }
    }
}