import React from 'react'
import { SignUpEmailInput } from './SignUpEmailInput'
import { SignUpPasswordInput } from './SignUpPasswordInput'
import { PhoneInput } from './PhoneInput.js'
import "./SignUpForm.css";

export class SignUpForm extends React.Component {
    constructor(props) {    
        super(props);
        this.state = { disableBtn: false }
      };
    disableBtn = (value) => {
        this.setState({disableBtn: value})
        return this.state.disableBtn
    }
    day() {
        let days = []
        for (let day = 1; day < 32; day++) {
            days.push(
                <option key={day}>{day}</option>
            )
        }
        return (
            <select className="select">
                {days}
            </select>
        )
    }
    month() {
        let months = [
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
        ]
        return (
            <select className = "select">
                {months.map(month => {
                    return <option key={month}>{month}</option>
                })}
            </select>
        )
    }
    year() {
        let years = []
        for (let year = 1940; year < 2024; year++) {
            years.push(
                <option key={year}>{year}</option>
            )
        }
        return (
            <select className = "select">
                {years}
            </select>
        )
    }
    render() {
        return(
            <form className='login'>
                <div className='divLog'>
                <h3>Форма регистрации</h3>
                <SignUpEmailInput 
                    disableBtn={this.disableBtn} 
                    disabledBtn={this.state.disableBtn}
                    months={this.months}
                    parentState={this.state}
                />
                <SignUpPasswordInput disableBtn={this.disableBtn} />
                <input id='inp' type="text" placeholder="Фамилия" />
                <input id='inp' type="text" placeholder="Имя" />
                <input id='inp' type="text" placeholder="Отчество" />
                <div className='divRad'>
                <label class="rad-label">
                    <input type="radio" class="rad-input" name="gender"/>
                            <div class="rad-design"></div>
                        <div class="rad-text">Муж</div>
                 </label>
                 <label class="rad-label">
                    <input type="radio" class="rad-input" name="gender"/>
                        <div class="rad-design"></div>
                        <div class="rad-text">Жен</div>
                </label>
                </div>
                <div className="date">
                <div>{this.day()}</div>
                <div>{this.month()}</div>
                <div>{this.year()}</div>
                </div>
                <br />
                <PhoneInput />
                <button className = "send" disabled={this.state.disableBtn} onClick={this.handleBtnClick}>Отправить</button>
                </div>
            </form>
            
        )
    }
}
