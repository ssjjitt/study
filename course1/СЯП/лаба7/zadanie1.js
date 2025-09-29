function MyFunction() {

for (let i = 0; i < document.form.kyrs.length; i++) {           
    if (document.form.kyrs[i].checked) {                        
        kyrs = document.form.kyrs[i].value;
        break;
    }
}

document.write("Студент " +document.form.lastname.value+ " специальность " +document.form.select.options[document.form.select.selectedIndex].text+ " курс " +kyrs+ " должен сдавать следующие предметы: ");

dovument.write(document.form.predmet[1].value)

document.write("<ul>");
for (let j = 0; j < document.form.predmet.length; j++) {           
    if (document.form.predmet[j].checked) {                        
        predm = document.form.predmet[j].value;
            document.write("<li>" +predm+ "</li>");
    }

}
document.write("</ul>")

}
/*
name. Имя объекта.
selectedIndex. Номер выбранного элемента или первого среди выбранных (если указан атрибут MULTIPLE).
length. Количество элементов (строк) в списке.
options. Массив элементов списка, заданных тегами OPTION.
*/
