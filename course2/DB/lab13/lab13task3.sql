/*
3. Создать временную локальную таблицу с име-нем #SUBJECT. Наименование и тип столбцов таб-лицы должны соответствовать столбцам результи-рующего набора процедуры PSUBJECT, разрабо-танной в задании 2. 
Изменить процедуру PSUBJECT таким образом, чтобы она не содержала выходного параметра.
Применив конструкцию INSERT… EXECUTE с модифицированной процедурой PSUBJECT, доба-вить строки в таблицу #SUBJECT. 
*/
use UNIVER
go

CREATE TABLE #SUBJECT (
	[SUBJECT] NVARCHAR(20) PRIMARY KEY,
	[SUBJECT_NAME] NVARCHAR(MAX),
	[PULPIT] NVARCHAR(MAX)
	)
go
ALTER PROCEDURE PSUBJECT @p NVARCHAR(20)
AS
BEGIN
	SELECT * FROM SUBJECT
	WHERE SUBJECT.PULPIT = @p
END
GO

INSERT #SUBJECT EXEC PSUBJECT @p = 'ИСиТ'
select * from #SUBJECT