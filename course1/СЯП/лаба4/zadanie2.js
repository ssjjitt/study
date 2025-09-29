function Student(name, surname, math, fiz, infa)
{
    this.name = name
    this.surname = surname
    this.math = math
    this.fiz = fiz
    this.infa = infa
    this.information = function information(){
        document.write("<p>имя: " +name+  "</p><p>фамилия: " +surname+ "</p></p>математика: " +math+ "</p><p>физика: " +fiz+ "</p><p>информатика: " +infa+ "</p>")
    }
}

Student.prototype.okno=function fn1(){
    alert("имя: " +this.name+ " фамилия: " +this.surname+ " ")
}

Student.prototype.ball=function fn2(){
    document.write("средний балл: " +(this.math + this.fiz + this.infa) / 3+ "</p>")
}

Student.prototype.svoistvo=function fn3(){                    
    if((this.math > 4) && (this.math < 7)) document.write("<p>знает математику на среднем уровне</p><br>")
    else if ((this.math < 4) && (this.math > 0)) document.write("<p>не знает математику, чайковский негодует</p><br>")
    else document.write("<p>отлично знает математику, чайковский похвалил</p><br>")
}

let student1 = new Student("Мария", "Дубина", 3, 5, 4)
student1.information()
student1.ball()
student1.svoistvo()

let student2 = new Student("Алина", "Маевская", 8, 9, 10)
student2.information()
student2.ball()
student2.svoistvo()

let student3 = new Student("Дарья", "Глухова", 5, 6, 1)
student3.information()
student3.ball()
student3.okno()
student3.svoistvo()

//zadanie3
document.write("<p>typeof student1.name: " +(typeof student1.name)+ "</p>")             // определяем к какому типу относятся значения: string, number, function....
document.write("<p>typeof student1.surname: " +(typeof student1.surname)+ "</p>")
document.write("<p>typeof student1.math: " +(typeof student1.math)+ "</p>")
document.write("<p>typeof student1.fiz: " +(typeof student1.fiz)+ "</p>")
document.write("<p>typeof student1.infa: " +(typeof student1.infa)+ "</p>")
document.write("<p>typeof student1.information: " +(typeof student1.information)+ "</p>")
document.write("<p>typeof student1: " +(typeof student1)+ "</p>")
document.write("<p>typeof student1.okno: " +(typeof student1.okno)+ "</p>")
document.write("<p>typeof student1.ball: " +(typeof student1.ball)+ "</p>")
document.write("<p>typeof student1.svoistvo: " +(typeof student1.svoistvo)+ "</p>")