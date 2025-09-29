using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PP_lab2
{
    public class Faculty : Organization
    {
        protected List<Department> departments;
        public Faculty()
        {

        }
        public Faculty(Faculty faculty)
        {
            Name = "Faculty";
            ShortName = "Fac";
            Address = "FaciltyAdress";
        }
        public Faculty(string name, string shortName, string adress)
        {
            Name = name;
            ShortName = shortName;
            Address = adress;
        }
        public int addDepartment(Department department)
        {
            this.departments.Add(department);
            return this.departments.Count - 1;
        }
        public bool delDepartment(int index)
        {
            if (index >= 0 && index < this.departments.Count)
            {
                this.departments.RemoveAt(index);
                return true;
            }
            else
            {
                return false;
            }
        }
        public bool updDepartment(Department department)
        {
            int index = this.departments.IndexOf(department);
            if (index != -1)
            {
                this.departments[index] = department;
                return true;
            }
            else
            {
                return false;
            }
        }
        private bool verDepartment(int id)
        {
            if (id >= 0 && id < this.departments.Count)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        public List<Department> getDepartmentList()
        {
            return new List<Department>(this.departments);
        }
        public void PrintInfo()
        {
            Console.WriteLine($"Name: {Name}");
            Console.WriteLine($"ShortName: {ShortName}");
            Console.WriteLine($"Address: {Address}");
        }
        public List<JobVacancy> GetJobVacancies()
        {
            return new List<JobVacancy>();
        }
        public int AddJobTitle(JobTitle jobTitle)
        {
            return 1;
        }
        public bool DelJobTitle(int id)
        {
            return true;
        }
        public int OpenJobVacancy(JobVacancy jobVacancy)
        { 
            return 1; 
        }
        public bool CloseJobVacancy(int id)
        {
            return true;
        }
        public Employee Recruit(JobVacancy jobVacancy, Person person)
        {
            return null;
        }
        public bool Dismiss(int id, Reason reason)
        {
            return true;
        }
    }
}
