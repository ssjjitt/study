--����������� ��� �������� A � B �� ������� ���� ������ UNIVER. 
--�������� A ������������ ����� ����� ���������� � ������� ��������������� READ UNCOMMITED, 
--�����-��� B � ����� ���������� � ������� ��������������� READ COMMITED (�� ����-�����). 
--�������� A ������ �����-����������, ��� ������� READ UNCOMMITED �����-���� ����������������, '
--����-����������� � ��������� ������. 

SET TRANSACTION ISOLATION LEVEL READ UNCOMMITTED
BEGIN TRANSACTION
SELECT @@SPID, 'insert STUDENT' FROM STUDENT
WHERE IDSTUDENT = 1014
SELECT @@SPID, 'update STUDENT' FROM STUDENT
WHERE IDSTUDENT = 1014
commit

begin transaction 
select @@spid
insert STUDENT values(1013, 3, '�������� ��������� ����������', '2000-09-09')
update STUDENT set IDSTUDENT = 1014
where IDSTUDENT = 1013
ROLLBACK;