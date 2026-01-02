let person = {
    age: 18,
    name: 'Daria',
    surname: 'Gluhova'
  }
let withoutDeleteAge = ({age, ...rest}) => rest           // age исключается, а то, что осталось собирается в массив rest                  

let person2 = {...withoutDeleteAge(person), surname2: "Vitalievna", education: "BSTU"};     // копирование withoutDeleteAge(person) и добавление новых свойств
document.write(Object.values(person2)) 
console.log(person2) 