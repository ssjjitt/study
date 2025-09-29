/*
с помощью bom можно управлять поведением браузера используя js
window - корневой объект js, в котором хранятся все объекты, переменные и функции определяемые пользователем 
писать "window." при обращении к объектам и переменным необязательно: js подставляет его автоматически
то есть a = 10 то же, что и window.a = 10;
*/
let openOkno1=() =>
{
    window.okno1 = open()                                  // объект open() - метод объекта window - открывает новое пустое окно
}

let openOkno2=() =>
{
    okno2 = open()
}

let closeOkno1=() =>
{
    okno1.close()                                  // объект close() - метод объекта window - закрывает окно
}

let closeOkno2=() =>
{
    okno2.close()
}

let textOkno1=() =>
{
    okno1.document.write("текст в okno1")
}

let textOkno2=() =>
{
    okno2.document.write("текст в okno2")
}            