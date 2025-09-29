import { StudentInfo } from "./StudentInfo.js";
import "./S.css"
import React from "react";

export class StudentInfoHandler extends React.Component {
  age(student) {
    let currentDate = new Date(),
      birthDate = student.birthDate.replace(/[^0-9]+/g, ""),  // возвращаем строку с совпадениями
      // ^ Соответствует началу ввода
      // g - глобальный поиск
      // так как мы получили строку без точек
      birthYear = birthDate % 10000, // то мы можем поделить с остатком и получить год рождения
      birthMonth = Math.round((birthDate / 10000) % 100), // и соответственно, манипуляциями далее, месяц
      birthDay = Math.round(birthDate / 1000000), // и день
      age = currentDate.getFullYear() - birthYear; 
    if (currentDate.getMonth() < birthMonth - 1) age--; // если человек родился в мае а сейчас апрель
    if (
      birthMonth - 1 === currentDate.getMonth() &&
      currentDate.getDate() < birthDay          // такая же проверка и на день рождения
    )
      age--;
    return age;
  }
  cours(student) {
    let currentDate = new Date(),
      cours = 1 + currentDate.getFullYear() - student.uniYear;  // отнимаем от текущего года год поступления в университет
    if (currentDate.getMonth() > 8) cours++; // если месяц > 8, то курс увеличиваем
    if(cours > 4) cours = "Окончил унивеситет" 
    return cours;
  }
  mailOperator(student) {
    return student.email.split("@")[1]; // разбиваем на массив подстрок указанным символом - подстрокой. в массиве две части: начало почты и gmail.com или чет еще
  }
  phoneOperator(student) { // ассоциативный массив с операторами
    let operators = [
        {
          name: "A1 (Velcom)",
          code: 29,
          firstNumber: [1, 3, 6, 9],
        },
        {
          name: "МТС",
          code: 29,
          firstNumber: [2, 5, 7, 8],
        },
        {
          name: "A1 (Velcom)",
          code: 44,
        },
        {
          name: "МТС",
          code: 33,
        },
        {
          name: "life :)",
          code: 25,
        },
        {
          name: "Городской",
          code: 17,
        },
      ],
      phone = student.phoneNumber,
      position,
      code,
      operator;
    // проверка на формат ввода
    if (phone[0] === "+") position = 4;     // +37529
    if (phone[0] === "8") position = 2;     // 8029
    code = +phone.slice(position, position + 2); // "нарезаем" код

    operators.map((item) => {
      if (item.code === code && code === 29) {      // проверка на код, так как в мтс и А1 есть одинаковые
        let firstNum = +phone.slice(position + 2, position + 3); // опять нарезаем, чтобы сверить цифру 
        for (let i = 0; i < item.firstNumber.length; i++) {     // перебираем массив одного из объектов в ассоциативном массиве
          if (firstNum === item.firstNumber[i]) {       // и если что-то из них нам подойдет
            return (operator = item.name); // возвращаем оператор
          }
        }
      } else if (item.code === code) return (operator = item.name);
    });
    return operator;
  }
  render() {
    return (
        <StudentInfo
          render={(student) => (    // пропсы рендера для совместного использования кода между компонентами
          // то есть здесь мы сообщаем компоненту, что именно он должен отрисовывать
            <table>
              <tbody>
                <tr>
                  <td>ФИО</td>
                  <td>{student.fio}</td>
                </tr>
                <tr>
                  <td>Текущий возраст</td>
                  <td>{this.age(student)}</td>
                </tr>
                <tr>
                  <td>Факультет, курс, группа</td>
                  <td>
                    {student.faculty}, {this.cours(student)}, {student.group}
                  </td>
                </tr>
                <tr>
                  <td>Специальность</td>
                  <td>{student.speciality}</td>
                </tr>
                <tr>
                  <td>Электронная почта</td>
                  <td>{student.email}</td>
                </tr>
                <tr>
                  <td>Оператор услуг ЭП</td>
                  <td>{this.mailOperator(student)}</td>
                </tr>
                <tr>
                  <td>Номер телефона</td>
                  <td>{student.phoneNumber}</td>
                </tr>
                <tr>
                  <td>Оператор услуг МС</td>
                  <td>{this.phoneOperator(student)}</td>
                </tr>
              </tbody>
            </table>
          )}
        />
    );
  }
}
