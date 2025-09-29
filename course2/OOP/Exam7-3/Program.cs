//using System;
//using System.Drawing;

//namespace Exam7_3
//{
//    class Button
//    {
//        private string caption;
//        public string Caption { get { return caption; } set { caption = value; } }
//        struct startpoint
//        {
//            internal int x;
//            internal int y;
//        }
//        private double w;
//        public double W { get { return w; } set { w = value; } }
//        private double h;
//        public double H { get { return h; } set { h = value; } }

//        public Button(string caption, Point startpoint, int w, int h)
//        {
//            this.caption = caption;
//            this.startpoint = startpoint;
//            this.w = w;
//            this.h = h;
//        }

//    }
//    class CheckButton : Button
//    {
//        enum state
//        {
//            uncheckedd = 0,
//            checkedd = 1
//        }
//        public override string ToString()
//        {
//            return base.ToString();
//        }
//        public override bool Equals(object? obj)
//        {
//            if (obj is Button some)
//            {
//                return this.Caption == some.Caption && this.H == some.H && this.W == some.W;
//            }
//            return base.Equals(obj);
//        }
//        public bool Check()
//        {
//            if(this.)
//            return false;
//        }
//    }
//    class Program
//    {
//        static void Main(string[] args)
//        {
//            Button button = new Button();
//        }
//    }
//}