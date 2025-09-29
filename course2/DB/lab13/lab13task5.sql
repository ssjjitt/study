/*
����������� ��������� � ������ SUB-JECT_REPORT, ����������� � ����������� �������� ����� ����� �� ������� ��������� �� ���������� �������.
� ����� ������ ���� �������� ������� �������� (���� SUBJECT) �� ������� SUBJECT � ���� ����-�� ����� ������� (������������ ���������� ����-��� RTRIM
��������� ����� ������� �������� � ������ @p ���� CHAR(10), ������� ������������ ��� �����-��� ���� �������.
��������� SUBJECT_REPORT ������ ���-������� � ����� ������ ���������� ���������, ������������ � ������
*/
Use UNIVER
go

drop procedure if exists SUBJECT_REPORT
go

CREATE PROCEDURE SUBJECT_REPORT @p NVARCHAR(MAX)
AS
DECLARE @rc INT = 0
BEGIN TRY
	DECLARE @sb NVARCHAR(20), @result NVARCHAR(MAX) = ''

	DECLARE SUBJECTS CURSOR FOR SELECT SUBJECT.SUBJECT FROM SUBJECT WHERE SUBJECT.PULPIT = rtrim(@p)
	IF NOT EXISTS (SELECT SUBJECT.SUBJECT FROM SUBJECT WHERE SUBJECT.PULPIT = rtrim(@p))
		RAISERROR('ERROR', 11, 1)
	ELSE
		OPEN SUBJECTS
		FETCH SUBJECTS INTO @sb
		PRINT 'SUBJECTS:'
		WHILE @@FETCH_STATUS = 0
		BEGIN
			SET @result = rtrim(@sb) + ', ' + rtrim(@result)
			SET @rc = @rc + 1
			FETCH SUBJECTS INTO @sb
		END
		PRINT @result
		CLOSE SUBJECTS
	    DEALLOCATE SUBJECTS
		RETURN @rc
END TRY
BEGIN CATCH
	PRINT '������ � ����������';
	IF ERROR_PROCEDURE() IS NOT NULL
		PRINT '��� ��������� : ' + ERROR_PROCEDURE()
	RETURN @rc
END CATCH
GO

declare @res int;
exec @res = SUBJECT_REPORT '����'
print '���������� ��������� = ' + cast(@res as varchar(3));




