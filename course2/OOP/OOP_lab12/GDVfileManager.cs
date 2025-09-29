using System;
using System.Collections.Generic;
using System.IO;
using System.IO.Compression;

namespace OOP_lab12
{
    class GDVFileManager
    {
        private GDVlog log;

        public GDVFileManager(GDVlog log)
        {
            this.log = log;
        }

        public void GetDiskContents(string diskName)
        {
            log.logWrite("GetDiskContents", $"Disk Name: {diskName}");

            string inspectDirectoryPath = Path.Combine(diskName, "GDVInspect");
            try
            {
                Directory.CreateDirectory(inspectDirectoryPath);

                string fileInfoPath = Path.Combine(inspectDirectoryPath, "gdvdirinfo.txt");
                using (StreamWriter writer = File.CreateText(fileInfoPath))
                {
                    writer.WriteLine("Files:");
                    foreach (string file in Directory.GetFiles(diskName))
                    {
                        writer.WriteLine(file);
                    }

                    writer.WriteLine();
                    writer.WriteLine("Directories:");
                    foreach (string directory in Directory.GetDirectories(diskName))
                    {
                        writer.WriteLine(directory);
                    }
                }

                string copyFilePath = Path.Combine(inspectDirectoryPath, "gdvdirinfo_copy.txt");
                File.Copy(fileInfoPath, copyFilePath, true);

                string renamedFilePath = Path.Combine(inspectDirectoryPath, "renamedfile.txt");
                if (File.Exists(renamedFilePath))
                {
                    File.Delete(renamedFilePath);
                }
                File.Move(copyFilePath, renamedFilePath);

                File.Delete(fileInfoPath);
            }
            catch (Exception ex)
            {

            }
        }

        public void CopyFilesByExtension(string sourceDirectory, string targetDirectory, string extension)
        {
            log.logWrite("CopyFilesByExtension", $"Source Directory: {sourceDirectory}, Target Directory: {targetDirectory}, Extension: {extension}");

            string targetFilesDirectory = Path.Combine(targetDirectory, "GDVFiles");
            try
            {
                Directory.CreateDirectory(targetFilesDirectory);

                string[] files = Directory.GetFiles(sourceDirectory, $"*.{extension}");
                foreach (string file in files)
                {
                    string fileName = Path.GetFileName(file);
                    string targetFilePath = Path.Combine(targetFilesDirectory, fileName);
                    File.Copy(file, targetFilePath, true);
                }
            }
            catch (Exception ex)
            {
            }
        }

        public void CreateArchive(string sourceDirectory, string archivePath)
        {
            log.logWrite("CreateArchive", $"Source Directory: {sourceDirectory}, Archive Path: {archivePath}");

            try
            {
                ZipFile.CreateFromDirectory(sourceDirectory, archivePath);
            }
            catch (Exception ex)
            {
            }
        }

        public void ExtractArchive(string archivePath, string targetDirectory)
        {
            log.logWrite("ExtractArchive", $"Archive Path: {archivePath}, Target Directory: {targetDirectory}");

            try
            {
                ZipFile.ExtractToDirectory(archivePath, targetDirectory);
            }
            catch (Exception ex)
            {
            }
        }
    }
}