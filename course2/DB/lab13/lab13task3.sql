/*
3. ������� ��������� ��������� ������� � ���-��� #SUBJECT. ������������ � ��� �������� ���-���� ������ ��������������� �������� ��������-������� ������ ��������� PSUBJECT, �������-������ � ������� 2. 
�������� ��������� PSUBJECT ����� �������, ����� ��� �� ��������� ��������� ���������.
�������� ����������� INSERT� EXECUTE � ���������������� ���������� PSUBJECT, ����-���� ������ � ������� #SUBJECT. 
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

INSERT #SUBJECT EXEC PSUBJECT @p = '����'
select * from #SUBJECT