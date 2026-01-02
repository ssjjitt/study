// Object.keys(obj) – возвращает массив ключей.
// Object.values(obj) – возвращает массив значений.

let information = 
{
    name: "Дарья",              
    surname: "Глухова",
    surname2: "Витальевна"
}  

document.write("<br>Массив значений: " +Object.values(information));
document.write("<br>Массив ключей: " +Object.keys(information));