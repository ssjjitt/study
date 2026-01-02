import React from "react";
import PropTypes from "prop-types"    

export class SignUpEmailInput extends React.Component {
  state = {
    email: ""
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
        id='inp0'
        type="email"
        name="email"
        placeholder="Email"
        value={this.state.email}
        onChange={this.inputHandler}
      />
    );
  }
}

SignUpEmailInput.propTypes = {
  disableBtn: PropTypes.bool,
  months: PropTypes.array,
  parentState: PropTypes.object,
  str: PropTypes.string,
  num: PropTypes.number,
};


