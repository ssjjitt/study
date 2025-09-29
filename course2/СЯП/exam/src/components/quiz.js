import React, { useState } from 'react';

function Quiz() {
  const questions = [
    {
      question: 'Сколько будет 2 + 2?',
      answer: '4',
    },
    {
      question: '5 + 3?',
      answer: '8',
    },
    {
      question: '5 + 7 - одиннадцать или адиннадцать?',
      answer: '12',
    },
  ];

  const [currentQuestion, setCurrentQuestion] = useState(0);
  const [userAnswer, setUserAnswer] = useState('');
  const [isCorrect, setIsCorrect] = useState(null);

  const checkAnswer = () => {
    const correctAnswer = questions[currentQuestion].answer;
    setIsCorrect(userAnswer === correctAnswer);
  };

  const handleNextQuestion = () => {
    setCurrentQuestion((prevQuestion) => prevQuestion + 1);
    setUserAnswer('');
    setIsCorrect(null);
  };

  return (
    <div>
        <h1>Quiz</h1>
      {currentQuestion < questions.length ? (
        <div>
          <p>{questions[currentQuestion].question}</p>
          <input type="text" value={userAnswer} onChange={(e) => setUserAnswer(e.target.value)} />
          <button onClick={checkAnswer}>Проверить</button>
          {isCorrect !== null && (
            <p style={{ color: isCorrect ? 'green' : 'red' }}>
              {isCorrect ? 'Верно!' : 'Неверно!'}
            </p>
          )}
          <button onClick={handleNextQuestion}>Следующий вопрос</button>
        </div>
      ) : (
        <p>Вы ответили на все вопросы!</p>
      )}
    </div>
  );
}

export default Quiz;
