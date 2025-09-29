--����������� ��������� ������� FFACPUL, ���������� ������ ������� ������������������ �� ������� ����.
--������� ��������� ��� ���������, �������� ��� ��-�������� (������� FACULTY.FACULTY) � ��� ������� (������� PULPIT.PULPIT). 
--���������� SELECT-������ c ����� ������� ����������� ����� ��������� FACUL-TY � PULPIT. 
--���� ��� ��������� ������� ����� NULL, �� ��� ���-������� ������ ���� ������ �� ���� �����������. 
--���� ����� ������ �������� (������ ����� NULL), ������� ���������� ������ ���� ������ ��������� ��-��������. 
--���� ����� ������ �������� (������ ����� NULL), ������� ���������� �������������� �����, �������-��� ������, ��������������� �������� �������.

use UNIVER
go

drop function if exists  FFACPUL
go

create function FFACPUL(@fac varchar(10), @pul varchar(10)) returns table
    as return
    select FACULTY.FACULTY, PULPIT.PULPIT
    from FACULTY left outer join PULPIT
    on FACULTY.FACULTY = PULPIT.FACULTY
where FACULTY.FACULTY=isnull(@fac, FACULTY.FACULTY) and PULPIT.PULPIT=isnull(@pul, PULPIT.PULPIT);
go


select * from dbo.FFACPUL(null,null);
select * from dbo.FFACPUL('����',null);
select * from dbo.FFACPUL(null,'����');

