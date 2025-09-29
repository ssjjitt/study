use UNIVER

--Разработать скалярную функцию с именем COUNT_STUDENTS, которая вычисляет количество студентов на факультете, код которого задается парамет-ром типа varchar(20) с именем @faculty. 
--Использовать внутреннее соединение таблиц FACULTY, GROUPS, STUDENT. Опробовать работу функции.

go

create function COUNT_STUDENTS(@faculty nvarchar(20)) returns int 
as begin declare @rc int = 0;
set @rc = (select count(*) from STUDENT as stud 
join GROUPS as gr on stud.IDGROUP = gr.IDGROUP 
join FACULTY as fac on gr.FACULTY = fac.FACULTY 
where fac.FACULTY = @faculty);
return @rc;
end;

go

drop function COUNT_STUDENTS;

go

declare @fun int = dbo.COUNT_STUDENTS('ТОВ');
print 'количество студентов: ' + cast(@fun as varchar(4));

go 

--Внести изменения в текст функции с помощью операто-ра ALTER с тем, чтобы функция принимала второй пара-метр @prof типа varchar(20), 
--обозначающий специаль-ность студентов. Для параметров определить значения по умолчанию NULL. Опробовать работу функции с помо-щью SELECT-запросов.

alter function COUNT_STUDENTS(
@faculty nvarchar(20),
@prof nvarchar(60)
) returns int
as 
begin
declare @rc int = 0
set @rc = (
select count(*) from STUDENT as stud 
join GROUPS as gr on stud.IDGROUP = gr.IDGROUP 
join FACULTY as fac on gr.FACULTY = fac.FACULTY 
join PROFESSION as prof on prof.PROFESSION = gr.PROFESSION
where fac.FACULTY = @faculty and (prof.PROFESSION_NAME =@prof));
return @rc;
end;

declare @fun2 int = dbo.COUNT_STUDENTS('ТОВ', 'Химическая технология переработки древесины');
print 'количество студентов: ' + cast(@fun2 as varchar(4));
