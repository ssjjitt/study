/*
1. Разработать сценарий создания XML-документа в режиме PATH из таб-лицы TEACHER для преподавателей кафедры ИСиТ. 
*/

use UNIVER;
go

select *    from TEACHER inner join PULPIT
on TEACHER.PULPIT = PULPIT.PULPIT
where TEACHER.PULPIT = 'ИСиТ' for xml path, root('Список_преподавателей_кафедры_ИСиТ');
go


