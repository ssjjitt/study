import React from "react";
import "./Catalog.css";
export class Search extends React.Component {
  onChange = (e) => {
    this.setState(() => this.props.search(e.target.value));
  };
  onClick = (target) => {
    this.setState(() => this.props.searchParameter(target));
  };
  render() {
    return (
      <div className="search">
        <input
          id="inp"
          type="search"
          placeholder="Поиск"
          onChange={this.onChange}
        />
        <br />
        <div className="inner divRad">
          <label className="SearcLabel rad-label">
            <input
              type="radio"
              className="rad-input"
              id="partial"
              name="search"
              defaultChecked
              onClick={this.onClick.bind(this, "partial")}
            />
            <div className="rad-design"></div>
            <div className="rad-text">Частичный ввод</div>
          </label>{" "}
          <br />
          <label className="SearcLabel rad-label">
            <input
              className = "rad-input"
              type="radio"
              id="full"
              name="search"
              onClick={this.onClick.bind(this, "full")}
            />
            <div className="rad-design"></div>
            <div className="rad-text">Полный ввод</div>
          </label>{" "}
        </div>
      </div>
    );
  }
}
