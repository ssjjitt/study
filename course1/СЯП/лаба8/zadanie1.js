/*
события – это функции, которые могут быть привязаны к элементам HTML страниц.
событие - сигнал, пуступающий от браузера о том, что произошло какое-то действие на странице
отлавливать эти события с помощью обработчиков.

Событию можно назначить обработчик, то есть функцию, которая сработает, как только событие произошло. Именно благодаря обработчикам JavaScript-код может реагировать 
на действия пользователя.

Все инициированные события заносятся операционной системой в буфер и выполняются последовательно в том порядке, в каком они туда попали.

Дополнительную информацию о событиях, которые произошли, содержит объект события events, то есть в объекте events хранятся атрибуты событий

1) Обработчик может быть назначен прямо в разметке, в атрибуте, который называется on<событие>.
2) Можно назначать обработчик, используя свойство DOM-элемента on<событие>.

Обработчик всегда хранится в свойстве DOM-объекта, а атрибут – лишь один из способов его инициализации.

Так как у элемента DOM может быть только одно свойство с именем onclick, то назначить более одного обработчика так нельзя.

Убрать обработчик можно назначением elem.onclick = null.

Когда происходит событие, браузер создаёт объект события, записывает в него детали и передаёт его в качестве аргумента функции-обработчику.
*/
// задание 1
function ForColorBlue(){
    abzac.style.color = "blue"
}
                                                    
function ForColorBlack(){
    abzac.style.color = "black"
}

//задание 2
function ForFont(){
    abzac.style.fontSize = "20px"
}

//задание 3
function ForImage(){
    document.getElementById("image").src = "kot12.jpg";
}

//задание 4
function ForZamena(){
    document.getElementById("zamena").innerHTML = "<img src = 'kot10.jpg'>"
}

//задание 5
function ForSizePlus(){
    document.getElementById("sizeimg").style.width = "300px"
    document.getElementById("sizeimg").style.height = "300px"
}
function ForSizeMinus(){
    document.getElementById("sizeimg").style.width = "200px"
    document.getElementById("sizeimg").style.height = "200px"
}

//задание 6
function ForBorder() {
    document.getElementById("border").style.border = "2px dashed blue";
}

