--����������� ��������, �����-���������� ���������� ���-������ SAVE TRAN �� 
--���-���� ���� ������ UNIVER. 
--� ����� CATCH �����-�������� ������ �����������-���� ��������� �� �������. 
--���������� ������ �����-��� ��� ������������� ���-������ ����������� ����� � ��������� ���������� ����-������� ������.

USE UNIVER

declare @point varchar(32)
begin try
begin tran
delete SUBJECT where SUBJECT_NAME = '�����������'
set @point = 'p1' 
save tran @point
insert SUBJECT values('������', '������ �����������', '����')
set @point = 'p2' 
save tran @point 
insert SUBJECT values('���������', '�������������� ������', '����')
commit tran 
end try
begin catch
print 'error' + case
when error_number() = 2627 and patindex('%PK_STUDENT%', error_message()) > 0
then '������������ ��������'
else '����������� ������' + cast(error_number() as varchar(5)) + error_message()
end
if @@trancount > 0 
begin 
print '����������� �����: ' + @point
rollback tran @point 
end
end catch

