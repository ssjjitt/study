import logo from './logo.svg';
import './App.css';
import "./components/employees"
import NumberArray from "./components/numbers"
import EmployeeTable from './components/employees';
import Quiz from './components/quiz';
import TodoList from './components/todo';
import UserList from './components/user';
import Apps from "./components/text"
import Notes from "./components/calendar"

function App() {
  return (
    <div>
    <EmployeeTable/>
    <hr></hr>
    <NumberArray/>
    <hr></hr>
    <Quiz/>
    <hr></hr>
    <TodoList/>
    <hr></hr>
    <UserList/>
    <hr></hr>
    <Apps/>
    <hr></hr>
    <Notes/>
    </div>
  );
}

export default App;
