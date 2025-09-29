using System;

using System.Collections.Generic;

using System.ComponentModel;

using System.Data;

using System.Drawing;

using System.Text;

using System.Windows.Forms;

 

namespace SMMIF_lab3_

{

    public partial class Form1 : Form

    {

        List<double> a;

        List<double> b;



        public Form1()

        {

            InitializeComponent();

        }

        private double fun(double x, int cn)

        {

            double res = -Math.PI / 2;

            for (int i = 1; i <= cn; i++)

            {

                res = res + a[i - 1] * Math.Cos(x * i) + b[i - 1] * Math.Sin(x * i);

            }

            return res;

        }



        private void button1_Click(object sender, EventArgs e)

        {

            a = new List<double>();

            b = new List<double>();

            int cn = 10;

            for (int i = 1; i <= cn; i++)

            {

                double i_d = Convert.ToDouble(i);

                a.Add(2 / Math.PI / i_d / i_d * (1 - Math.Pow(-1, i_d)));

                b.Add(2 / i_d * (Math.Pow(-1, i_d + 1)));

            }



            StringBuilder sb = new StringBuilder();

            for (int j = 0; j <= 100; j++)

            {

                double x = -Math.PI + j * 0.1;

                sb.AppendFormat("{0}; {1}\n", x, fun(x, cn));

            }

            System.IO.File.WriteAllText("c:\\3\\fur.txt", sb.ToString());

        }

    }

}