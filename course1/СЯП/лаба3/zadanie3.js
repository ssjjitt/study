var massiv = ["pow", "pop", "push", "shift", "round", "floor", "slice", "sort"]; 
var partMassiva1 = massiv.slice(1, 4); //создает массив из элементов с указанного диапазона
var partMassiva2 = massiv.slice(6);                                                   
var partMath2 = massiv.slice(4, 6);
var partMath1 = massiv.slice(0, 1);
var array = ["concat", ...partMassiva1, ...partMassiva2];           //spread - оператор ... который клонирует массив, копирует его свойства, но не ссылки
var math = [...partMath1, ...partMath2, "max"];                     // rest -  для соединения отдельных значений в массив
document.write("<p>исходный массив: " +massiv+ "</p><p>длина исходного массива: " +massiv.length+ "</p>");
document.write("<p>массив math: " +math+ "</p><p>длина массива math: " +math.length+ "</p>");
document.write("<p>массив array: " +array+ "</p><p>длина массива array: " +array.length+ "</p>");
//Оператор spread возвращает набор значений итерируемого объекта. 
//Применяется при вызовах функций и в «литералах массивов». 
//Возможно использование при деструктурирующем присваивании

// итерируемый объект → набор значений
// набор значений → массив (в левой части присваивания)


// rest - выглядит как оператор расширения, но «собирает» отдельные аргументы в массив.
