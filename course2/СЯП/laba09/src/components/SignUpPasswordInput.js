import React from "react";
import "./SignUpForm.css";

export class SignUpPasswordInput extends React.Component {
  constructor(props) {
    super(props);
    this.state = { password: "", background: "", disableBtn: true };
  }
  handlePassword = (e) => {
    this.setState({ password: e.target.value });
  };

  handleRepeat = (e) => {
    if (this.state.password === e.target.value) {
      this.setState({ disableBtn: false }, () =>
        this.props.disableBtn(this.state.disableBtn)
      );
    } else {
      this.setState({ disableBtn: true }, () =>
        this.props.disableBtn(this.state.disableBtn)
      );
    }
  };

  checkIfRepeat() {
    let password = this.state.password;
    let display = "none";
    if (!password.length) {
      display = "none";
      return <div style={{ display: display }}>Пароли не совпадают</div>;
    }
    if (this.state.disableBtn) {
      display = "block";
      return <div style={{ display: display }}>Пароли не совпадают</div>;
    }
  }

  checkPassword() {
    let password = this.state.password,
      check = 0,
      width = "",
      transition = "0.3s",
      background = "";
    if (password.match(/\d/g)) check++;
    if (password.match(/[a-z]/g)) check++;
    if (password.match(/[A-Z]/g)) check++;
    if (password.match(/\W/g)) check++;// Соответствует любому не цифробуквенному символу.

    if (!password.length) width = "0%";
    else if (password.length < 6 && check < 3) {
      width = "25%";
      background = "red";
    } else if (password.length < 6 && check >= 3) {
      width = "30%";
      background = "red";
    } else if (password.length >= 6 && check < 3) {
      width = "35%";
      background = "orange";
    } else if (password.length >= 6 && check > 1 && check < 4) {
      width = "65%";
      background = "green";
    } else if (password.length >= 8 && check >= 3) {
      width = "100%";
      background = "green";
    } else if (password.length >= 6 && check === 4) {
      width = "100%";
      background = "green";
    }
    return (
      <div className="progress_bar_bg">
        <div
          className="progress_bar"
          style={{
            width: width,
            background: background,
            transition: transition,
          }}
        />
      </div>
    );
  }
  render() {
    return (
      <>
        <input
          id="inp4"
          type="password"
          placeholder="Введите ваш пароль"
          onChange={this.handlePassword}
        />
        <input
          id="inp5"
          type="password"
          placeholder="Повторите пароль"
          onChange={this.handleRepeat}
        />
        {this.checkIfRepeat()}
        {this.checkPassword()}
      </>
    );
  }
}
