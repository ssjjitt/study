using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;


namespace OOP_lab8
{
    public delegate void MoveEventHandler(int offset); // делегаты для событий
    public delegate void CompressEventHandler(double compressionFactor);

    public class User // Создать класс Пользователь с событиями Переместить (можно задать смещение) и Сжать(коэффициент сжатия)
    {
        public event MoveEventHandler Move;
        public event CompressEventHandler Compress;

        // лямбда-выражение для обработки события Move
        public void OnMove(int offset) => Move?.Invoke(offset); // При реализации методов везде где возможно использовать лямбда-выражения.
        // лямбда-выражение для обработки события Compress
        public void OnCompress(double compressionFactor) => Compress?.Invoke(compressionFactor);
    }
}
