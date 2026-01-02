import React from "react";

  class Clock extends React.Component {
    constructor(props) {
      super(props);
      this.state = { date: new Date() };
      this.format = parseInt(props.format);
      this.timeZone = parseFloat(props.timeZone);
    }

    componentDidMount() {
      this.timerID = setInterval(() => this.tick(), 1000);
    }

    componentWillUnmount() {
      clearInterval(this.timerID);
    }

    tick() {
      this.setState({
        date: new Date(),
      });
    }

    myFunction() {
      let date = new Date();

      let hours = date.getHours();

      let minutes = date.getMinutes();

      let newformat = hours >= 12 ? "PM" : "AM";

      hours = hours % 12;

      minutes = minutes < 10 ? "0" + minutes : minutes;

      return (
        <div>
          {hours}:{minutes} {newformat}
        </div>
      );
    }

    check() {
      if (this.format === 12) {
        return <div> 12-часовой формат: {this.myFunction()}</div>;
      }
    }

    tmz() {
      if (this.timeZone !== 0) {
        let nd = new Date(this.state.date.getTime() + this.state.date.getTimezoneOffset() * 60000 + 3600000 * Number(this.timeZone));
        return (
          <div>
            <p>TimeZone:{this.timeZone} UTC</p>
            <p>Time:{nd.toLocaleTimeString()}</p>
          </div>
        );
      }
    }
    render() {
      return (
        <div>
          <p>Сегодня {this.state.date.toLocaleDateString()}</p>
          <p>Сейчас {this.state.date.toLocaleTimeString()}</p>
          <p>
            {this.check()}
            {this.tmz()}
          </p>
          
        </div>
      )
    }
  }

  class Clocks extends React.Component {
    render(){
      return(
        <div>
            <Clock format="12" timeZone="+5.5" />
          </div>
      )
    }
  }

export default Clocks;
