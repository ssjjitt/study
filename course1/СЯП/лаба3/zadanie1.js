var massiv = new Array();           //массив - упорядоченный набор данных
massiv[0] = 6 - Math.PI * Math.PI + 3 * Math.exp(8);        //присваиваем элементам массива значения выражений
massiv[1] = 2 * Math.cos(4) + Math.cos(12) + 8 - Math.exp(3);
massiv[2] = 3 * Math.sin(9) + Math.log(5);
massiv[3] = 2 * Math.tan(5) + 6;
document.write("<p>0 элемент массива: " +massiv[0]+ "</p>");
document.write("<p>1 элемент массива: " +massiv[1]+ "</p>");
document.write("<p>2 элемент массива: " +massiv[2]+ "</p>");
document.write("<p>3 элемент массива: " +massiv[3]+ "</p>");
document.write("<p>Минимальный элемент массива: " +Math.min(massiv[0], massiv[1], massiv[2], massiv[3])+ "</p>");
document.write("<p>Максимальный элемент массива: " +Math.max(massiv[0], massiv[1], massiv[2], massiv[3])+  "</p>");
