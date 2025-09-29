k = +prompt("сколько студентов исключить")

h = +prompt("сколько студентов добавить")

function Gruppa(facultet, speciality, students){              // создаем функцию-конструктор          
    this.facultet = facultet                                  // функция-конструктор - функция, которая представляет собой "шаблон" для создания любого нового экземпляра этой функции
    this.speciality = speciality                              
    this.students = students                                  // через this прописываем значения свойств
}                                                             // используется для доступа к информации внутри объекта

Gruppa.prototype.sub_stud=function fn1(){                           // prototype - механизм, который оказывает влияние на то, как работают объекты в js
    document.write("<p>исключено " + k + " студентов</p>" )         // можно было впихнуть в перечисление свойств выше. если значние свойства - функция, то она является методом
}                                                                   // с помощью прототайп добавляем методы или свойства к объекту  
                                            // при объявлении любой функции в ней можно использовать this, но этот this не имеет значения до тех пор, пока функция не будет вызвана.
Gruppa.prototype.add_stud=function fn2(){                           // в каждом экземпляре this. различно, оно принимает значение только при вызове функции
    document.write("<p>добавлено " +h+ " студентов</p>")            // this всегда будет иметь значение, которое он получил при создании
    document.write("<p>в живых осталось " + (this.students-k+h) +  " студентов</p>")
}                                                                   // прототип наследует свойства

let gr1 = new Gruppa("ФИТ", "ИСИТ", 39)                             // создание экземпляра объекта                
document.write("<p> группа 1 </p>")                                 // если функция вызывается как метод, то this принимает значение объекта
gr1.sub_stud()                                                      // если как конутруктор, то this связан с новым создаваемым объектом
gr1.add_stud()
document.write("<br>")                                         

let gr2 = new Gruppa("ФИТ", "ПОИТ", 35)
document.write("<p> группа 2 </p>")
gr2.sub_stud()
gr2.add_stud()
document.write("<br>")   

let gr3 = new Gruppa("ФИТ", "ПОИБМС", 25)
document.write("<p> группа 3 </p>")
gr3.sub_stud()
gr3.add_stud()
document.write("<br>")   


// задание 3, используя оператор in проверяем наличие свойств в объектах
document.write("<br>")
document.write("<p>есть ли свойство facultet в gr2 " +('facultet' in gr2)+ "</p>")
document.write("<p>есть ли свойство nomer в gr3 " +('nomer' in gr3)+ "</p>")
// typeof
document.write("<br><p>typeof gr1.facultet: " +(typeof gr1.facultet)+ "</p>")
document.write("<p>typeof gr1: " +(typeof gr1)+ "</p>")