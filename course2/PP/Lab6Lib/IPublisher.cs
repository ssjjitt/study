using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab6Lib
{
    public interface IPublisher
    {
        public void subscribe(ISubscriber subscriber);
        public bool unsubscribe(ISubscriber subscriber);
        public int notify();
    }
}
