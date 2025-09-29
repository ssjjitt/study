import { Component } from "react";  // для импорта компонент из react

export class SelectJob extends Component {    // сразу же импортируем в App.js
  constructor(props) {    // добавили базовый конструктор, классовые компоненты всега должны вызывать базовый конструктор с аргументом props
    super(props); // передаем props, чтобы базовый конструктор мог иинициализировать this.props
    this.state = { value: "" }; // указали начальное состояние в переменной this.state
    this.selected = this.selected.bind(this); // при вызове устанавливает в качестве контекста выполнения this предоставленное значение
  }
  // инициализировали ассоциативный массив
  jobs = [
    { value: "", name: "Выберите" },
    { value: "Programmer", name: "Программист" },
    { value: "Manager", name: "Менеджер" },
    { value: "Worker", name: "Рабочий" },
    { value: "Doctor", name: "Доктор" },
    { value: "Driver", name: "Водитель" },
    { value: "Actor", name: "Актёр"}
  ];
  selected(el) {  // устанавливает target на выбранный option
    return this.setState({ value: el.target.value });
  }
// onChange - для отслеживания изменений в selected
// создаем массив MAP с параметром item из объектов job и записываем пары ключ-значение в аттрибут value и непосредственно в сад тег option
// далее выводим компоненту JobMenu в соответствии с тем, какой value принимает тег
  render() {
    return (
      <div>
        <select onChange={this.selected}>
          {this.jobs.map((item) => {
            return <option value={item.value}>{item.name}</option>;
          })}
        </select>
        <JobMenu value={this.state.value} />
      </div>
    );
  }
}

class JobMenu extends Component {
  switchCase() {
    let links = [];   // создаем пустой массив, в котором позже будем хранить ссылки
    let value = this.props.value;   // создаем локальную переменную value, которая будет принимать параметры из тех value, которые мы выбрали в теге select
// метод push() добавляет элементы в конец массива и возвращает новую длину
    switch (value) {
      case "Programmer":
        links.push("linkForProgrammer", "linkForProgrammer", "linkForProgrammer", "linkForProgrammer", "linkForProgrammer");
        break;
      case "Manager":
        links.push("linkForManager", "linkForManager", "linkForManager", "linkForManager", "linkForManager");
        break;
      case "Worker":
        links.push("linkForWorker", "linkForWorker", "linkForWorker", "linkForWorker", "linkForWorker");
        break;
      case "Doctor":
        links.push("linkForDoctor", "linkForDoctor", "linkForDoctor", "linkForDoctor", "linkForDoctor");
        break;
      case "Driver":
        links.push("linkForDriver", "linkForDriver", "linkForDriver", "linkForDriver", "linkForDriver");
        break;
      case "Actor":
        links.push("linkForActor", "linkForActor", "linkForActor", "linkForActor", "linkForActor");
      break;
    }
    return (
      <div>
        <ul>
          {links.map((item) => {
            return (
              <li><a href="#">{item}</a></li>
            );
          })}
        </ul>
      </div>
    );
  }

  render() {
    return <>{this.switchCase()}</>;
  }
}