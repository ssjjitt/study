using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Runtime.ConstrainedExecution;
using System.Security.Cryptography.X509Certificates;
using System.Text;
using System.Threading.Tasks;
using System.Xml.Linq;

namespace PP_lab2
{
    public class University : Organization
    {
        private List<Faculty> faculties;

        private List<JobVacancy> allJobVacancies;
        private List<JobVacancy> jobVacancies;

        public University()
        {
            Name = "Faculty";
            ShortName = "Fac";
            Address = "FaciltyAdress";
        }

        public University(University university)
        {
            // Id = university.Id;
            Name = university.Name;
            ShortName = university.ShortName;
            Address = university.Address;
        }

        public University(string name, string shortName, string address)
        {
            Name = name;
            ShortName = shortName;
            Address = address;
        }

        public int addFaculty(Faculty faculty)
        {
            this.faculties.Add(faculty);
            return this.faculties.Count - 1;
        }

        public bool delFaculty(int index)
        {
            if (index >= 0 && index < this.faculties.Count)
            {
                this.faculties.RemoveAt(index);
                return true;
            }
            else
            {
                return false;
            }
        }

        public bool updFaculty(Faculty faculty)
        {
            int index = this.faculties.IndexOf(faculty);
            if (index != -1)
            {
                this.faculties[index] = faculty;
                return true;
            }
            else
            {
                return false;
            }
        }

        public bool verFaculty(int index)
        {
            return index >= 0 && index < faculties.Count;
        }

        public List<Faculty> getFaculties()
        {
            return new List<Faculty>(this.faculties);
        }

        public void printInfo()
        {
            Console.WriteLine($"Name: {Name}");
            Console.WriteLine($"ShortName: {ShortName}");
            Console.WriteLine($"Address: {Address}");
        }

        public List<JobVacancy> getJobVacancies()
        {
            allJobVacancies.Clear();
            foreach (Faculty faculty in faculties)
            {
                allJobVacancies.AddRange(faculty.GetJobVacancies());
            }
            return new List<JobVacancy>(this.jobVacancies);
        }

        public int addJobTitle(JobVacancy jobVacancy)
        {
            this.jobVacancies.Add(jobVacancy);
            return this.jobVacancies.Count - 1;
        }

        public bool delJobTitle(int index)
        {
            if (index >= 0 && index < this.jobVacancies.Count)
            {
                this.jobVacancies.RemoveAt(index);
                return true;
            }
            else
            {
                return false;
            }
        }

        public int openJobVacancy(JobVacancy jobVacancy)
        {
            return 1;
        }

        public bool closeJobVacancy(int index)
        {
            if (index >= 0 && index < this.jobVacancies.Count)
            {
                return true;
            }
            else
            {
                return false;
            }
        }

        private List<Employee> employees;


        public Employee recruit(JobVacancy jobVacancy, Person person)
        {
            Employee employee = new Employee(jobVacancy, person);
            employees.Add(employee);
            return employee;
        }

        public bool dismiss(int index, Reason reason)
        {
            bool reas = false;
            employees.RemoveAt(index);
            switch (reason)
            {
                case Reason.плохо_работал:
                    {
                        reas = false;
                        break;
                    }
                case Reason.слишкрм_хорошо_работал:
                    {
                        reas = true;
                        break;
                    }
            }
            return reas;
        }
    }
    public class JobVacancy
    {
        public string v1;

        public JobVacancy(string v1)
        {
            this.v1 = v1;
        }
    }
    public class Person
    {
        public string v2;
        public Person(string person)
        {
            this.v2 = person;
        }
    }
    public class Employee
    {
        public string jobVacancy;
        public string person;
        public Employee()
        {

        }
        public Employee(JobVacancy jobVacancy, Person person)
        {
            this.jobVacancy = jobVacancy.v1;
            this.person = person.v2;
        }
        public void PrintInfo()
        {
            Console.WriteLine(person);
            Console.WriteLine(jobVacancy);
        }
    }
    public class JobTitle
    {
    }
    public enum Reason
    {
        плохо_работал,
        не_достаточно_хорошо_работал,
        слишкрм_хорошо_работал
    }
}
