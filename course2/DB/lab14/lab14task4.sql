use UNIVER
go

drop function if exists FCTEACHER;
go

--�� ������� ���� ������� ��������, ��������������� ������ ��������� ������� FCTEACHER. 
--������� ���-������ ���� ��������, �������� ��� �������. 
--������� ���������� ���������� �������������� �� �������� ��-�������� �������. 
--���� �������� ����� NULL, �� ���-��������� ����� ���������� ��������������. 

create function FCTEACHER(@pul nvarchar(10)) returns int as
begin
declare @count int=(select count(*) from TEACHER
where PULPIT=isnull(@pul, PULPIT));
return @count;
end;

go


select PULPIT, dbo.FCTEACHER(PULPIT) [���������� ��������������] from PULPIT;

select dbo.FCTEACHER('����') [�� �����],dbo.FCTEACHER(null) [�����];