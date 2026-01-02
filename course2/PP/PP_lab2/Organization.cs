using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PP_lab2
{
    public class Organization : IStaff
    {
        public int Id { get; private set; }
        public string Name { get; protected set; }
        public string ShortName { get; protected set; }
        public string Address { get; protected set; }
        public DateTime TimeStamp { get; protected set; }

        public Organization()
        {
            Id = 1;
            Name = "Standart";
            ShortName = "Stand";
            Address = "Minsk";
            TimeStamp = DateTime.Now;
        }

        public Organization(Organization organization)
        {
            Id = organization.Id;
            Name = organization.Name;
            ShortName = organization.ShortName;
            Address = organization.Address;
            TimeStamp = organization.TimeStamp;
        }

        public Organization(string name, string shortName, string address)
        {
            Name = name;
            ShortName = shortName;
            Address = address;
            TimeStamp = DateTime.Now;
        }

        public void PrintInfo()
        {
            Console.WriteLine($"Id: {Id}");
            Console.WriteLine($"Name: {Name}");
            Console.WriteLine($"Short Name: {ShortName}");
            Console.WriteLine($"Address: {Address}");
            Console.WriteLine($"Time Stamp: {TimeStamp}");
        }

        public List<JobVacancy> GetJobsVacancies()
        {
            List<JobVacancy> allVacancies = new List<JobVacancy>();
            return allVacancies;
        }

        public List<Employee> GetEmployees()
        {
            return new List<Employee>(); 
        }

        public List<JobTitle> GetJobTitles()
        {
            return new List<JobTitle>(); 
        }

        public int AddJobTitle() 
        {
            return 1;
        }

        public string PrintJobVacancies()
        {
            StringBuilder sb = new StringBuilder();
            List<JobVacancy> vacancies = GetJobsVacancies();
            if (vacancies.Count == 0)
            {
            }
            else
            {
                foreach (JobVacancy vacancy in vacancies)
                {
                    sb.AppendLine(vacancy.ToString());
                }
            }
            return sb.ToString();
        }

        public bool DelJobTitle(int id) 
        {
            return true; 
        }

        public bool OpenJobVacancy(JobVacancy jobVacancy)
        {
            return true; 
        }

        public bool CloseJobVacancy(int id)
        {
            return false; 
        }

        public Employee Recruit(JobVacancy jobVacancy, Person person)
        {
            return null;
        }

        public bool Dismiss(int id, Reason reason)
        {
            return false;
        }
    }
}
