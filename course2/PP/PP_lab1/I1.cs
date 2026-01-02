using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PP_lab1
{
    public interface I1
    {
        int Property { get; set; }

        void Method(string param);

        event EventHandler Event;

        int this[int index] { get; set; }
    }
}
