import { Component } from "react";
import "./SortTable.css";
import one from "./1.webp";
import two from "./2.jfif";
import three from "./3.webp";
import four from "./4.jpg";
import five from "./5.jpg";
import six from "./6.jpg";

export class SortTable extends Component {
  constructor(props) {
    super(props);
    this.sorted = { name: true, price: true, inStock: true, discount: true };
    this.state = { array: this.goods };
  }

  goods = [
    {
      id: "first",
      name: "Маленький принц",
      price: 12,
      inStock: 3,
      img: one,
      desc: "Маленький принц - аллегорическая повесть-сказка, наиболее известное произведение Антуана де Сент-Экзюпери. Сказка рассказывает о Маленьком принце, который посещает различные планеты в космосе, включая Землю. Книга обращается к темам одиночества, дружбы, любви и утраты.",
      new: true,
      discount: 15,
    },
    {
      id: "second",
      name: "Бесы",
      price: 20,
      inStock: 2,
      img: two,
      desc: "Небольшой уездный городок. Мысли Степана Верховенского — организатора дружеского кружка отечественных либералов — заняты красавицей Дарьей Шатовой. Но его надежды на светлое будущее с девушкой обрывает приезд Николая Ставрогина — загадочного молодого человека с темным прошлым...",
      new: false,
      discount: 50,
    },
    {
      id: "third",
      name: "Бесы Лудена",
      price: 18,
      inStock: 18,
      img: three,
      desc: "Городок Луден, в котором внезапно сходят с ума монахини урсулинской обители. В духовном и сексуальном совращении сестер обвинен католический священник Урбен Грандье. Страстный женолюб и жизнелюб, харизматичный и образованный человек, он должен понести суровое наказание за колдовство и отправиться на костер.",
      new: false,
      discount: 20,
    },
    {
      id: "fourth",
      name: "Своя комната",
      price: 10,
      inStock: 3,
      img: four,
      desc: "Аннотация к книге 'Своя комната'. В своем знаменитом эссе Вирджиния Вулф утверждает: главное, чего не хватало женщинам для творчества, - это Своя комната, чтобы уединиться, и минимальный доход, чтобы не голодать. Таких элементарных вещей не могла себе позволить ни одна из ее великих предшественниц.",
      new: false,
      discount: 25,
    },
    {
      id: "fifth",
      name: "Скорбь Сатаны",
      price: 11,
      inStock: 0,
      img: five,
      desc: "Молодой писатель Джеффри Темпест, прозябающий в нищете и безвестности, продает душу Сатане и получает от Князя Тьмы все, о чем только мечтал… точнее, почти все. Теперь светское общество, ранее им пренебрегавшее, лежит у его ног. К его услугам несметное состояние, любовь прекрасной девушки, роскошь и удовольствия.",
      new: false,
      discount: 40,
    },
    {
      id: "sixth",
      name: "Убить пересмешника",
      price: 13,
      inStock: 3,
      img: six,
      desc: "История судебного процесса по делу чернокожего парня, обвиненного в насилии над белой девушкой. Но прежде всего – история переломной эпохи, когда ксенофобия, расизм, нетерпимость и ханжество, присущие американскому югу, постепенно уходят в прошлое. 'Ветер перемен' только-только повеял над Америкой.",
      new: false,
      discount: 90,
    },
  ];

  sort(byWhat) {
    let direction = this.sorted[byWhat] ? 1 : -1,
      goodsCopy = [...this.goods].sort(function (a, b) {
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

  table() {
    let stringNumber = 0;
    return this.state.array.map((item) => {
      let inStockStyle = {};
      if (+item.inStock < 15)
        inStockStyle = { background: "#dcff5c", color: "black" };
      if (+item.inStock === 0)
        inStockStyle = { background: "#ff7979", color: "black" };
      return (
        <tbody key={item.id}>
          <tr>
            <td>{++stringNumber}</td>
            <td>{item.name}</td>
            <td>
              <img src={item.img} style={{ width: "30px" }} alt="" />
            </td>
            <td>{item.price}BYN</td>
            <td style={Object.assign({}, inStockStyle)}>{item.inStock}</td>
            <td>{item.discount}%</td>
            <td>{String(item.new)}</td>
          </tr>
        </tbody>
      );
    });
  }
  head = [
    <thead key = {1}>
      <tr className="tableNameRow">
        <td className="tableName">N</td>
        <td className="tableName">
          <button onClick={() => this.sort("name")}>Имя</button>
        </td>
        <td className="tableName">
          <h5>Picture</h5>
        </td>
        <td className="tableName">
          <button onClick={() => this.sort("price")}>Цена</button>
        </td>
        <td className="tableName">
          <button onClick={() => this.sort("inStock")}>Количество</button>
        </td>
        <td className="tableName">
          <button onClick={() => this.sort("discount")}>Скидка</button>
        </td>
        <td className="tableName">
          <h5>Новинки</h5>
        </td>
      </tr>
    </thead>,
  ];
  render() {
    return (
      <table className="table">
        {this.head}
        {this.table()}
      </table>
    );
  }
}
