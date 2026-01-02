export class SignUpForm extends React.Component {
  constructor(props) {
    // вызываем базовый конструктор
    super(props); // для доступа к this
    this.state = { disableBtn: false }; // устанавливаем начальное состояние
  }
  disableBtn = (value) => {
    // этот метод будет использоваться для видимости кнопки
    this.setState({ disableBtn: value }); // он обновляет состояние на значение true/false
    return this.state.disableBtn; // и возващает его значение
  };
  day() {
    // метод чтобы вставить дни в select
    let days = []; // массив для дней
    for (let day = 1; day < 32; day++) {
      // через цикл for будем заполнять массив
      days.push(
        // в конец массива закидываем тег option
        <option key={day}>{day}</option>
      );
    }
    return (
      // и возвращаем разметку
      <select className="select">{days}</select>
    );
  }
  month() {
    let months = [
      // массив строк
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
    return (
      // возвращаем разметку, прогоняя каждый элемент через map
      <select className="select">
        {months.map((month) => {
          return <option key={month}>{month}</option>;
        })}
      </select>
    );
  }
  year() {
    let years = [];
    for (let year = 1940; year < 2024; year++) {
      years.push(<option key={year}>{year}</option>);
    }
    return <select className="select">{years}</select>;
  }
  str = Number(123);
  num = "123";
  sym = Symbol("111");
  render() {
    return (
      <form className="login">
        <div className="divLog">
          <h3>Форма регистрации</h3>
          <SignUpEmailInput
            disableBtn={this.disableBtn}
            disabledBtn={this.state.disableBtn}
            months={this.months}
            parentState={this.state}
            str={this.str}
            num={this.num}
            sym={this.sym}
          />
          <SignUpPasswordInput disableBtn={this.disableBtn} />
          <input id="inp" type="text" placeholder="Фамилия" />
          <input id="inp" type="text" placeholder="Имя" />
          <input id="inp" type="text" placeholder="Отчество" />
          <div className="divRad">
            <label class="rad-label">
              <input type="radio" class="rad-input" name="gender" />
              <div class="rad-design"></div>
              <div class="rad-text">Муж</div>
            </label>
            <label class="rad-label">
              <input type="radio" class="rad-input" name="gender" />
              <div class="rad-design"></div>
              <div class="rad-text">Жен</div>
            </label>
          </div>
          <div className="date">
            {this.day()}
            {this.month()}
            {this.year()}
          </div>
          <br />
          <PhoneInput />
          <button
            className="send"
            disabled={this.state.disableBtn}
            onClick={this.handleBtnClick}
          >
            Отправить
          </button>
        </div>
      </form>
    );
  }
}

export class SignUpEmailInput extends React.Component {
  constructor(props) {
    super(props);
    this.state = { email: "" };
  }
  inputHandler = (e) => {
    this.setState({ email: e.target.value });
    let check = /\S+@\S+\.\S+/, 
    // + Соответствует предыдущему символу повторенному 1 или более раз
    // \S Соответствует одиночному символу непустого пространства.
      checked = check.test(e.target.value); // возвращаем true/false при совпадении/несовпадении с регулярным выражением 
    this.props.disableBtn(!checked);    
  };
  render() {
    return (
      <input
        id="inp"
        type="email"
        name="email"
        placeholder="email@smth.smth"
        value={this.state.email}
        onChange={this.inputHandler}
      />
    );
  }
}

export class SignUpPasswordInput extends React.Component {
  constructor(props) {
    super(props);
    this.state = { password: "", background: "", disableBtn: true };
  }
  handlePassword = (e) => {
    this.setState({ password: e.target.value });
  };

  handleRepeat = (e) => {   // функция для проверки пароля
    if (this.state.password === e.target.value) {
      this.setState({ disableBtn: false }, () =>
        this.props.disableBtn(this.state.disableBtn)
      );
    } else {
      this.setState({ disableBtn: true }, () =>
        this.props.disableBtn(this.state.disableBtn)
      );
    }
  };

  checkIfRepeat() {     // еще одна функция для проверки паролей, но уже со всплывабщим блоком
    let password = this.state.password;
    let display = "none";
    if (!password.length) {
      display = "none";
      return <div style={{ display: display }}>Пароли не совпадают</div>;
    }
    if (this.state.disableBtn) {
      display = "block";
      return <div style={{ display: display }}>Пароли не совпадают</div>;
    }
  }

  checkPassword() {
    let password = this.state.password,
      check = 0,
      width = "",
      transition = "0.3s",
      background = "";
    if (password.match(/\d/g)) check++; // Соответствует цифровому символу.
    if (password.match(/[a-z]/g)) check++;
    if (password.match(/[A-Z]/g)) check++;
    if (password.match(/\W/g)) check++; // Соответствует любому не цифробуквенному символу. 

    if (!password.length) width = "0%";
    else if (password.length < 6 && check < 3) {
      width = "25%";
      background = "red";
    } else if (password.length < 6 && check >= 3) {
      width = "30%";
      background = "red";
    } else if (password.length >= 6 && check < 3) {
      width = "35%";
      background = "orange";
    } else if (password.length >= 6 && check > 1 && check < 4) {
      width = "65%";
      background = "green";
    } else if (password.length >= 8 && check >= 3) {
      width = "100%";
      background = "green";
    } else if (password.length >= 6 && check === 4) {
      width = "100%";
      background = "green";
    }
    return (
      <div className="progress_bar_bg">
        <div
          className="progress_bar"
          style={{
            width: width,
            background: background,
            transition: transition,
          }}
        />
      </div>
    );
  }
  render() {
    return (
      <>
        <input
          id="inp"
          type="password"
          placeholder="Введите ваш пароль"
          onChange={this.handlePassword}
        />
        <input
          id="inp"
          type="password"
          placeholder="Повторите пароль"
          onChange={this.handleRepeat}
        />
        {this.checkIfRepeat()}
        {this.checkPassword()}
      </>
    );
  }
}
