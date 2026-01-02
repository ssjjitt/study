import React from "react";
import "./Calendar.css" 

export class Calendar extends React.Component {   
  constructor(props) {    // вызываем контруктор базового класса и передаем props в качестве параметра
    super(props);   // используем super чтобы получить доступ к this
    this.state = { date: new Date(), selectedDays: [] };  // устанавливаем начальное состояние
  }
  // функция - метод класса, для изменения для изменения месяцев при нажатии на кнопку
  changeDate = (value) => {     
    this.setState({ date: value });  // this.setState планирует обновление внутреннего состояния компонента
  };
  
  selectDays = (day) => {       // выбранный день
    for (let i = 0; i < this.state.selectedDays.length; i++) {  // перебираем массив выбранных дней    
      if (
        day.getDate() === this.state.selectedDays[i].getDate() &&
        day.getMonth() === this.state.selectedDays[i].getMonth() &&
        day.getFullYear() === this.state.selectedDays[i].getFullYear()
      )
        return this.setState(({ selectedDays }) => ({
          selectedDays: [
            ...selectedDays.slice(0, i),
            ...selectedDays.slice(i + 1),
          ],
        }));
    }
    this.setState(({ selectedDays }) => ({
      selectedDays: [...selectedDays, day],   
    }));
  };
  render() {
    return (
      <>
        <CalendarHead changeDate={this.changeDate} /> // changeDate - обработчик события, с помощью которого планируем обновление состояния
        // в CalendarHead мы нажимаем стрелочку, у нас меняется месяц, соответственно нужно планировать обновление состояния
        <CalendarBody
          date={this.state.date}
          selectDays={this.selectDays}
          selectedDays={this.state.selectedDays}
        />
      </>
    );
  }
}

class CalendarHead extends React.Component {
  constructor(props) {  // вызывает конструктор базового класса 
    super(props); // для доступа к this
    this.state = { date: new Date() }; // устанавливаем начальное состояние                         
  }
  monthNames = [  // массив строк
    "Январь",
    "Февраль",
    "Март",
    "Апрель",
    "Май",
    "Июнь",
    "Июль",
    "Август",
    "Сентябрь",
    "Октябрь",
    "Ноябрь",
    "Декабрь",
  ];

  // параметры отсюда передаются в ChangeDate
  prevMonth = () => {   // планируем обновление состояния на предыдущий месяц
    let date = new Date(        // у нас записывается всё в переменную date
      this.state.date.getFullYear(),  // год получается из стандартного метода getFullYear
      this.state.date.getMonth() - 1  // а месяц получен после -1 от месяца
    );
    this.setState({ date }, () => this.props.changeDate(this.state.date));  // в зависимости от переменной date планируем обновление состояния
  };
  nextMonth = () => {   // для следующего месяца мы получаем год и к текущему месяцу изначально прибавляем единицу
    let date = new Date(    // все записывается в переменную date
      this.state.date.getFullYear(),  // год из метода getFullYear
      this.state.date.getMonth() + 1  // месяц черед +1
    );
    this.setState({ date }, () => this.props.changeDate(this.state.date));    // планируем обновление состояния на следующий месяц
  };
// первая кнопка у нас содержит обработчик события onclick, который вызывает метод класса, а по совместительству стрелочную функцию, prevMonth, то есть при нажатии у нас месяц -1
// вторая кнопка у нас содержит обработчик события onclick, который вызывает метод класса, а по совместительству стрелочную функцию, nextMonth, то есть при нажатии у нас месяц +1
// monthManes[index]. в скобках у нас подсчитывается месяц по порядку из прошлых методов, в зависимости от индекса возвращается определенная строка
  render() {
    return (
      <>
      <div class="calendarHeader">
        {this.monthNames[this.state.date.getMonth()]} {this.state.date.getFullYear()}   
        <span class="buttonGroup">
        <button onClick={this.prevMonth}>{"<"}</button>   
        <button onClick={this.nextMonth}>{">"}</button>
        </span>
      </div>
      </>
    );
  }
}

class CalendarBody extends React.Component {
  dayNames = ["пн", "вт", "ср", "чт", "пт", "сб", "вс"];  // массив строк 
  currentDate = new Date(); // today          
  startDay(date) {
    let startDay;
    // так как 0 соответствует воскресенью, то если условие выполняется, startDay = 6, что в массиве строк выше соответствует 'вс', в противном случае от полученного значения -1
    date.getDay() === 0 ? (startDay = 6) : (startDay = date.getDay() - 1);
    return startDay;
  }
  // oneMonth потом будет использоваться в рендере при создании массива map 
  oneMonth(date) {
    let fullMonth = [], // массив, который потом заполним
      day = 1 - this.startDay(date),  // 1 - день. то есть 1 - 5 число == 27, для правильного отображения
      month = date.getMonth(),
      year = date.getFullYear();
    for (let i = 0; i < 6; i++) {     // месяц мы заполним матрицей из дней, где i - недели
      fullMonth[i] = [];
      for (let j = 0; j < 7; j++) {   // j - дни
        fullMonth[i][j] = new Date(year, month, day++);
      }
    }
    return fullMonth;
  }
  // стили для CalendarBody
  styleTd = (wdate, currentDate, date, selectedDays) => {
    if (date.getMonth() !== wdate.getMonth()) //не входит
      return { color: "#dfdfdf" };      // если дни месяца не совпадают с нями недель, то они закрашиваются серым
      
    for (let i = 0; i < selectedDays.length; i++) {
      if (
        selectedDays[i].getDate() === wdate.getDate() &&
        selectedDays[i].getMonth() === wdate.getMonth() &&
        selectedDays[i].getFullYear() === wdate.getFullYear()
      )
        return { background: "#B6CDF0" };   // если день выбран
    }
    // для текущего, если тот день, на который мы нажали равен по всем параметрам тому дню, который текущий, то перекрашиваем задний фон 
    if (
      wdate.getDate() === currentDate.getDate() &&
      wdate.getMonth() === currentDate.getMonth() &&
      wdate.getFullYear() === currentDate.getFullYear()
    )
      return { background: "#D89FEE" }; // если один из дней недели = текущему
  };
  // вызываем setState для обновления состояния выбранного дня
  selectDays = (wdate) => {
    this.setState({}, () => this.props.selectDays(wdate));
  };
  render() {
    const date = new Date(
        this.props.date.getFullYear(),
        this.props.date.getMonth(),
        1
      ), 
      selectedDays = this.props.selectedDays;
    return (
      <table class="calendarTable">
        <thead>
          <tr>
            {this.dayNames.map((name) => (  // из объекта dayNames(пн, вт...) создаем массив map и возвращаем разметку
              <td key={name}>{name}</td>
            ))}
          </tr>
        </thead>
        <tbody>
          {this.oneMonth(date).map((week, index) => (   // oneMonth для заполнения таблицы числами месяца
            <tr key={index}>
              {week.map((wdate, index) => (
                <td
                  key={index}
                  style={this.styleTd(
                    wdate,
                    this.currentDate,
                    date,
                    selectedDays
                  )}
                  onClick={() => {
                    if (date.getMonth() === wdate.getMonth())
                      this.selectDays(wdate);
                  }}
                >
                  {wdate.getDate()}   
                </td> // wdate === fullMonth[i][j]
              ))}
            </tr>
          ))}
        </tbody>
      </table>
    );
  }
}