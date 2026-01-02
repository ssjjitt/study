/*
2. Разработать сценарий создания XML-документа в режиме AUTO на основе SE-LECT-запроса к таблицам AUDITORIUM и AUDITORIUM_TYPE, 
который содержит следующие столбцы: наименование аудито-рии, наименование типа аудитории и вмести-мость. 
Найти только лекционные аудитории. 
*/

use UNIVER;
go

select AUDITORIUM.AUDITORIUM [Аудитория], AUDITORIUM.AUDITORIUM_TYPE [Наимменование_типа], AUDITORIUM.AUDITORIUM_CAPACITY [Вместимость]
from AUDITORIUM join AUDITORIUM_TYPE on AUDITORIUM.AUDITORIUM_TYPE = AUDITORIUM_TYPE.AUDITORIUM_TYPE
where AUDITORIUM.AUDITORIUM_TYPE = 'ЛК' for xml path , root('Список_аудиторий');