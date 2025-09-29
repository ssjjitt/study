//ДЛЯ ЦВЕТА ГРАФИКА
function forBlack(){
    let ctx = canvas.getContext("2d");
    ctx.strokeStyle = "black";
}
function forBlue(){
    let ctx = canvas.getContext("2d");
    ctx.strokeStyle = "blue";
}
function forRed(){
    let ctx = canvas.getContext("2d");
    ctx.strokeStyle = "red";
}
function forGreen(){
    let ctx = canvas.getContext("2d");
    ctx.strokeStyle = "green";
}


// ДЛЯ ПАРАБОЛЫ
function firstFunction()
{
  let y = (x) => x * x;                             // функция с параметром x              
  let scale = 30;                                           // масштаб 
  let canvas = document.getElementById("canvas");           // холст 
  let ctx = canvas.getContext("2d");       /* используется для получения контекста визуализации и её функции рисования.
  getContext() принимает один параметр, тип контекста. Для 2D графики использовать метку "2d".*/

  // центровочка
  ctx.translate(canvas.width / 2, canvas.height / 2);        

  ctx.beginPath();                            // Метод beginPath() начинает контур или сбрасывает текущий контур
  for (var i = -2; i <= 2; i += 0.2) {
    if(i){
    ctx.lineTo(i * scale, y(i) * scale);      // Метод lineTo() добавляет новую точку и создает линию ДО этой точки ОТ последней указанной точки на холсте (этот метод не рисует линию)
    }
    else 
    {
    ctx.moveTo(i * scale, y(i) * scale);     // Метод moveTo() передвигает точку контура в заданные координаты не рисуя линию.
    } 
  }
  ctx.stroke();                          // рисует фигуру, контур которой был задан ранее. По умолчанию фигура будет нарисована черным цветом.         
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