import { Component } from "react";

export class SortTable extends Component {      // сразу экспортируем
  constructor(props) {  // вызывает конструктор базового класса для того чтобы указать начальное состояние
    super(props);       // чтобы получить доступ к this
    this.sorted = { name: true, price: true, inStock: true };       // устранавливает значения для пропса
    this.state = { array: this.goods };             // устанавливаем начальное состояние как ассоциативный массив
  }
  goods = [
    { id: "Milk", name: "Milk", price: 0.8, inStock: 0 },
    { id: "Butter", name: "Butter", price: 1.3, inStock: 13 },
    { id: "Coffee", name: "Coffee", price: 12, inStock: 23 },
    { id: "Tea", name: "Tea", price: 13, inStock: 2 },
    { id: "Sugar", name: "Sugar", price: 1.2, inStock: 4 },
    { id: "Apples", name: "Apples", price: 1, inStock: 16 },
    { id: "Cheese", name: "Cheese", price: 10, inStock: 9 },
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
  // сорт - изначально это метод, который сортирует в алфавитном порядке
  // может принимать доп параметры в виде функций
  sort(byWhat) {        
    let direction = this.sorted[byWhat] ? 1 : -1,       // переменная для изменения направления сортировки возрастание/убывание
      goodsCopy = [...this.goods].sort(function (a, b) {            // создаем копию массива с помощью spread оператора и вновь вызываем sort. 
        if (a[byWhat] > b[byWhat]) {    
          return direction;
        }
        if (a[byWhat] < b[byWhat]) {
          return direction * -1;
        }
        return 0;   // без сортировки
      });
    this.sorted[byWhat] = !this.sorted[byWhat];
    this.setState({ array: goodsCopy });
  }
  table() {
    let stringNumber = 0;
    return this.state.array.map((item) => {
      let inStockStyle = {};
      if (+item.inStock < 3) inStockStyle = { background: "yellow" };
      if (+item.inStock === 0) inStockStyle = { background: "red" };
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
  head = [      // jsx элемент возвращающий шапку таблицы
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
