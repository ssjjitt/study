import React from "react";
import "./S.css";

export class Notes extends React.Component {
  constructor(props) {
    super(props);
    this.state = {
      title: "",
      date: null,
      desc: "",
      notes: [],
      edit: null,
    };
  }
  style(length) {
    if (length > 8) {
      return { background: "red" };
    }
    return { background: "#ffed86" };
  }

  handle = (target, e) => {
    this.setState({ [target]: e.target.value });
  };

  addNote = () => {
    this.setState(
      {
        notes: [
          ...this.state.notes,
          {
            title: this.state.title,
            date: this.props.date.toLocaleDateString(),
            desc: this.state.desc,
          },
        ],
        title: "",
        date: this.state.date,
        desc: "",
      },
    );
  };
  deleteFirst = () => {
    this.setState(
      {
        notes: this.state.notes.slice(1, this.state.notes.length),
      },
    );
  };
  deleteLast = () => {
    this.setState(
      {
        notes: this.state.notes.slice(0, this.state.notes.length - 1),
      },
    );
  };
  deleteAll = () => {
    this.setState({ notes: [] }, () => this.props.addNote(this.state.notes));
  };
  form() {
    if (this.props.showForm)
      return (
        <>
        <div className="note">
          <form>
            <input 
              type="text"
              placeholder="заголовок"
              onChange={this.handle.bind(this, "title")}
              value={this.state.title}
            />
            <input  
              type="text"
              placeholder="дата"
              readOnly
              value={this.props.date.toLocaleDateString()}
            />
            <textarea
              placeholder="заметка"
              onChange={this.handle.bind(this, "desc")}
              value={this.state.desc}
            />
          </form>
          <button onClick={this.addNote}>Добавить заметку</button>
          </div>
        </>
      );
  }
  edit = (note, newNote) => {
    for (let i = 0; i < this.state.notes.length; i++) {
      if (this.state.notes[i] === note) {
        return this.setState(({ notes }) => ({
          notes: [...notes.slice(0, i), newNote, ...notes.slice(i + 1)],
          edit: null,
        }));
      }
    }
  };
  render() {
    let length = 0;
    return (
      <>
        {this.form()}
        {this.state.notes.length > 0 && (
          <>
          <div className="note">
            <button onClick={this.deleteFirst}>Удалить первую</button>
            <button onClick={this.deleteLast}>Удалить последнюю</button>
            <button onClick={this.deleteAll}>Удалить все</button>
            </div>
          </>
        )}
        {this.state.notes.map((item) => {
          length++;
          return (
            <div>
            <div 
              key={item.title + item.date}
              className="notes"
              style={this.style(length)}
            >
              <p>{length > 7 && "Слишком много заметок!!!!"}</p>
              <h3>{item.title}</h3>
              <h4>{item.date}</h4>
              <p>{item.desc}</p>
              <div className = "note">
              <button onClick={() => this.setState({ edit: item })}>
                Редактировать
              </button>
              </div>
              {this.state.edit === item && (
                <EditNote note={item} edit={this.edit} />
              )}
            </div>
            </div>
          );
        })}
      </>
    );
  }
}

class EditNote extends React.Component {
  onSubmit = () => {
    let note = {
      title: this.state.title,
      date: this.props.note.date,
      desc: this.state.desc,
    };
    this.props.edit(this.props.note, note);
  };
  handle = (target, e) => {
    this.setState({ [target]: e.target.value });
  };
  render() {
    return (
      <form class = "note" onSubmit={this.onSubmit}>
        <input  
          type="text"
          placeholder="заголовок"
          onChange={this.handle.bind(this, "title")}
          defaultValue={this.props.note.title}
        />
        <input  
          type="text"
          placeholder="дата"
          readOnly
          defaultValue={this.props.note.date}
        />
        <textarea
          placeholder="заметка"
          onChange={this.handle.bind(this, "desc")}
          defaultValue={this.props.note.desc}
        />
        <input type="submit" value="Исправить" />
      </form>
    );
  }
}