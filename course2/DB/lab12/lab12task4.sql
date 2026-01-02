--Разработать два сценария A и B на примере базы данных UNIVER. 
--Сценарий A представляет собой явную транзакцию с уровнем изолированности READ UNCOMMITED, 
--сцена-рий B – явную транзакцию с уровнем изолированности READ COMMITED (по умол-чанию). 
--Сценарий A должен демон-стрировать, что уровень READ UNCOMMITED допус-кает неподтвержденное, '
--непо-вторяющееся и фантомное чтение. 

SET TRANSACTION ISOLATION LEVEL READ UNCOMMITTED
BEGIN TRANSACTION
SELECT @@SPID, 'insert STUDENT' FROM STUDENT
WHERE IDSTUDENT = 1014
SELECT @@SPID, 'update STUDENT' FROM STUDENT
WHERE IDSTUDENT = 1014
commit

begin transaction 
select @@spid
insert STUDENT values(1013, 3, 'Катюшина Екатерина Витальевна', '2000-09-09')
update STUDENT set IDSTUDENT = 1014
where IDSTUDENT = 1013
ROLLBACK;