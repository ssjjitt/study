data = new Date(); //Объект Date позволяет производить различные операции с датой и временем
document.write(data)
document.write("<table border = 1 style = 'border-collapse: collapse; color: blue; font-size: 25px'>");
document.write("<tr>"); //далее методы объекта Date
document.write("<td>год</td><td>" +data.getFullYear()+ "</td></tr>");
document.write("<tr>")
document.write("<td>месяц</td><td>" +data.getMonth()+  "</td></tr>");
document.write("<tr>")
document.write("<td>день</td><td>" +data.getDay()+  "</td></tr>");
document.write("<tr>");
document.write("<td>час</td><td>" +data.getHours()+  "</td></tr>");
document.write("<tr>")
document.write("<td>минуты</td><td>" +data.getMinutes()+  "</td></tr>");
document.write("<tr>")
document.write("<td>секунды</td><td>" +data.getSeconds()+  "</td></tr>");
document.write("<tr>")