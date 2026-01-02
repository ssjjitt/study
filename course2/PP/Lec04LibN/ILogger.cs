using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lec04LibN
{
        public interface ILogger // логіка запісі в файл
        {
            void Start(string title); 
            void Log(string message);
            void Stop();
        }
}
