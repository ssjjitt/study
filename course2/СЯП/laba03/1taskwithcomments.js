import React, { useEffect, useState } from "react";   // импортируем хуки из библиотеки реакт, для их непосредственного использования в коде
import bel from "./images/bel.png";
import rus from "./images/rus.png";
import ucr from "./images/uk.png";
import lt from "./images/lithuania.png";
import lv from "./images/latvia.png";
import pl from "./images/poland.png";
import "./PhoneInput.css";

let NumberFormats = [       // ассоциативный массив
  {
    id: 1,                  
    name: "Беларусь",
    code: "+375",
    mask: "XXXX (XX) XXX-XX-XX",
    operators: ["МТС", "А1", "life:)"],
    count: 13,
  },
  {
    id: 2,
    name: "Россия",
    code: "+7",
    mask: "XX (XXX) XXX-XX-XX",
    operators: ["МТС", "Билайн", "Мегафон", "Tele2"],
    count: 12,
  },
  {
    id: 3,
    name: "Украина",
    code: "+380",
    mask: "XXXX (XX) XXX-XX-XX",
    operators: ["Lifecell", "Vodafone", "Київстар"],
    count: 13,
  },
  {
    id: 4,
    name: "Польша",
    code: "+48",
    mask: "XXX XXX-XXX-XXX",
    operators: ["Orange", "Play", "Plus", "T-mobile"],
    count: 12,
  },
  {
    id: 5,
    name: "Литва",
    code: "+370",
    mask: "XXXX (XX) XXX-XX-XX",
    operators: ["Telia", "Bite", "Tele2"],
    count: 13,
  },
  {
    id: 6,
    name: "Латвия",
    code: "+371",
    mask: "XXXX XXXX-XXXX",
    operators: ["LMT", "Tele2", "Bite"],
    count: 12,
  },
];

// функция для установки картинки
let SwitchFlag = ({ id }) => {  // объявили стрелочную функцию
// ДЕСТРУКТУРИЗАЦИЯ МАССИВОВ!!!!
const [img, setImg] = useState(bel);    // объявили новую переменнуб состояния img
// useState - хук состояния, вызывается, чтобы наделить функциональный компонент внутренним состоянием, это состояние react будет хранить между рендерами
// возвращает массив из двух элементов: 1 - текущее состояние, 2 - функция для обновления, она схожа с this.setState, но старое и новое состояние не сливает
// аргумент bel - начальное состояние, используется только при первом рендере
useEffect(() => {   // хук эффекта, по принципу componentDidMount() и componentDidUpdate()
// используя API обновляем картинку   
  switch (id) {
      case 1:
        setImg(bel);      // вызов функции для обновления состояния
        break;
      case 2:
        setImg(rus);
        break;
      case 3:
        setImg(ucr);
        break;
      case 4:
        setImg(pl);
        break;
      case 5:
        setImg(lt);
        break;
      case 6:
        setImg(lv);
        break;
      default:
        break;
    }
  }, [id]); // второй аргумент для пропуска эффекта. если из пред и след рендеров элементы равны, то пропускается

  return <img src={img} alt={"err"} />;
};

// функция для вывода операторов
const OperatorsButtonList = ({ numberFormats, id }) => {  // вновь объявили стрелочную функцию, вновь деструктуризация массивов
  const [currentFormat, setCurrentFormat] = useState(numberFormats[0]);

  useEffect(() => {
    switch (id) {   // switch case на id выбранного
      case 1:
        setCurrentFormat(numberFormats[0]);
        break;
      case 2:
        setCurrentFormat(numberFormats[1]);
        break;
      case 3:
        setCurrentFormat(numberFormats[2]);
        break;
      case 4:
        setCurrentFormat(numberFormats[3]);
        break;
      case 5:
        setCurrentFormat(numberFormats[4]);
        break;
      case 6:
        setCurrentFormat(numberFormats[5]);
        break;
      default:
        break;
    }
  }, [id, numberFormats]); // второй аргумент для пропуска эффекта. если из пред и след рендеров элементы равны, то пропускается
  // после выбора какого-то формата, используем хук эффекта и получаем список операторов снизу в соответствии с выбранным
  return (
    <>
      {currentFormat.operators.map((operator) => (    // применяем метод мап для операторов
        <div>
          <input type={"radio"} value={operator} name={"op"} />
          <label>{operator}</label>
        </div>
      ))}
    </>
  );
};

