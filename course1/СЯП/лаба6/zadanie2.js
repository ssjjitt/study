document.write("<table border = 1px style = 'border-collapse: collapse'><tr><td>свойство/метод</td><td>значение</td></tr>")

document.write("<tr><td>userAgent</td>")                                        // navigator - лбъект, который позволяет определить какой браузер используется
document.write("<td>" +navigator.userAgent+ "</td></tr>")                       // информация о браузере пользователя

document.write("<tr><td>appVersion</td>")
document.write("<td>" +navigator.appVersion+ "</td></tr>")                      // версия браузера

document.write("<tr><td>appName</td>")
document.write("<td>" +navigator.appName+ "</td></tr>")                         // имя браузера

document.write("<tr><td>appCodeName</td>")
document.write("<td>" +navigator.appCodeName+ "</td></tr>")                     // кодовое имя

document.write("<tr><td>platform</td>")                             
document.write("<td>" +navigator.platform + "</td></tr>")                       // ОС

document.write("<tr><td>javaEnabled()</td>")
document.write("<td>" +navigator.javaEnabled()+ "</td></tr>")                   // поддержка js браузером

document.write("<tr><td>width x height</td>")
document.write("<td>" +screen.width+ " x " +screen.height+  "</td></tr>")       // ширина и высота экрана

document.write("<tr><td>colorDepth</td>")
document.write("<td>" +screen.colorDepth+ "</td></tr>")                         // глубина цвета

document.write("<tr><td>lenght</td>")
document.write("<td>" +history.length+ "</td></tr>")                            // количество посещенных url

document.write("<tr><td>href</td>")
document.write("<td>" +location.href+ "</td></tr>")                             // url текущего документа

document.write("<tr><td>pathname</td>")
document.write("<td>" +location.pathname+ "</td></tr>")                          // путь к текущему  

document.write("<tr><td>host</td>")
document.write("<td>" +location.hostname+ "</td></tr>")                              //

let index=() =>
{
    location.assign("file:///E:/%D1%83%D0%BD%D0%B8%D0%BA/%D0%BB%D0%B0%D0%B1%D1%8B/%D0%9F%D1%80%D0%B0%D0%BA%D1%82%D0%B8%D0%BA%D1%83%D0%BC_%D0%A1%D0%AF%D0%9F_2022/index.html#")
}

