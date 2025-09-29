import React from "react";
import { Component } from "react";
import "./Comments.css";
import one from "./1.jpg";
import two from "./2.jpg";
import three from "./3.jpg";
import four from "./4.jpg";
import five from "./5.jpg";
import six from "./6.jpg";

export class Comments extends Component {
  constructor(props) {
    super(props);
    this.state = {
      img: one,
      comments: [
        {
          name: "",
          avatar: "",
          email: "",
          message: "",
          secretWord: "",
          date: new Date(),
        },
      ],
      delete: null,
      edit: null,
      info: null,
    };
  }
  avatars = [
    {
      img: "./1.jpg",
      name: "геленджик",
    },
    {
      img: "./2.jpg",
      name: "дефтонс",
    },
    {
      img: "./3.jpg",
      name: "дефтонс v2",
    },
    {
      img: "./4.jpg",
      name: "ложка",
    },
    {
      img: "./5.jpg",
      name: "байкер",
    },
    {
      img: "./6.jpg",
      name: "пиво",
    },
  ];



  onSubmit = (e) => {
    e.preventDefault();
    if (
      (this.name.value &&
        this.email.value &&
        this.message.value &&
        this.secretWord.value) === ""
    ) {
      alert("Не все поля заполнены");
      return;
    }
    let comment = {
      name: this.name.value,
      avatar: this.state.img,
      email: this.email.value,
      message: this.message.value,
      secretWord: this.secretWord.value,
      date: new Date(),
    };
    this.setState({
      comments: [...this.state.comments, comment],
    });
    this.name.value = null;
    this.email.value = null;
    this.message.value = null;
    this.secretWord.value = null;
  };



  comments() {
    return this.state.comments.map((comment) => {
      return (
        <div className="comment" key={comment.message}>
          <div className="staticinfo">
            <img
              style={{ height: "100px", width: "100px" }}
              src={comment.avatar}
              alt="avatar"
              id="img"
            />
            <div className="NameMessage">
              <div className="name">
                Пользователь: <span id="sp1">{comment.name}</span>
              </div>
              <div className="message">
                Комментарий: <span id="sp1">{comment.message}</span>
              </div>
            </div>
          </div>
          <div className="divBut">
            <button
              className="fill"
              onClick={() =>
                this.setState({ edit: comment, delete: null, info: null })
              }
            >
              Редактировать
            </button>
            <div className="inf">
              {comment === this.state.edit ? (
                <CommentsEdit
                  comment={this.state.edit}
                  editComment={this.editComment}
                />
              ) : null}
            </div>
            <button
              className="fill"
              onClick={() =>
                this.setState({ delete: comment, edit: null, info: null })
              }
            >
              Удалить
            </button>
            <div className="inf">
              {comment === this.state.delete ? (
                <CommentsDel
                  deleteComment={this.deleteComment}
                  comment={this.state.delete}
                />
              ) : null}
            </div>
            <button
              className="fill"
              onClick={() =>
                this.setState({ info: comment, edit: null, delete: null })
              }
            >
              Инфо
            </button>
            <div className="inf">
              {comment === this.state.info ? (
                <CommentsInfo comment={this.state.info} />
              ) : null}
            </div>
          </div>
        </div>
      );
    });
  };



  deleteComment = (comment) => {
    for (let i = 0; i < this.state.comments.length; i++) {
      if (this.state.comments[i] === comment) {
        return this.setState(({ comments }) => ({
          comments: [...comments.slice(0, i), ...comments.slice(i + 1)],
          delete: null,
        }));
      }
    }
  };



  editComment = (comment, text) => {
    for (let i = 0; i < this.state.comments.length; i++) {
      if (this.state.comments[i] === comment) {
        comment.message = text;
        comment.date = new Date();
        return this.setState(({ comments }) => ({
          comments: [
            ...comments.slice(0, i),
            comment,
            ...comments.slice(i + 1),
          ],
          edit: null,
        }));
      }
    }
  };



  selectImg = (e) => {
    switch (e.target.value) {
      case "геленджик":
        this.setState({ img: one });
        break;
      case "дефтонс":
        this.setState({ img: two });
        break;
      case "дефтонс v2":
        this.setState({ img: three });
        break;
      case "ложка":
        this.setState({ img: four });
        break;
      case "байкер":
        this.setState({ img: five });
        break;
      case "пиво":
        this.setState({ img: six });
        break;
    }
  };



  render() {
    return (
      <>
        <form onSubmit={this.onSubmit} id="f1">
          <input
            ref={(e) => (this.name = e)}
            type="text"
            placeholder="Имя пользователя"
            name=""
          />

          <select onChange={this.selectImg}>
            {this.avatars.map((avatar) => {
              return (
                <option key={avatar.img} value={avatar.name}>
                  {avatar.name}
                </option>
              );
            })}
          </select>
          <Links value={this.state.value} />

          <img id="img4" src={this.state.img} />
          <input
            ref={(e) => (this.email = e)}
            type="email"
            placeholder="Email"
          />
          <textarea placeholder="Комментарий" ref={(e) => (this.message = e)} />
          <input
            ref={(e) => (this.secretWord = e)}
            type="text"
            placeholder="Секретное слово"
          />
          <input type="submit" value="Отправить" />
        </form>
        {this.comments()}
      </>
    );
  }
}



class Links extends React.Component {
  switchCase() {
    let links = [];
    let value = this.props.value;

    switch (value) {
      case "1":
        links.push("./1.jpg");
        break;
      case "2":
        links.push("./2.jpg");
        break;
      case "3":
        links.push("./3.jpg");
        break;
      case "4":
        links.push("./4.jpg");
        break;
      case "5":
        links.push("./5.jpg");
        break;
      case "6":
        links.push("./6.jpg");
        break;
      default:
        break;
    }
    return (
      <div>
        <ul>
          {links.map((item) => {
            return <img src={item}></img>;
          })}
        </ul>
      </div>
    );
  }

  render() {
    return <div>{this.switchCase()}</div>;
  }
}



class CommentsDel extends Component {
  onSubmit = (e) => {
    e.preventDefault();
    if (this.yourWord.value === this.props.comment.secretWord) {
      return this.props.deleteComment(this.props.comment);
    }
    alert("Неправильное секретное слово!");
  };
  render() {
    return (
      <form onSubmit={this.onSubmit}>
        <input
          type="text"
          ref={(e) => (this.yourWord = e)}
          placeholder="Секретное слово"
        />
        <input type="submit" value="Подтвердить" />
      </form>
    );
  }
}



class CommentsEdit extends Component {
  onSubmit = (e) => {
    e.preventDefault();
    this.props.editComment(this.props.comment, this.yourComment.value);
  };
  render() {
    return (
      <form onSubmit={this.onSubmit}>
        <div className="name">
          Пользователь: <span id="sp1">{this.props.comment.name}</span>
        </div>
        <div className="message">
          Email: <span id="sp1">{this.props.comment.email}</span>
        </div>
        <textarea
          ref={(e) => (this.yourComment = e)}
          defaultValue={this.props.comment.message}
        />
        <input type="submit" value="Подтвердить" />
      </form>
    );
  }
}



class CommentsInfo extends Component {
  render() {
    let comment = this.props.comment;
    return (
      <>
        <div className="name">
          Пользователь: <span id="sp1">{comment.name}</span>
        </div>
        <div className="date">
          Дата изменения: <span id="sp1">{comment.date.toLocaleString()}</span>
        </div>
        <div className="message">
          Email: <span id="sp1">{comment.email}</span>
        </div>
      </>
    );
  }
}
