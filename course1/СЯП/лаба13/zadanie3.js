let symbol = prompt("введите символ: ");

let firstArray = ["," , ".", "/", "]", ";", ">"];
let secondArray = ["|", "[", ">"];
let thirdArray = ["а", "б", "в"];

document.write("<br>имеется ли символ в firstArray: "+ firstArray.includes(symbol));
document.write("<br>имеется ли символ в secondArray: "+ secondArray.includes(symbol));
document.write("<br>имеется ли символ в thirdArray: "+ thirdArray.includes(symbol));
