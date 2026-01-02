USE UNIVER;
--1
--Определить все индексы, которые имеются в БД UNIVER.
--Создать временную локальную таблицу. Заполнить ее данными (не менее 1000 строк). 
--Разработать SELECT-запрос. Получить план запроса и опреде-лить его стоимость. 
--Создать кластеризованный ин-декс, уменьшающий стоимость SE-LECT-запроса.
exec sp_helpindex 'AUDITORIUM';
exec sp_helpindex 'AUDITORIUM_TYPE';
exec sp_helpindex 'FACULTY';
exec sp_helpindex 'GROUPS';
exec sp_helpindex 'PROFESSION';
exec sp_helpindex 'PROGRESS';
exec sp_helpindex 'PULPIT';
exec sp_helpindex 'STUDENT';
exec sp_helpindex 'SUBJECT';
exec sp_helpindex 'TEACHER';
create table #temp_table (
    some_ind int,
    some_field varchar(20)
);
set nocount on;
declare @i int = 0;
while @i < 2000
begin
insert into #temp_table (some_ind, some_field)
values (@i, replicate('test ', 3));
set @i = @i + 1;
end;
select *
from #temp_table
where some_ind BETWEEN 1500 AND 2000
order by some_ind;
checkpoint;
dbcc DROPCLEANBUFFERS;

create clustered index #temp_table_cl on #temp_table(some_ind asc);

drop index #temp_table_cl on #temp_table;
drop table #temp_table;
go


--2. Создать временную локаль-ную таблицу. Заполнить ее данны-ми (10000 строк или больше). 
--Разработать SELECT-запрос. Получить план запроса и опреде-лить его стоимость. 
--Создать некластеризованный не-уникальный составной индекс. 
CREATE TABLE #temp_table_1
(
    some_ind   INT,
    some_field VARCHAR(20),
    cc         INT IDENTITY (1,1)
);
SET NOCOUNT ON;
DECLARE @j INT = 0;
WHILE @j < 10000
BEGIN
INSERT INTO #temp_table_1 (some_ind, some_field)
VALUES (FLOOR(RAND() * 10000), 'str' + CAST(@j AS NVARCHAR(1000)));
SET @j = @j + 1;
END;
SELECT *
FROM #temp_table_1
WHERE cc > 500
AND some_ind BETWEEN 1500 AND 5000;
GO

CREATE NONCLUSTERED INDEX IX_NonClusteredIndex
ON #temp_table_1 (cc, some_ind);

SELECT *
FROM #temp_table_1
WHERE some_ind = 556
AND cc > 3;
DROP TABLE #temp_table_1;
go


--3. Создать временную локальную таблицу. Заполнить ее данными (не менее 10000 строк). 
--Разработать SELECT-запрос. Получить план запроса и опреде-лить его стоимость. 
--Создать некластеризованный ин-декс покрытия, уменьшающий стоимость SELECT-запроса
CREATE TABLE #temp_table_2
(
    some_ind INT,
    some_field VARCHAR(20),
    cc INT IDENTITY(1,1)
);
SET NOCOUNT ON;
DECLARE @k INT = 0;
WHILE @k < 30000
BEGIN
INSERT INTO #temp_table_2 (some_ind, some_field)
VALUES (FLOOR(RAND() * 30000), REPLICATE('test2', 3));
SET @k = @k + 1;
END;
SELECT cc
FROM #temp_table_2
WHERE some_ind > 500;
GO

CREATE NONCLUSTERED INDEX IX_CoveringIndex
ON #temp_table_2 (some_ind)
INCLUDE (cc, some_field);

drop index IX_CoveringIndex on #temp_table_2
drop table #temp_table_2
go


--4. Создать и заполнить времен-ную локальную таблицу. 
--Разработать SELECT-запрос, получить план запроса и опреде-лить его стоимость. 
--Создать некластеризованный фильтруемый индекс, уменьшаю-щий стоимость SELECT-запроса.
use UNIVER;
go
create table #temp_table_3
(
	some_ind int,
	some_field varchar(20),
	cc int identity(1,1)
)

SET nocount on;
DECLARE @k int = 0;
while @k < 30000
begin
	insert #temp_table_3(some_ind, some_field)
		values(FLOOR(RAND()*30000), REPLICATE('test2',3) );
	SET @k = @k + 1;
end
SELECT some_ind from  #temp_table_3 where some_ind between 5000 and 19999;
SELECT some_ind from  #temp_table_3 where some_ind>15000 and  some_ind < 20000

CREATE  index #temp_table_WHERE on #temp_table_3(some_ind) where (some_ind>15000 and
some_ind  < 20000);

drop index #temp_table_WHERE on #temp_table_3
go


 --5. Заполнить временную локальную таблицу. 
--Создать некластеризованный индекс. Оценить уровень фрагмен-тации индекса. 
--Разработать сценарий на T-SQL, выполнение которого приводит к уровню фрагментации индекса выше 90%. 
--Оценить уровень фрагментации индекса. 
--Выполнить процедуру реоргани-зации индекса, оценить уровень фрагментации. 
--Выполнить процедуру пере-стройки индекса и оценить уро-вень фрагментации индекса.
CREATE TABLE #temp_table (
    some_ind   INT,
    some_field VARCHAR(20)
);
SET NOCOUNT ON;
DECLARE @i INT = 0;
WHILE @i < 1000
BEGIN
    INSERT INTO #temp_table (some_ind, some_field)
    VALUES (@i, REPLICATE('test ', 3));
    SET @i = @i + 1;
END;

CREATE NONCLUSTERED INDEX IX_NonClusteredIndex
ON #temp_table (some_ind);

-- Оценка уровня фрагментации
DBCC SHOWCONTIG ('#temp_table', 'IX_NonClusteredIndex');
-- фрагментации индекса выше 90%
DELETE FROM #temp_table WHERE some_ind BETWEEN 200 AND 500;
DBCC SHOWCONTIG ('#temp_table', 'IX_NonClusteredIndex');
ALTER INDEX IX_NonClusteredIndex ON #temp_table REORGANIZE; --реорганізація
DBCC SHOWCONTIG ('#temp_table', 'IX_NonClusteredIndex');
-- Процедура перестройки индекса
ALTER INDEX IX_NonClusteredIndex ON #temp_table REBUILD; -- перестсройка
DBCC SHOWCONTIG ('#temp_table', 'IX_NonClusteredIndex');
DROP INDEX IX_NonClusteredIndex ON #temp_table;
DROP TABLE #temp_table;

--6. Разработать пример, демонстри-рующий применение параметра FILLFACTOR при создании некла-стеризованного индекса.
CREATE TABLE SampleTable (
    Id INT PRIMARY KEY,
    Name VARCHAR(50)
);
INSERT INTO SampleTable (Id, Name)
VALUES (1, 'John'),
       (2, 'Jane'),
       (3, 'Mark'),
       (4, 'Alice'),
       (5, 'Bob');

CREATE NONCLUSTERED INDEX IX_NonClusteredIndex
ON SampleTable (Id)
WITH (FILLFACTOR = 80);

INSERT INTO SampleTable (Id, Name)
VALUES (6, 'Tom'),
       (7, 'Sarah');
-- Получение информации о заполнении страниц индекса
DBCC SHOWCONTIG ('SampleTable', 'IX_NonClusteredIndex');
DROP INDEX IX_NonClusteredIndex ON SampleTable;
DROP TABLE SampleTable;