/*7. ����������� ��������, ��������������� �� ������� ���� ������ X_UNIVER �����-������: 
AFTER-������� �������� ������ ����-������, � ������ �������� ����������� �����-���, ���������������� �������.*/


use UNIVER
go

drop trigger if exists  dbo.PTran
go
create trigger PTran
on PULPIT after INSERT, DELETE, UPDATE
as
declare @c int = (select count (*) from PULPIT);
if (@c >22)
begin
raiserror('����� ���������� ������ �� ����� ���� >22', 10, 1);
rollback;
end;
return;
go
-- ��� ������� ��� ������ ���
insert into PULPIT(PULPIT) values ('�1���')

drop trigger if exists  dbo.PTran
go