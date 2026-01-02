import React from "react";
// при передаче компонента Clock в render(), React вызывает конструктор компонента
const Task_1 = () => {  // Task_1 - jsx элемент, который будет содержать нагу компоненту
  class Clock extends React.Component { // Clock определен как класс, а не как функция. Метод render() будт вызываться при каждом обновлении
    constructor(props) { // добавили базовый конструктор, классовые компоненты всега должны вызывать базовый конструктор с аргументом props
      // здесь нельзя использовать this.
      super(props); // передаем props, чтобы базовый конструктор мог иинициализировать this.props, указывает на коструктор родительского класса(на реализацию react.components)
      // здесь можно
      this.state = { date: new Date() }; // указали начальное состояние в переменной this.state, так как Clock должен отображать текущее время
      this.format = props.format;
      this.timeZone = parseFloat(props.timeZone);   // берем строку - возвращаем число
    }
// МЕТОДЫ ЖИЗНЕННОГО ЦИКЛА
// в приложениях, где много компонентов нужно освобождать ресурсы, когда компоненты удаляются
    componentDidMount() {
      // метод запускается после того, как компонент отрендерился в dom
      // установим таймер каждый раз, когда происходит монтирование
      this.timerID = setInterval(() => this.tick(), 1000);  // сохраняем id таймера в this
    }

    componentWillUnmount() {    // когда dom узел удаляется, чтобы избежать утечки ресурсов будем сбрасывать таймер при каждом размонтировании
      clearInterval(this.timerID);
    }

    tick() {    // метод tick() запускается таймером каждую секунду и вызывает this.setState()
      this.setState({    // this.setState планирует обновление внутреннего состояния компонента
        date: new Date(),
      });
    }
    myFunction() {      // метод для нового формата времени и таймзоны
      let date = new Date();    // создадим новую переменную date, в которой будут храниться данные о системном времени из функции-конструктора new Date()

      let hours = date.getHours();  // получаем часы из объекта и записывает в переменную

      let minutes = date.getMinutes();    // минуты
// далее получим переменную и разметку для 12-часового формата времени 
      let newformat = hours >= 12 ? "PM" : "AM";  

      hours = hours % 12; // делим с остатком на 12, получаем числа от 1 до 12

      hours = hours ? hours : 12;

      minutes = minutes < 10 ? "0" + minutes : minutes; // для вывода нуля, например, для времени 12:09
// далее возвращаем разметку с нашим 12-часовым форматом времени
      return (
        <div>
          {hours}:{minutes} {newformat}
        </div>
      );
    }
// метод check проверяет аттрибут format в компоненте и будет возвращать созданный нами метод MyFunction(), если мы укажем 12-часовой формат
    check() {
      if (this.format === 12) {
        return <div>{this.myFunction()}</div>;
      }
    }
// метод для настройки таймзоны
    tmz() {
      if (this.timeZone !== 0) {    // если мы ввели таймзону не равную нулю 

        let nd = new Date(this.state.date.getTime() + this.state.date.getTimezoneOffset() * 60000 + 3600000 * Number(this.timeZone));

        return (
          <div>
            TimeZone:{this.timeZone}
            <br></br>Time:{nd.toLocaleTimeString()}
          </div>
        );
      }
    }
    render() {  // вызывает метод рендер, таким образом react узнает, что отобразить на экране
      // первый этап переноса date из пропсов в состояние
      // заменили this.props на this.state в методе render()
      
      // this.state.date.toLocaleDateString() и this.state.date.toLocaleTimeString() вывод текущего СИСТЕМНОГО времени
      // check() возвращает 12-часовой формат
      // tmz() возвращает TimeZone и Time
      return (
        <div>
          <h1>Задание 1</h1>
          <div>
            Сегодня{this.state.date.toLocaleDateString()}   
            Сейчас{this.state.date.toLocaleTimeString()}
         </div>
          {this.check()}
          {this.tmz()}
        </div>
      );
    }
  }

  return (
    <div>
      <Clock format="12" timeZone="-5" />
    </div>
  );
};

export default Task_1;
