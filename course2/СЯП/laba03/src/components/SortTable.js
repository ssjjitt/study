import { Component } from "react";

export class SortTable extends Component {
  constructor(props) {
    super(props);
    this.sorted = { name: true, price: true, inStock: true };
    this.state = { array: this.goods };
  }
  goods = [
    { id: "Butter", name: "Butter", price: 0.9, inStock: 9 },
    { id: "Cheese", name: "Cheese", price: 4.9, inStock: 20 },
    { id: "Fansy French Cheese", name: "Fansy French Cheese", price: 99, inStock: 2 },
    { id: "Heavy Cream", name: "Heavy Cream", price: 3.9, inStock: 1 },
    { id: "Milk", name: "Milk", price: 1.9, inStock: 32 },
    { id: "Sour Cream", name: "Sour Cream", price: 2.9, inStock: 0 },
    { id: "Yoghurt", name: "Yoghurt", price: 10, inStock: 12 },
  ];
  styles = {
    td: {
      padding: "10px 20px",
      border: "1px solid",
    },
    table: {
      margin: "100px",
      borderCollapse: "collapse",
    },
  };
  sort(byWhat) {
    let direction = this.sorted[byWhat] ? 1 : -1,   
      goodsCopy = [...this.goods].sort(function (a, b) {
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
  table() {
    let stringNumber = 0;
    return this.state.array.map((item) => {
      let inStockStyle = {};
      if (item.inStock < 3) inStockStyle = { background: "yellow" };
      if (item.inStock === 0) inStockStyle = { background: "red" };
      return (
        <tr key={item.id}>
          <td style={this.styles.td}>{++stringNumber}</td>
          <td style={this.styles.td}>{item.name}</td>
          <td style={this.styles.td}>${item.price}</td>
          <td style={Object.assign({}, this.styles.td, inStockStyle)}>
            {item.inStock}
          </td>
        </tr>
      );
    });
  }
  head = [
    <tr>
      <td style={this.styles.td}>№</td>
      <td style={this.styles.td}>
        <button onClick={() => this.sort("name")}>Name</button>
      </td>
      <td style={this.styles.td}>
        <button onClick={() => this.sort("price")}>Price</button>
      </td>
      <td style={this.styles.td}>
        <button onClick={() => this.sort("inStock")}>In Stock</button>
      </td>
    </tr>,
  ];
  render() {
    return (
      <table style={this.styles.table}>
        {this.head}
        {this.table()}
      </table>
    );
  }
}
