USE UNIVER
--1. объявить переменные типа char, varchar, datetime, time, int, smallint, ti-nint, numeric(12, 5); 
--первые две переменные проинициали-зировать в операторе объявления;
declare @mychar char = 'c',
@myvarchar varchar(4) = 'и',
@mydatetime datetime,
@mytime time,
@mysmallint smallint,
@mytinyint tinyint,
@mynumeric numeric(12, 5);

--присвоить произвольные значения пе-ременным с помощью операторов SET и select; 
set @mysmallint = 4;
set @mytinyint = 53;
set @mynumeric = 4.54213;
select @mydatetime = GETDATE();  
select @mytime = GETDATE();  

--значения одних переменных вывести с помощью оператора select, значе-ния других переменных распечатать с помощью оператора PRINT
select @mychar as mychar, @myvarchar as myvarchar, @mydatetime as mydatetime, @mytime as mytime;
print 'mysmallint: ' +cast(@mysmallint as varchar(10));
print 'mytinyint: ' +cast(@mytinyint as varchar(10));
print 'mynumeric: ' +cast(@mynumeric as varchar(10));

--2. Разработать скрипт, в котором опре-деляется общая вместимость аудиторий
declare @auditoriumCapacity int;
select @auditoriumCapacity = sum(AUDITORIUM_CAPACITY) from AUDITORIUM;
if @auditoriumCapacity > 200
begin
    declare @kolvoAuditorium int;
    select @kolvoAuditorium = count(*) from AUDITORIUM;
    
	declare @avgAuditorium float;
    select @avgAuditorium = avg(AUDITORIUM_CAPACITY) from AUDITORIUM;

    declare @numSmallAuditoriums int;
    select @numSmallAuditoriums = count(*) from AUDITORIUM where AUDITORIUM_CAPACITY < @avgAuditorium;

    declare @percentSmallAuditoriums float;
    select @percentSmallAuditoriums = cast(@numSmallAuditoriums as float) / @kolvoAuditorium * 100;

	print ''
    print 'Количество: ' + cast(@kolvoAuditorium as varchar);
    print 'Средняя вместимость: ' + cast(@avgAuditorium as varchar);
    print 'Количество, вместимость которых меньше средней: ' + cast(@numSmallAuditoriums as varchar);
    print 'Процент, вместимость которых меньше средней: ' + cast(@percentSmallAuditoriums as varchar) + '%';
end
else
begin
    print 'Общая вместимость: ' + cast(@auditoriumCapacity as varchar);
end

--3. Разработать T-SQL-скрипт, ко-торый выводит на печать глобальные переменные
print ''
print 'число обработанных строк: ' + cast(@@ROWCOUNT as varchar(100));
print 'версия SQL Server: ' + cast(@@VERSION as varchar(100));
print 'системный идентификатор процесса для текущего подключения: ' + cast(@@SPID as varchar(100));
print 'код последней ошибки: ' + cast(@@ERROR as varchar(100));
print 'имя сервера: ' + cast(@@SERVERNAME as varchar(100));
print 'уровень вложенности транзакции: ' + cast(@@TRANCOUNT as varchar(100));
print 'результат считывания строк результирующего набора: ' + cast(@@FETCH_STATUS as varchar(100));
print 'уровень вложенности текущей процедуры: ' + cast(@@NESTLEVEL as varchar(100));

--4. вычисление значений переменной z 
declare @x int = 2, @t int = 3, @z float;
if (@t > @x) set @z = power(sin(@t), 2);
else if (@t < @x) set @z = 4 * (@t + @x);
else set @z = 1 - exp(@x - 2);
print '';
print 'x = ' + cast(@x as varchar(10));
print 't = ' + cast(@t as varchar(10));
print 'z = ' + cast(@z as varchar(10));

--преобразование полного ФИО студен-та в сокращенное 
declare @FIO varchar(100)
declare @TempTable table
(
    LastName varchar(100)
)
insert into @TempTable (LastName)
select substring(NAME, 1, charindex(' ', NAME))
       + substring(NAME, charindex(' ', NAME) + 1, 1) + '.'
       + substring(NAME, charindex(' ', NAME, charindex(' ', NAME) + 1) + 1, 1) + '.'
from STUDENT
select * from @TempTable

--поиск студентов, у которых день рож-дения в следующем месяце, и определение их возраста;
select NAME, BDAY, datediff(year, BDAY, getdate()) AS Возраст
from STUDENT where month(BDAY) = month(dateadd(month, 1, getdate()));

--поиск дня недели, в который студенты некоторой группы сдавали экзамен по БД.
select *
from (select *,
(CASE
when datepart(weekday, PDATE) = 1 then 'Понедельник'
when datepart(weekday, PDATE) = 2 then 'Вторник'
when datepart(weekday, PDATE) = 3 then 'Среда'
when datepart(weekday, PDATE) = 4 then 'Четверг'
when datepart(weekday, PDATE) = 5 then 'Пятница'
when datepart(weekday, PDATE) = 6 then 'Суббота'
when datepart(weekday, PDATE) = 7 then 'Воскресенье'
end) День_недели
from PROGRESS
where SUBJECT like '%СУБД%') as tr;

--5. Продемонстрировать конструкцию IF… ELSE
declare @numberOfGroups int = 20;
declare @kolvoGroups int = (select count(*) from GROUPS)

if (select count(*) from GROUPS) > @numberOfGroups
begin
print 'Количество групп больше '+ cast(@numberOfGroups as varchar);
print 'Количество '+ cast(@kolvoGroups as varchar);
end
else
begin
print 'Количество групп меньше ' + cast(@numberOfGroups as varchar);
print 'Количество '+ cast(@kolvoGroups as varchar);
end

--6. Разработать сценарий, в котором с помощью CASE анализируются оцен-ки, полученные студентами некоторо-го факультета при сдаче экзаменов
select IDSTUDENT,
avg(NOTE) as балл,
case
when avg (PROGRESS.NOTE) = 4 then 'Сойдет'
when avg (PROGRESS.NOTE) between 5 and 6 then 'Тоже добре'
when avg (PROGRESS.NOTE) between 7 and 8 then 'Добренько'
when avg (PROGRESS.NOTE) between 9 and 10 then 'Добрейше'
else 'Не определено'
end [Анализ среднего балла]
from PROGRESS
group by IDSTUDENT

--7. Создать временную локальную табли-цу из трех столбцов и 10 строк, заполнить ее и вывести содержимое. Ис-пользовать оператор WHILE.
declare @Fam varchar(100)
declare @TempTable2 table
(
	ID int identity(1,1),
    LastName varchar(100),
	Birth varchar(100)
)
declare @iter int = 1;
while @iter <= 10
begin
insert into @TempTable2 (LastName, Birth)
select top 1 NAME, BDAY
from STUDENT
order by newid();
set @iter = @iter + 1;
end
select * from @TempTable2

--8. Разработать скрипт, демонстрирующий использование оператора RETURN. 
DECLARE @note int = 8;
print @note+1
print @note+2
RETURN 
print @note+3

--9. Разработать сценарий с ошибками, в котором используются для обработки ошибок блоки TRY и CATCH. 
begin try
select 1 / 0
end try 
begin catch
print 'Error Number: ' + cast(error_number() as varchar(10))
print 'Error Message: ' + error_message()
print 'Error Line: ' + cast(error_line() as varchar(10))
print 'Error Procedure: ' + isnull(error_procedure(), 'N/A')
print 'Error Severity: ' + cast(error_severity() as varchar(10))
print 'Error State: ' + cast(error_state() as varchar(10))
end catch