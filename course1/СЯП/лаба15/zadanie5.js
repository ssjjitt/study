let person = {
  age: 18,
  name: 'Daria',
  surname: 'Gluhova'
}
let deleteAge = ({age, ...rest}) => rest           // age исключается, а то, что осталось собирается в массив rest
console.log(deleteAge(person))