import React from "react";

export class SignUpEmailInput extends React.Component {
  constructor(props) {    
    super(props);
    this.state = { email: "" }
  };
  inputHandler = (e) => {   
    this.setState({ email: e.target.value });
    let check = /\S+@\S+\.\S+/,
    checked = check.test(e.target.value)
    this.props.disableBtn(!checked)
  };
  render() {
    return (
      <input
        id='inp'
        type="email"
        name="email"
        placeholder="yourpost@smth.smth"
        value={this.state.email}
        onChange={this.inputHandler}
      />
    );
  }
}