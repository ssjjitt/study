// свойства для доступа к объекту
// геттер - свойство-аксессор для чтения.
// сеттер - для записи, они позволяют присваиваивать значения объекта.

let jsInfo = {
    name: "javascipt",
    since: "1995",
    developerSurname: "Брендан",
    developerName: "",
    set devName(devName){
        this.developerName = devName;            // устанавливаем значение свойства developerName используя свойство devName
    },
    get fullInfo() {                                    // чтобы не дублировать уже имеющуюся инфу, используется геттер
        return `${this.name} ${this.since} ${this.developerSurname} ${this.developerName}`;
    }
}

jsInfo.devName = "Эйх";                                  // устанавливаем свойство с помощью сеттера

document.write(jsInfo.fullInfo) ;                        // НЕ ВЫЗОВ КАК ФУНКЦИИ, А ЧТЕНИЕ КАК ОБЫЧНОГО СВОЙСТВА
console.log(Object.entries(jsInfo));                     // вывод массива состоящего из пар ключ-значение