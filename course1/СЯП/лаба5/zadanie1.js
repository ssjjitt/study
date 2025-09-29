
document.write("<p>задание 1</p>")

for(var i = 0; i < document.all.length; i++) 
{//инициализация        проверка          инкремент     
    document.write(" | ")
    document.write(document.all[i].tagName, "-")        // имя тега
    document.write(document.all[i].nodeType, " ")       // тип элементов
}
document.write("<p>значение у document:  " +document.nodeType+ "</p>")         //нашла в помойке. у объектов значение = 9 :)

document.write("<p>задание 2</p>")

for(var i = 0; i < document.body.childNodes.length; i++)        
{
    document.write(" | ")
    document.write(document.body.childNodes[i].tagName)                        // если выводит undefined - не элемент
}

//задание 3
alert(document.all(9).innerHTML)            // содержит код внутри
alert(document.getElementById("spanid").innerHTML)



//задание 4
let ball = (5+7+6)/3
document.all(58).innerHTML = "<tr><td>баллы:</td> <td>5</td> <td>7</td> <td>6</td> </tr>"
document.all(12).innerHTML = "<span> участь  с самого детства. " +ball+ "</span>"




// DOM - представление документа в виде дерева тегов. У разных DOM-узлов могут быть разные свойства
// html - корневой элемент, все остальные - потомки
// all - коллекция, которая представляет все элементы страницы без исключений, в том числе и изображения
// коллекция - своего рода массив, проиндексированный не только по числовым номерам элементов, но и по их именам, и имеющий свойства и методы.
// nodeType - атрибут, в котором хранится тип элементов, у текстовых = 3, у тегов = 1, у объектов = 9. позволяет узнать тип DOM-узла
// tagName - узнать имя тега с помощью свойства
// childNodes - массив с дочерними элементами
// innerHTLM - свойство, которое содержит HTML-еод внутри узла, можно менять, для динамического изменения содержимого страницы
// у разных DOM-узлов могут быть разные свойства