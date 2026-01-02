import React from 'react'
import { SignUpEmailInput } from './SignUpEmailInput'
import { SignUpPasswordInput } from './SignUpPasswordInput'
import { PhoneInput } from './PhoneInput.js'
import "./SignUpForm.css";

export class SignUpForm extends React.Component {
    state = {
        disableBtn: false,
    }
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
        for (let year = 1960; year < 2024; year++) {
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
    
    
    // ПРИМЕР ПРОПТАЙПСОВ
    num = 123;
    str = "qeqwe";

    
    render() {
        return(
            <form className='login'>
                <div className='divLog'>
                    <h2>Форма регистрации</h2>
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
                <input id='inp' type="text" placeholder="Фамилия" />
                <input id='inp2' type="text" placeholder="Имя" />
                <input id='inp3' type="text" placeholder="Отчество" />
                <div className='divRad'>
                <label className="rad-label">
                    <input type="radio" className="rad-input" name="gender"/>
                            <div className="rad-design"></div>
                        <div className="rad-text">Муж</div>
                 </label>
                 <label className="rad-label">
                    <input type="radio" className="rad-input" name="gender"/>
                        <div className="rad-design"></div>
                        <div className="rad-text">Жен</div>
                </label>
                </div>
                <div className="date">
                {this.day()}
                {this.month()}
                {this.year()}
                </div>
                <br />
                <PhoneInput />
                <br />
                <button className = "send" disabled={this.state.disableBtn} onClick={this.handleBtnClick}>Отправить</button>
                </div>
            </form>
        )
    }
}



