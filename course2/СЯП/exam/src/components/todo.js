import React, { useState } from 'react';

function TodoList() {
  const [tasks, setTasks] = useState([]);
  const [inputValue, setInputValue] = useState('');
  const [editIndex, setEditIndex] = useState(null);

  const handleInputChange = (event) => {
    setInputValue(event.target.value);
  };

  const addTask = () => {
    if (inputValue.trim() !== '') {
      if (editIndex !== null) {
        const updatedTasks = [...tasks];
        updatedTasks[editIndex].text = inputValue;
        setTasks(updatedTasks);
        setInputValue('');
        setEditIndex(null);
      } else {
        setTasks([...tasks, { text: inputValue, completed: false }]);
        setInputValue('');
      }
    }
  };

  const deleteTask = (index) => {
    const updatedTasks = [...tasks];
    updatedTasks.splice(index, 1);
    setTasks(updatedTasks);
  };

  const toggleTaskCompletion = (index) => {
    const updatedTasks = [...tasks];
    updatedTasks[index].completed = !updatedTasks[index].completed;
    setTasks(updatedTasks);
  };

  const editTask = (index) => {
    const taskToEdit = tasks[index];
    setInputValue(taskToEdit.text);
    setEditIndex(index);
  };

  return (
    <div>
      <h1>TODO List</h1>
      <input type="text" value={inputValue} onChange={handleInputChange} />
      <button onClick={addTask}>{editIndex !== null ? 'Сохранить' : 'Добавить задачу'}</button>
      <ul>
        {tasks.map((task, index) => (
          <li
            key={index}
            style={{
              textDecoration: task.completed ? 'line-through' : 'none',
              fontWeight: task.completed ? 'normal' : 'bold',
            }}
          >
            <input
              type="checkbox"
              checked={task.completed}
              onChange={() => toggleTaskCompletion(index)}
            />
            {task.text}
            <button onClick={() => editTask(index)}>Редактировать</button>
            <button onClick={() => deleteTask(index)}>Удалить</button>
          </li>
        ))}
      </ul>
    </div>
  );
}

export default TodoList;
