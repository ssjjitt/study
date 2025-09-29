let massiv = new Array();           
massiv[0] = 6 - Math.PI * Math.PI + 3 * Math.exp(8);        
massiv[1] = 2 * Math.cos(4) + Math.cos(12) + 8 - Math.exp(3);
massiv[2] = 3 * Math.sin(9) + Math.log(5);
massiv[3] = 2 * Math.tan(5) + 6;
document.write("<p>исходный массив: " +massiv+ "</p>");

delete massiv[2];                                                   // с помощью оператора delete удаляем 3-й элемент массива, с помощью него можно удалять и свойства объектов 
document.write("<p>полученный массив: " +massiv+ "</p><br>");       // удаляется и индекс элемента массива, но все остальные элементы сохраняют свои прежние индексы, длина массива не меняется

document.write("<p>есть ли второй элемент в массиве? "+(1 in massiv)+ "</p>"); // с помощью оператора in проверяем есть ли 2-й элемент в массиве, можно проверить наличие свойств и методов

let stroka = new String("белеет парус одинокий");

document.write("<p>принадлежит ли massiv объектной модели Array: " +(massiv instanceof Array)+ "</p>");   // instanceof - можем определить принадлежит ли объект к указанной объектной модели 
document.write("<p>принадлежит ли stroka объектной модели String: " +(stroka instanceof String)+ "</p>");
document.write("<p>принадлежит ли stroka объектной модели Array: " +(stroka instanceof Array)+ "</p>");
document.write("<p>принадлежит ли massiv объектной модели Object: " +(massiv instanceof Object)+ "</p>");

function zadanie3()
{
    return 5;
}

document.write("<p>typeof zadanie3: " +(typeof zadanie3())+ "</p>");    // typeof - позволяет определить к какому типу относится значение 
document.write("<p>typeof stroka: " +(typeof stroka)+ "</p>");
document.write("<p>typeof massiv: " +(typeof massiv)+ "</p>")