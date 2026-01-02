let jsInfo = 
{
    since: "1995"       //создание нового объекта
}; 

let jsName = "javascript";                
Object.defineProperty(jsInfo, 'name', {         // создаем свойство name в объекте jsInfo
  get: function() { return name = jsName; },             // геттер возвращабщий name
  set: function(reductionName) { this.reductionName = redName; },       // сеттер, чтобы записать значение redName  
  enumerable: true                                                      
});

jsInfo.redName = "js";
console.log(Object.entries(jsInfo)); 

