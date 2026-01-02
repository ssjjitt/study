// draggable - атрибут, который указывает, можно ли перетаскивать элемент.
// dragstart - срабатывает, как только пользователь начинает перетаскивать элемент

document.getElementById("textarea").ondragstart = dragStart;

document.getElementById("image").ondragstart = dragStart;

function dragStart() {
  console.log("элемент двигается");
}