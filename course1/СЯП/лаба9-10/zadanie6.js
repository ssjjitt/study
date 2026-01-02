/*
    для event.target
    ДЕЛЕГИРОВАНИЕ
  если есть много элементов, которые нужно обрабатывать похожим образом, то можно поставить один обработчик на общего предка, а не назначать для каждого.
  из обработчика можно получить event.target - целевой элемент. 
  по этому элементу можно понять, на каком именно потомке произошло событие 
*/


document.getElementById("nav").onmouseover = function (event) {               // событие. отслеживает, наведена ли мышь на нашу навигацию или нет
    let target = event.target;                                                // переменная таргет содержит информацию о том, на какой элемент мы невели мышь
    if (target.className == "menu-item") {                                    // если мы навели на элемент с классом menu-item, то выполняется следующее:                 
      let s = target.getElementsByClassName("submenu");                       // формируется массив с подменю, на которое наведена мышь
      closeMenu(); 
      s[0].style.display = "block";                                           //массив, содержащий ложное меню          
    }
  };
  document.onmouseover = function (event) {                                   // если мы наводим в любое место страницы, но не на элементы меню, то меню закрывается
    let target = event.target;
    console.log(event.target);
    if (target.className != "menu-item" && target.className != "submenu") {
      closeMenu();
    }
  };
  function closeMenu() {
    //получение всех элементов подменю в блоке nav, присваивание
    let menu = document.getElementById("nav");
    let subm = document.getElementsByClassName("submenu");
    for (let i = 0; i < subm.length; i++) {
      subm[i].style.display = "none";
    }
  }