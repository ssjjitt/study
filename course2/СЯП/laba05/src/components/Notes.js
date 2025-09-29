
import React from "react";
import "./S.css"

export class Notes extends React.Component {
  constructor(props) {
    super(props);
    this.state = {
      title: "",
      date: "",
      desc: "",
      notes: [],
    };
  }
  style(length) {
    if (length > 8) {
      return { background: "red" };
    }
    return { background: "rgb(250, 250, 162)" };
  }
  titleHandle = (e) => {
    this.setState({ title: e.target.value });
  };
  dateHandle = (e) => {
    this.setState({ date: e.target.value });
  };
  descHandle = (e) => {
    this.setState({ desc: e.target.value });
  };
  addNote = () => {
    this.setState({
      notes: [
        ...this.state.notes,
        {
          title: this.state.title,
          date: this.state.date,
          desc: this.state.desc,
        },
      ],
      title: "",
      date: "",
      desc: "",
    });
  };
  deleteFirst = () => {
    this.setState({notes: this.state.notes.slice(1, this.state.notes.length)})
  }
  deleteLast = () => {
    this.setState({notes: this.state.notes.slice(0, this.state.notes.length - 1)})
  }
  render() {
    let length = 0;
    return (
      <>
        <form>
          <input
            type="text"
            placeholder="Название заметки"
            onChange={this.titleHandle}
            value={this.state.title}
          />
          <input
            type="text"
            placeholder="Дата заметки"
            onChange={this.dateHandle}
            value={this.state.date}
          />
          <textarea
            placeholder="Введите текст заметки"
            onChange={this.descHandle}
            value={this.state.desc}
          />
        </form>
        <div>
        <button onClick={this.addNote}>Добавить заметку</button>
        {this.state.notes.length > 3 && (
          <>
            <button onClick={this.deleteFirst}>Удалить первую</button>
            <button onClick={this.deleteLast}>Удалить последнюю</button>
          </>
        )}
        </div>
        <div>
        {this.state.notes.map((item) => {
          length++;
          return (
            <div key={item.title} style={this.style(length)}>
            <p>{length > 7 && "Слишком много заметок!!!!"}</p>
              <h3>{item.title}</h3>
              <h4>{item.date}</h4>
              <p>{item.desc}</p>
            </div>
          );
        })}
        </div>
      </>
    );
  }
}