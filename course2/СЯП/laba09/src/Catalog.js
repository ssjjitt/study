import { SortTable } from "./SortTable.js";
import React, { Component } from "react";
import "./Catalog.css";
import { Search } from "./Search";
import symb from "./symbol.png";
import kolvo from "./kolvo.png";
import sale from "./sale.png";
import money from "./money.png";
export class Catalog extends Component {
  constructor(props) {
    super(props);
    this.sortTableRef = React.createRef();
    this.state = { loaded: false, search: "", searchParameter: "partial" };
    this.sorted = { name: true, price: true, inStock: true, discount: true };
  }
  componentDidMount() {
    this.setState({ loaded: true, array: this.sortTableRef.current.goods });
  }

  sort(byWhat) {
    let direction = this.sorted[byWhat] ? 1 : -1,
      goodsCopy = [...this.sortTableRef.current.goods].sort(function (a, b) {
        if (a.new || b.new) return 0;
        if (a[byWhat] > b[byWhat]) {
          return direction;
        }
        if (a[byWhat] < b[byWhat]) {
          return direction * -1;
        }
        return 0;
      });
    this.sorted[byWhat] = !this.sorted[byWhat];
    this.setState({ array: goodsCopy });
  }

  sorts() { 
    return (
      <>
        <div className="divBut">
          <img
            onClick={() => this.sort("name")}
            className="sortImg"
            src={symb}
          />
          <img
            onClick={() => this.sort("price")}
            className="sortImg"
            src={money}
          />
          <img
            onClick={() => this.sort("inStock")}
            className="sortImg"
            src={kolvo}
          />
          <img
            onClick={() => this.sort("discount")}
            className="sortImg"
            src={sale}
          />
        </div>
      </>
    );
  }


  goods() {
    return this.state.array
      .filter((item) => {
        if (!this.state.search) return item;
        switch (this.state.searchParameter) {
          case "partial":
            if (
              item.name.toLowerCase().includes(this.state.search.toLowerCase())
            ) {
              return item;
            }
            break;
          case "full":
            if (item.name.toLowerCase() === this.state.search.toLowerCase()) {
              return item;
            }
            break;
          default:
            return item;
        }
      })
      .map((item) => {
        return (
          <div key={item.id} className="one_good">
            <div className="text">
              <div className="discount">
                {item.new && (
                  <div className="new">
                    <div>Новинка</div>
                  </div>
                )}
                <div className="disc">
                  <div>{item.discount}%</div>
                </div>
              </div>
              <img className="imageCatalog" src={item.img} alt="" />
              <div className="info">
                <div className="name">{item.name}</div>
                <div className="prices">
                  {item.discount && (
                    <div>
                      <span className="newprice">
                        {" "}
                        {(item.price * (100 - item.discount)) / 100}BYN{" "}
                      </span>
                      <span className="oldprice">{item.price}BYN </span>
                    </div>
                  )}
                </div>
                <div className="count">
                  <div>Количество: {item.inStock} шт.</div>
                </div>
                <div className="descr">{item.desc}</div>
              </div>
            </div>
          </div>
        );
      });
  }

  search = (item) => {
    this.setState({ search: item });
  };
  searchParameter = (item) => {
    this.setState({ searchParameter: item });
  };
  render() {
    return (
      <>
        <Search search={this.search} searchParameter={this.searchParameter} />
        {this.state.loaded && this.sorts()}
        <div className="catalog">{this.state.loaded && this.goods()}</div>
        <SortTable ref={this.sortTableRef} />
      </>
    );
  }
}
