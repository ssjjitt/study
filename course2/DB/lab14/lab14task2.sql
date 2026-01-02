use UNIVER

--Разработать скалярную функцию с именем FSUBJECTS, принимающую параметр @p типа varchar(20), 
--значение которого задает код кафедры (столбец SUBJECT.PULPIT). 
--Функция должна возвращать строку типа varchar(300) с перечнем дисциплин в отчете. 

go

alter function FSUBJECTS(@p nvarchar(20)) returns nvarchar(300)
as 
begin
declare @tv char(20);
declare @t varchar(300) = 'Перечень дисциплин: ';
declare curs cursor local 
for select SUBJECT from SUBJECT as subj
join PULPIT as pulp on subj.PULPIT = pulp.PULPIT
where pulp.PULPIT = @p
open curs
fetch curs into @tv
while @@FETCH_STATUS = 0
begin
set @t = @t + ' ' + rtrim(@tv)
fetch curs into @tv
end;
return @t;
end;

go

select PULPIT, dbo.FSUBJECTS(PULPIT) from PULPIT