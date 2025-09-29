stroka = "Глухова Дарья Витальевна";
stroka1 = stroka.toUpperCase(); //перевод строки в верхний регистр
stroka2 = stroka.toLowerCase(); //перевод в нижний
document.write("<p>исходная сторока: " +stroka+  "</p>")
document.write("<p>длина исходной строки: " +stroka.length+ "</p>");
document.write("<p>строка в верхнем регистре: " +stroka1+ "</p>");
document.write("<p>строка в нижнем регистре: " +stroka2+ "</p>");
document.write("<p>соединенные строки: " +stroka1.concat(stroka2)+ "</p>");
document.write("<p>ФИО: " +stroka.replace("Дарья Витальевна", "Д. В.")+ "</p>"); //Дарья Витальевна замезается на Д.В.