--Разработать табличную функцию FFACPUL, результаты работы которой продемонстрированы на рисунке ниже.
--Функция принимает два параметра, задающих код фа-культета (столбец FACULTY.FACULTY) и код кафедры (столбец PULPIT.PULPIT). 
--Использует SELECT-запрос c левым внешним соединением между таблицами FACUL-TY и PULPIT. 
--Если оба параметра функции равны NULL, то она воз-вращает список всех кафедр на всех факультетах. 
--Если задан первый параметр (второй равен NULL), функция возвращает список всех кафедр заданного фа-культета. 
--Если задан второй параметр (первый равен NULL), функция возвращает результирующий набор, содержа-щий строку, соответствующую заданной кафедре.

use UNIVER
go

drop function if exists  FFACPUL
go

create function FFACPUL(@fac varchar(10), @pul varchar(10)) returns table
    as return
    select FACULTY.FACULTY, PULPIT.PULPIT
    from FACULTY left outer join PULPIT
    on FACULTY.FACULTY = PULPIT.FACULTY
where FACULTY.FACULTY=isnull(@fac, FACULTY.FACULTY) and PULPIT.PULPIT=isnull(@pul, PULPIT.PULPIT);
go


select * from dbo.FFACPUL(null,null);
select * from dbo.FFACPUL('ИДиП',null);
select * from dbo.FFACPUL(null,'ИСиТ');

