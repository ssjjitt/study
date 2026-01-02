// setInterval - метод объекта window
// setInterval позволяет вызывать функцию регулярно, повторяя вызов через определённый интервал времени

setInterval(move, 20);
let left = 10;
function move() {
  document.getElementById("image").style.left = left + "px";
  left++;
}