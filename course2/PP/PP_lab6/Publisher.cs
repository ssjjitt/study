using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab6Lib
{
    public class Publisher
    {

        public Publisher(string eventname) {
            
        }

        public void subscribe(ISubscriber subscriber)
        {

        }

        public bool unsubscribe(ISubscriber subscriber)
        {

            return false;
        }

        public int nonify()
        {
            return 0;
        }
    }
}
