import React from "react";

class JobMenu extends React.Component {    
  constructor(props) {    
    super(props); 
    this.state = { value: "" }; 
    this.selected = this.selected.bind(this); 
  }
  jobs = [
    { value: "", name: "Выберите" },
    { value: "Programmer", name: "Программист" },
    { value: "Manager", name: "Менеджер" },
    { value: "Worker", name: "Рабочий" },
    { value: "Doctor", name: "Доктор" },
    { value: "Driver", name: "Водитель" },
    { value: "Actor", name: "Актёр"},
  ];
  selected(el) {   
    return this.setState({ value: el.target.value });
  }
  render() {
    return (
      <div>
        <select onChange={this.selected}>
          {this.jobs.map((item) => {
            return <option value={item.value}>{item.name}</option>;
          })}
        </select>
        <Links value={this.state.value} />
      </div>
    );
  }
}

class Links extends React.Component {
  switchCase() {
    let links = [];
    let value = this.props.value;

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
      default:
        break;
    }
    return (
      <div>
        <ul>
          {links.map((item) => {
            return (
              <li><a href="#1">{item}</a></li>
            );
          })}
        </ul>
      </div>
    );
  }

  render() {
    return <div>{this.switchCase()}</div>;
  }
}

export default JobMenu;