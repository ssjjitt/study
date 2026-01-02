import React, { useState } from 'react';

function NumberArray() {
  const [numbers, setNumbers] = useState([1, 2, 3, 4, 5]);
  const [inputValue, setInputValue] = useState('');

  const handleInputChange = (event) => {
    setInputValue(event.target.value);
  };

  const handleDelete = () => {
    const updatedNumbers = numbers.filter((number) => number !== parseInt(inputValue));
    setNumbers(updatedNumbers);
    setInputValue('');
  };

  return (
    <div>
        <h1>Array</h1>
      <ul>
        {numbers.map((number) => (
          <li key={number}>{number}</li>
        ))}
      </ul>
      <input type="text" value={inputValue} onChange={handleInputChange} />
      <button onClick={handleDelete}>Удалить</button>
    </div>
  );
}

export default NumberArray;
