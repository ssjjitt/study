/*9. ������� DDL-�������, ����������� �� ��� DDL-������� � �� UNIVER. 
������� ������ ��������� ��������� ��-��� ������� � ������� ������������. 
���������� ������� ������ ������������ ����������, ������� ��������: 
��� �������, ��� � ��� �������, � ����� ������������� �����, � ������ ���������� ���������� ���-������. 
����������� ��������, ��������������� ������ ��������. 
*/

use UNIVER;
go
drop trigger if exists  DDL_UNIVER on database;
go

	create  trigger DDL_UNIVER on database
                    for DDL_DATABASE_LEVEL_EVENTS
	    as
        raiserror('�������� � �� ���������', 10, 1);
	    rollback;
	return;
	go

	

	drop table  TR_AUDIT;


	 drop trigger if exists  DDL_UNIVER on database;