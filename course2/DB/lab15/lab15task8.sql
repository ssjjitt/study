/*8.  ��� ������� FACULTY ������� IN-STEAD OF-�������, ����������� �������� ����� � �������.
����������� ��������, ������� ���������-���� �� ������� ���� ������ X_UNIVER, ��� �������� ����������� ����������� ���������, ���� ���� INSTEAD OF-�������.
� ������� ��������� DROP ������� ��� DML-��������, ��������� � ���� ������������ ������.*/
use UNIVER
go
drop trigger if exists dbo.F_INSTEAD_OF
go

	create trigger F_INSTEAD_OF
	on FACULTY instead of DELETE
	as
        raiserror(N'�������� ���������', 10, 1);
	    rollback;
	return;
	    go

	 delete FACULTY where FACULTY = '����'
	    go

drop trigger if exists dbo.F_INSTEAD_OF
go