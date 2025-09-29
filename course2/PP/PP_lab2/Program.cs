using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PP_lab2
{
    internal class Program
    {
        static void Main(string[] args)
        {
            Organization organization = new Organization();
            Organization organization1 = new Organization("Организейшн", "Организ", "НЕМинск");
            University university = new University("Юниверсити", "Юниверс", "Где-то в Минске");
            Faculty faculty = new Faculty("Факульти", "Факульт", "Тоже где-то в Минске");
            University university1 = new University();
            Faculty faculty1 = new Faculty();

            Console.WriteLine("\n");
            university.PrintInfo();
            Console.WriteLine("\n");
            faculty.PrintInfo();
            Console.WriteLine("\n");
            university1.PrintInfo();
            Console.WriteLine("\n");
            faculty1.PrintInfo();
            Console.WriteLine("\n");
            organization.PrintInfo();
            Console.WriteLine("\n");
            organization1.PrintInfo();

            Console.WriteLine($"Name университета: {university.Name}");
            Console.WriteLine($"ShortName факультета: {faculty.ShortName}");

            Console.WriteLine("\n\n");
            Person person = new Person("Валера");
            JobVacancy job = new JobVacancy("Работает где угодно");
            Employee employee = new Employee(job, person);
            employee.PrintInfo();
            bool tr = university.Dismiss(0, Reason.плохо_работал);
            if (tr)
            {
                Console.WriteLine("уволен потому что слишком хорош");
            }
            else
            {
                Console.WriteLine("ужасен в работе");
            }
        }
    }
}
