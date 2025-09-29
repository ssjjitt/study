import React, { useEffect, useState } from "react";
import bel from "./images/bel.png";
import rus from "./images/rus.png";
import ucr from "./images/uk.png";
import lt from "./images/lithuania.png";
import lv from "./images/latvia.png";
import pl from "./images/poland.png";
import "./SignUpForm.css"

let NumberFormats = [
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

const SwitchFlag = ({ id }) => {
  const [img, setImg] = useState(bel);

  useEffect(() => {
    switch (id) {
      case 1:
        setImg(bel);
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
        setImg(bel);
        break;
    }
  }, [id]);
  return <img src={img} alt={"err"} />;
};

const OperatorsButtonList = ({ numberFormats, id }) => {
  const [currentFormat, setCurrentFormat] = useState(numberFormats[0]);

  useEffect(() => {
    switch (id) {
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
  }, [id, numberFormats]);

  return (
    <>
      {currentFormat.operators.map((operator, index) => (
        <div key={index}>
          <label className="rad-label">
            <input
              className="rad-input"
              type={"radio"}
              value={operator}
              name={"op"}
            />
            <div className="rad-design"></div>
            {operator}
          </label>
        </div>
      ))}
    </>
  );
};

const InputNumber = ({ numbers, id, setId }) => {
  const [number, setNumber] = useState(numbers[0]);
  const [value, setValue] = useState("");

  useEffect(() => {
    setNumber(numbers[id - 1]);
  }, [id, numbers]);

  const inputNumber = (e) => {
    numbers.forEach((el) => {
      if (el.code.length <= value.length && el.count >= value.length)
        if (value.slice(0, el.code.length) === el.code) {
          setNumber(el);
          setId(el.id);
        }
    });
    setValue(e.target.value.split(/[ \-()]/).join(""));

    if (value.length === number.count) {
      let inputStr = value.split("");
      let maskArr = number.mask.split("");
      for (let i = 0, j = 0; i < maskArr.length; i++)
        if (maskArr[i] === "X") {
          maskArr[i] = inputStr[j];
          j++;
        }
      let num = maskArr.join("");
      setValue(num);
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
        onInput={inputNumber}
        maxLength={number.count + 3}
        value={value}
      />
    </div>
  );
};

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

      <div className="countrySelect divRad">
        <label className="rad-label">Страна: </label>
        <select
          className = "select"
          id="select"
          onChange={(e) => setId(+e.target.value)}
          style={{ borderRadius: "5px" }}
          value={id}
        >
          {NumberFormats.map((item) => (
            <option key={item.id} value={item.id}>
              {item.name}
            </option>
          ))}
        </select>
      </div>

      <OperatorsButtonList  numberFormats={NumberFormats} id={id} />
    </div>
  );
};