// функциональный компонент с тремя параметрами
const InputNumber = ({ numbers, id, setId }) => {
  // деструктуризация массивов
  const [number, setNumber] = useState(numbers[0]); // по умолчанию number[0]
  const [value, setValue] = useState(""); // по умолчанию пустая строка

  useEffect(() => { // вызываем хук эффекта
    setNumber(numbers[id - 1]);   
  }, [id, numbers]);

  const inputNumber = (e) => {
    // forEach - перебирает все наши numbers и применяет для каждого из них стрелочную функцию в скобках
    numbers.forEach((el) => {
      // el.code - длина строки из цифр которые после плюсика
      // value.length - длина введенной строки
      // el.count - длина строки номера в целом
      // то есть если длина введенной строки больше кода, но меньше указанной длины номера, выполняется условие
      if (el.code.length <= value.length && el.count >= value.length)
// slice - метод который возвращает новый массив состоящий из копии исходного массива начиная с начальной позиции(0) и заканчивая конечной позицией не включая(el.code.length - 1)
// то есть если копия кусочка ВВЕДЕННОГО кода с плюсом (+375) совпадает с одним из кодов в массиве, то   
if (value.slice(0, el.code.length) === el.code) {
          setNumber(el);      // вызываем функцию setNumber для обновления состояния
          setId(el.id);       // и setId также для обновления состояния
        }
    });
    // split - делит строку на подстроки указанной подстрокой
    //       /[ \-()]/ регулярное выражение по подгруппам
    //       \- символ не должен интерпретироваться буквально
    //       [kkodakopakda] - для набора символов 
    // join - объединяет элементы массива в строку, то есть вставляет пробел между циферками
    setValue(e.target.value.split(/[ \-()]/).join(""));   // по сути это для того, чтобы в строке адекватно убирались символы - ( и ), а остались только цифры

    if (value.length === number.count) {    // если длина введенной строки равна значению в массиве сверху
      let inputStr = value.split("");         // массив символов состоящий из наших цифр   
      let maskArr = number.mask.split("");      // массив из X 
      for (let i = 0, j = 0; i < maskArr.length; i++)   // перебираем маску
        if (maskArr[i] === "X") {   // если X, то присваиваем 
          maskArr[i] = inputStr[j];   // каждому X какую-то цифру
          j++;          // увеличиваем счетчик
        }
      let num = maskArr.join("");   // соединяет массив из символов в строку
      setValue(num);    // вызывает функцию и передает num
    }
  };

  return (
    <div className="inputWrapper">
      <input
        className="input"
        type="tel"
        id="phone"
        name="phone"
        placeholder={number.code + number.mask.slice(4)}
        required
        onInput={inputNumber}   // обработчик событий, когда происходит ввод
        maxLength={number.count + 3}
        value={value}
      />
    </div>
  );
};

// просто экспорт нашей разметки
export const PhoneInput = () => {
  const [id, setId] = useState(1);

  return (
    <div className="container">
      <div className="phoneInput">
        <div className="content">
          <InputNumber numbers={NumberFormats} id={id} setId={setId} />
          <SwitchFlag id={id} />
        </div>
      </div>

      <div className="countrySelect">
        <label>Select country</label>
        <select
          id="select"
          onChange={(e) => setId(+e.target.value)}
          style={{ borderRadius: "5px" }}
        >
          {NumberFormats.map((item) => (
            <option key={item.id} value={item.id} selected={id === item.id}>
              {item.name}
            </option>
          ))}
        </select>
      </div>

      <OperatorsButtonList numberFormats={NumberFormats} id={id} />
    </div>
  );
};


