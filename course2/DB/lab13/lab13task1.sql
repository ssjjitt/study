/*1. ����������� �������� ��������� ��� ���������� � ������ PSUBJECT. �
�������� ��������� ��������-������ ����� �� ������ ������� SUBJECT, �����-������ ������, ��������������� �� �������:
� ����� ������ ��������� ������ ���������� ��-�������� �����, ���������� � �������������� �����.
*/
use UNIVER;
go

drop procedure if exists PSUBJECT;
go

GO
CREATE PROCEDURE PSUBJECT
AS
BEGIN
	DECLARE @count INT = (SELECT COUNT(*) FROM SUBJECT)
	SELECT SUBJECT as '���', SUBJECT_NAME as ����������, PULPIT as ������� FROM SUBJECT
	RETURN @count
END

GO
declare @res int = 0;
EXECUTE @res = PSUBJECT;
print 'result = ' + cast(@res as varchar(3))