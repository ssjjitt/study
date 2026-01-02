import React from "react";

export class StudentInfo extends React.Component {
  constructor(props) {
    super(props);
    this.state = {
      fio: "",
      birthDate: "",
      uniYear: "",
      faculty: "",
      group: "",
      speciality: "",
      email: "",
      phoneNumber: "",
      display: "none",
    };
  }

  handle = (target, e) => {
    this.setState({ [target]: e.target.value });
  };

  render() {
    return (
      <>
        <form>
          <input
            type="text"
            placeholder="фио"
            onChange={this.handle.bind(this, "fio")}
            value={this.state.fio}
          />
          <input
            type="text"
            placeholder="дата рождения(xx.xx.xxxx)"
            onChange={this.handle.bind(this, "birthDate")}
            value={this.state.birthDate}
          />
          <input
            placeholder="год поступления в университет"
            onChange={this.handle.bind(this, "uniYear")}
            value={this.state.uniYear}
          />
          <input
            placeholder="факультет"
            onChange={this.handle.bind(this, "faculty")}
            value={this.state.faculty}
          />
          <input
            placeholder="группа"
            onChange={this.handle.bind(this, "group")}
            value={this.state.group}
          />
          <input
            placeholder="специальность"
            onChange={this.handle.bind(this, "speciality")}
            value={this.state.speciality}
          />
          <input
            placeholder="почта"
            onChange={this.handle.bind(this, "email")}
            value={this.state.email}
          />
          <input
            placeholder="номер телефона"
            onChange={this.handle.bind(this, "phoneNumber")}
            value={this.state.phoneNumber}
          />
        </form>
        <StudentInfoHandler
          fio={this.state.fio}
          birthDate={this.state.birthDate}
          uniYear={this.state.uniYear}
          faculty={this.state.faculty}
          group={this.state.group}
          speciality={this.state.speciality}
          email={this.state.email}
          phoneNumber={this.state.phoneNumber}
        />
      </>
    );
  }
}

class StudentInfoHandler extends React.Component {
  age(student) {
    let currentDate = new Date(),
      birthDate = student.birthDate.replace(/[^0-9]+/g, ""),
      birthYear = birthDate % 10000,
      birthMonth = Math.round((birthDate / 10000) % 100),
      birthDay = Math.round(birthDate / 1000000),
      age = currentDate.getFullYear() - birthYear;
    if (currentDate.getMonth() < birthMonth - 1) age--;
    if (
      birthMonth - 1 === currentDate.getMonth() &&
      currentDate.getDate() < birthDay
    )
      age--;
    return age;
  }

  cours(student) {
    let currentDate = new Date(),
      cours = 1 + currentDate.getFullYear() - student.uniYear;
    if (currentDate.getMonth() > 8) cours++;
    if (cours > 4) cours = "Окончил унивеситет";
    return cours;
  }

  mailOperator(student) {
    return student.email.split("@")[1];
  }

  phoneOperator(student) {
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
    if (phone[0] === "+") position = 4;
    if (phone[0] === "8") position = 2;
    code = +phone.slice(position, position + 2);

    operators.map((item) => {
      if (item.code === code && code === 29) {
        let firstNum = +phone.slice(position + 2, position + 3);
        for (let i = 0; i < item.firstNumber.length; i++) {
          if (firstNum === item.firstNumber[i]) {
            return (operator = item.name);
          }
        }
      } else if (item.code === code) return (operator = item.name);
    });
    return operator;
  }

  render() {
    return (
      <>
        {this.props.phoneNumber.length >= 11 &&
          <table>
            <tr>
              <td>ФИО</td>
              <td>{this.props.fio}</td>
            </tr>
            <tr>
              <td>возраст</td>
              <td>{this.age(this.props)}</td>
            </tr>
            <tr>
              <td>факультет, курс, группа</td>
              <td>
                {this.props.faculty}, {this.cours(this.props)},{" "}
                {this.props.group}
              </td>
            </tr>
            <tr>
              <td>специальность</td>
              <td>{this.props.speciality}</td>
            </tr>
            <tr>
              <td>почта</td>
              <td>{this.props.email}</td>
            </tr>
            <tr>
              <td>оператор</td>
              <td>{this.mailOperator(this.props)}</td>
            </tr>
            <tr>
              <td>номер телефона</td>
              <td>{this.props.phoneNumber}</td>
            </tr>
            <tr>
              <td>оператор</td>
              <td>{this.phoneOperator(this.props)}</td>
            </tr>
          </table>
        }
      </>
    );
  }
}
