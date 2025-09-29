let array = ["JA", "VA", "SC", "RI", "PT"];

array = array.map(num=>num.padStart(10, "1"));
array = array.map(num=>num.padEnd(14));
array = array.map(num=>num.padEnd(15, "0"));

console.log(array);
