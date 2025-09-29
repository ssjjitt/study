import React from "react";
import "./S.css";

class Notes extends React.Component {
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

  style(date) {
    const { selectedDate } = this.props;
    if (selectedDate && selectedDate.toLocaleDateString() === date) {
      return { background: "#ffed86" };
    }
    return { background: "#ffffff" };
  }

  handle = (target, e) => {
    this.setState({ [target]: e.target.value });
  };

  addNote = () => {
    const { title, desc } = this.state;
    const newNote = {
      title,
      date: this.props.date.toLocaleDateString(),
      desc,
    };
    this.setState((prevState) => ({
      notes: [...prevState.notes, newNote],
      title: "",
      date: prevState.date,
      desc: "",
    }));
    this.props.addNote(newNote);
  };

  deleteFirst = () => {
    const [firstNote, ...remainingNotes] = this.state.notes;
    this.setState({
      notes: remainingNotes,
    });
    if (firstNote) {
      this.props.deleteNoteByDate(firstNote.date);
    }
  };

  deleteLast = () => {
    const { notes } = this.state;
    const lastNote = notes[notes.length - 1];
    this.setState({
      notes: notes.slice(0, notes.length - 1),
    });
    if (lastNote) {
      this.props.deleteNoteByDate(lastNote.date);
    }
  };

  deleteAll = () => {
    this.setState({ notes: [] }, () =>
      this.props.deleteAllNotesByDate(this.state.notes.map((note) => note.date))
    );
  };

  form() {
    if (this.props.showForm) {
      return (
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
      );
    }
  }

  edit = (note, newNote) => {
    const { notes } = this.state;
    const updatedNotes = notes.map((n) => (n === note ? newNote : n));
    this.setState({
      notes: updatedNotes,
      edit: null,
    });
  };

  render() {
    const { notes } = this.state;
    const length = notes.length;

    return (
      <>
        {this.form()}
        {length > 0 && (
          <div className="note">
            <button onClick={this.deleteFirst}>Удалить первую</button>
            <button onClick={this.deleteLast}>Удалить последнюю</button>
            <button onClick={this.deleteAll}>Удалить все</button>
          </div>
        )}
        {notes.map((item, index) => {
          const isLastNote = index === length - 1;
          const { title, date, desc } = item;
          return (
            <div key={title + date}>
              <div
                className="notes"
                style={this.style(date)}
              >
                {length > 7 && <p>Слишком много заметок!!!!</p>}
                <h3>{title}</h3>
                <h4>{date}</h4>
                <p>{desc}</p>
                <div className="note">
                  <button onClick={() => this.setState({ edit: item })}>
                    Редактировать
                  </button>
                </div>
                {this.state.edit === item && (
                  <EditNote note={item} edit={this.edit} />
                )}
              </div>
              {isLastNote && (
                <div className="empty-note" style={this.style("")}></div>
              )}
            </div>
          );
        })}
      </>
    );
  }
}

export default Notes;