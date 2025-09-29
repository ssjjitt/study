// создаем объект, используя литерал объекта
let proto =                             
{
    name: "Дарья",              
    surname: "Глухова",
    surname2: "Витальевна",
    information: function(){                           
    document.write(this.surname + " " + this.name +" "+ this.surname2);         // Значение this вычисляется во время выполнения кода, в зависимости от контекста.
}  
}

let proto1 = Object.create(proto);                          // создаем новый объект
proto1.information();                                       

document.write("<br>")

let proto2 = Object.create(proto);                         // создаем еще один объекта
proto2.name="Ольга";                                       // но здесь уже изменяем свойства
proto2.surname2="Михайловна";
proto2.information();