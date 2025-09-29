import React from "react";
import { Component } from "react";
import "./Comments.css";

export class Comments extends Component {
  constructor(props) {
    super(props);
    this.state = {
      img: "",
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
    this.onImageChange = this.onImageChange.bind(this);
  };
  avatars = [
    {
      img: "1.jpg",
      name: "1",
    },
    {
      img: "2.jpg",
      name: "2",
    },
    {
      img: "3.jpg",
      name: "3",
    },
    {
      img: "4.jpg",
      name: "4",
    },
    {
      img: "5.jpg",
      name: "5",
    },
    {
      img: "6.jpg",
      name: "6",
    },
  ];

  onSubmit = (e) => {   // Вызов функции при отправке формы
    e.preventDefault(); // preventDefault() — метод события. Этот метод отменяет поведение браузера по умолчанию, которое происходит при обработке события.
    // Например, при нажатии на ссылку, мы переходим по адресу этой ссылки. Вызов preventDefault() отменит это поведение.
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
  comments() { // метод вызывается в самом конце - {this.comments()}
    return this.state.comments.map((comment) => {
      return (
        <div className="comment" key={comment.message}>




            <div className="staticinfo">    // информация справа от картинки
            <img
                   style={{ height: "100px", width: "100px" }}
                    src={comment.avatar}
                    alt="avatar"
                    id="img"
                />
              <div className="NameMessage">
                <div className="name">Пользователь:  <span id="sp1">{comment.name}</span></div>
                <div className="message">Комментарий:  <span id="sp1">{comment.message}</span></div>
              </div>  
            </div>




          <div className="divBut">



              <button className="fill" onClick={() => this.setState({ edit: comment, delete: null, info: null })}>Редактировать</button>    // нажимаем кнопочку в результате чего свойство edit будет аналогично comment
              <div className="inf">
                  {comment === this.state.edit ? // соответственно здесь условие будет выполняться, а значит при условном рендеринге будет отрисован компонент
                  <CommentsEdit 
                    comment={this.state.edit} // из-за того, что мы передаем пропсы, компонент понимает, какой именно комментарий мы редактируем
                    editComment={this.editComment}
                  />
                  : null}
              </div>

                // аналогично со следующими двумя кнопками
              <button className="fill" onClick={() => this.setState({ delete: comment, edit: null, info: null })}>
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


              <button className="fill" onClick={() => this.setState({ info: comment, edit: null, delete: null })}>Инфо</button>
              <div className="inf">
                  {comment === this.state.info ? (
                    <CommentsInfo comment={this.state.info} />
                  ) : null}
              </div>
          </div>
        
        </div>
      );
    });
  }
  deleteComment = (comment) => {
    for (let i = 0; i < this.state.comments.length; i++) {
      if (this.state.comments[i] === comment) {
        return this.setState(({ comments }) => ({
          comments: [...comments.slice(0, i), ...comments.slice(i + 1)],
          delete: null
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
          comments: [...comments.slice(0, i), comment, ...comments.slice(i + 1)],
          edit: null
        }));
      }
    }
  }
  onImageChange = event => {
    if (event.target.files && event.target.files[0]) {
      let img = event.target.files[0];
      this.setState({
        img: URL.createObjectURL(img)
      });
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
          <input type="file" name="myImage" onChange={this.onImageChange}/>
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

class CommentsDel extends Component {
  onSubmit = (e) => {
    e.preventDefault()
    if (this.yourWord.value === this.props.comment.secretWord) {
      return this.props.deleteComment(this.props.comment);
    }
    alert("Неправильное секретное слово!")
  }
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
  onSubmit = e => {
    e.preventDefault()
    this.props.editComment(this.props.comment, this.yourComment.value)
  }
  render() {
    return (
      <form onSubmit={this.onSubmit}>
        <div className="name">Пользователь:  <span id="sp1">{this.props.comment.name}</span></div>
        <div className="message">Email:  <span id="sp1">{this.props.comment.email}</span></div>
        <textarea ref={(e) => (this.yourComment = e)} defaultValue={this.props.comment.message} />
        <input type="submit" value="Подтвердить" />
      </form>
    )
  }
}

class CommentsInfo extends Component {
  render() {
    let comment = this.props.comment;
    return (
      <>
        <div className="name">Пользователь:  <span id="sp1">{comment.name}</span></div>
        <div className="date">Дата изменения:  <span id="sp1">{comment.date.toLocaleString()}</span></div>
        <div className="message">Email:  <span id="sp1">{comment.email}</span></div>
      </>
    );
  }
}
