// ДЛЯ ПАРАБОЛЫ
function firstFunction()
{
    let y = (x) => x * x;                                     // функция с параметром x
    let scale = 30;                                           // масштаб
    let canvas = document.getElementById("canvas");           // холст
    let ctx = canvas.getContext("2d");                        /* используется для получения контекста визуализации и её функции рисования.
                                                              getContext() принимает один параметр, тип контекста. Для 2D графики использовать метку "2d".*/
    // центровочка
    ctx.translate(canvas.width / 2, canvas.height / 2);        // translate ретранслирует позицию (0,0) в новое место растрового холста
    // график функции
    ctx.beginPath();                        // Метод beginPath() начинает контур или сбрасывает текущий контур
    for (var i = -2; i <= 2; i += 0.2) {
      if(i){
      ctx.lineTo(i * scale, y(i) * scale);
      }
      else 
      {
      ctx.moveTo(i * scale, y(i) * scale);
      } 
    }
    ctx.stroke();                            // рисует фигуру, контур которой был задан ранее. По умолчанию фигура будет нарисована черным цветом.
  }
  // ДЛЯ КУБИЧЕСКОЙ ПАРАБОЛЫ
  function secondFunction()
  {
    let y = (x) => x * x * x;                                
    let scale = 30;                                          
    let canvas = document.getElementById("canvas");          
    let ctx = canvas.getContext("2d");                        

    ctx.translate(canvas.width / 2, canvas.height / 2);        
    
    ctx.beginPath();
    for (var i = -2; i <= 2; i += 0.2) {
      if(i){
      ctx.lineTo(i * scale, y(i) * scale);
      }
      else 
      {
      ctx.moveTo(i * scale, y(i) * scale);
      } 
    }
    ctx.stroke();
  }
  // ДЛЯ СИНУСА
  function thirdFunction()
{
    let y = (x) => Math.sin(x);                                         
    let scale = 20;                                           
    let canvas = document.getElementById("canvas");           
    let ctx = canvas.getContext("2d");                        
    ctx.translate(canvas.width / 2, canvas.height / 2);      
  
    ctx.beginPath();
    for (var i = -1; i <= 10; i += 0.2) {
      if(i){
      ctx.lineTo(i * scale, y(i) * scale);
      }
      else 
      {
      ctx.moveTo(i * scale, y(i) * scale);
      } 
    }
    ctx.stroke();
  }

  // ДЛЯ КОСИНУСА
  function fourthFunction()
  {
    let y = (x) => Math.cos(x);                              
    let scale = 20;                                          
    let canvas = document.getElementById("canvas");          
    let ctx = canvas.getContext("2d");                       

    ctx.translate(canvas.width / 2, canvas.height / 2);  
      
    ctx.beginPath();
    for (var i = -1; i <= 10; i += 0.2) {
      if(i){
      ctx.lineTo(i * scale, y(i) * scale);
      }
      else 
      {
      ctx.moveTo(i * scale, y(i) * scale);
      } 
    }
    ctx.stroke();
  }