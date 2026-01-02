use UNIVER
go

drop function if exists FCTEACHER;
go

--На рисунке ниже показан сценарий, демонстрирующий работу скалярной функции FCTEACHER. 
--Функция при-нимает один параметр, задающий код кафедры. 
--Функция возвращает количество преподавателей на заданной па-раметром кафедре. 
--Если параметр равен NULL, то воз-вращается общее количество преподавателей. 

create function FCTEACHER(@pul nvarchar(10)) returns int as
begin
declare @count int=(select count(*) from TEACHER
where PULPIT=isnull(@pul, PULPIT));
return @count;
end;

go


select PULPIT, dbo.FCTEACHER(PULPIT) [количество преподавателей] from PULPIT;

select dbo.FCTEACHER('ИСиТ') [на исите],dbo.FCTEACHER(null) [всего];