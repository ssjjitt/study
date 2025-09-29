using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PP_lab2
{
    interface IStaff
    {
        List<JobVacancy> GetJobsVacancies();
        List<Employee> GetEmployees();
        List<JobTitle> GetJobTitles();
        int AddJobTitle();
        string PrintJobVacancies();
        bool DelJobTitle(int id);
        bool OpenJobVacancy(JobVacancy jobVacancy);
        bool CloseJobVacancy(int id);
        Employee Recruit(JobVacancy employee, Person person);
        bool Dismiss(int id, Reason reason);
    }
}
