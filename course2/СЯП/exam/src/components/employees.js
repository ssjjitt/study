import React, { useState } from 'react';

const EmployeeTable = () => {
  const [employees, setEmployees] = useState([
    { id: 1, name: 'Алексей', fio: 'Мисевич', salary: 1, selected: false },
    { id: 2, name: 'Николай', fio: 'Белодед', salary: 1600, selected: false },
    { id: 3, name: 'Дмитрий', fio: 'Гринюк', salary: 880, selected: false },
    { id: 4, name: 'Александра', fio: 'Север <3', salary: 780, selected: false },
    { id: 5, name: 'Михаил', fio: 'Чайковский', salary: 980, selected: false },
    { id: 6, name: 'Аделина', fio: 'Наркевич', salary: 1080, selected: false },
  ]);

  const handleCheckboxChange = (id) => {
    setEmployees((prevEmployees) => {
      return prevEmployees.map((employee) => {
        if (employee.id === id) {
          return { ...employee, selected: !employee.selected };
        }
        return employee;
      });
    });
  };

  const totalSalary = employees
    .filter((employee) => employee.selected)
    .reduce((total, employee) => total + employee.salary, 0);

  return (
    <div>
        <h1>Employees</h1>
      <table>
        <thead>
          <tr>
            <th>Имя</th>
            <th>Фамилия</th>
            <th>Зарплата</th>
            <th>Выбор</th>
          </tr>
        </thead>
        <tbody>
          {employees.map((employee) => (
            <tr key={employee.id}>
              <td>{employee.name}</td>
              <td>{employee.fio}</td>
              <td>{employee.salary}</td>
              <td>
                <input
                  type="checkbox"
                  checked={employee.checked}
                  onChange={() => handleCheckboxChange(employee.id)}
                />
              </td>
            </tr>
          ))}
        </tbody>
      </table>
      <p>Сумма зарплат выбранных сотрудников: {totalSalary}</p>
    </div>
  );
};

export default EmployeeTable;
