--����������� ��������, �����-���������� �������� ���-�������� ����� ���������� 
--�� ������� ���� ������ UNI-VER. 
--� ����� CATCH �����-�������� ������ �����������-���� ��������� �� �������. 
--���������� ������ �����-��� ��� ������������� ���-������ ���������� ������-����� ������.
USE UNIVER

begin try
begin tran
delete STUDENT WHERE IDSTUDENT = 1012
insert STUDENT values(2, '������������ ������ ��������','22.11.1993')
insert STUDENT values(2, '����������� �������� ��������','22.11.1993')
commit tran
end try
begin catch
print 'error' + case
when error_number() = 2627 and patindex('%PK_STUDENT%', error_message()) > 0
then '������������ ��������'
else '����������� ������' + cast(error_number() as varchar(5)) + error_message()
end
if @@trancount > 0 rollback tran
end catch
