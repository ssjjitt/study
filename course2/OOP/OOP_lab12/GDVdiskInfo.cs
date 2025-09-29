using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace OOP_lab12
{
    class GDVdiskInfo
    {
        private GDVlog log;
        
        public GDVdiskInfo(GDVlog log)
        {
            this.log = log;
        }

        public string freeDisk(string drive) 
        {
            log.logWrite("freeDisk", "File: GDVlog.txt, Path: e:/уник/c/OOP_lab12/GDVlog.txt");

            DriveInfo driveInfo = new DriveInfo(drive);   
            if (driveInfo.IsReady) 
            {
                return $"Свободное место: {driveInfo.TotalFreeSpace}";
            }
            else
            {
                return "Проблемы с запуском";
            }
        }
        public string fileSystem(string driveName)
        {
            log.logWrite("fileSystem", "File: GDVlog.txt, Path: e:/уник/c/OOP_lab12/GDVlog.txt");

            DriveInfo drive = new DriveInfo(driveName);

            if (drive.IsReady)
            {
                return $"Файловая система диска {driveName}: {drive.DriveFormat}";
            }
            else
            {
                return $"Проблемы с запуском";
            }
        }

        public void driveInfo()
        {
            log.logWrite("driveInfo", "File: GDVlog.txt, Path: e:/уник/c/OOP_lab12/GDVlog.txt");

            DriveInfo[] drives = DriveInfo.GetDrives();

            foreach (DriveInfo drive in drives)
            {
                Console.WriteLine($"Имя: {drive.Name}");
                Console.WriteLine($"Тип: {drive.DriveType}");
                Console.WriteLine($"Объем: {drive.TotalSize} bytes");
                Console.WriteLine($"Доступный объем: {drive.TotalFreeSpace} bytes");
                Console.WriteLine($"Метка тома: {drive.VolumeLabel}");
                Console.WriteLine($"Имя файловой системы: {drive.DriveFormat}");
                Console.WriteLine();
            }
        }
    }
}
