USE Gl_MyBase

SELECT * From Преподаватели;

SELECT код_преподавателя, предмет  From Курсы;

SELECT count(*) [отчество] From Преподаватели 
	WHERE отчество = 'Иванович'

UPDATE Преподаватели SET оплата = оплата + 500 WHERE оплата < 8000 

DELETE From Преподаватели WHERE стаж > 6 

Select * FROM Преподаватели

UPDATE Преподаватели SET СТАЖ = стаж + 1 where стаж > 6

--ALTER Table Преподаватели ADD стаж INT default '1'
--DROP Table Курсы 
--ALTER Table Преподаватели DROP Column стаж 
