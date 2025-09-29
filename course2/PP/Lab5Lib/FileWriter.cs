using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection.Metadata;
using System.Text;
using System.Threading.Tasks;

namespace Lab5Lib.Class
{
    public class FileWriter : IWriter
    {
        private string _filename;
        public string FileName { get => _filename; }

        public FileWriter(string? filename = null)
        {
            this._filename = filename ?? Constant.FileName;
        }

        public string? Save(string? message)
        {
            using (StreamWriter sw = new(this._filename, true))
            {
                sw.WriteLine(message);
            }
            return this._filename;
        }
    }
}