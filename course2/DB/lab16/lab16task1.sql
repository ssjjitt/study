/*
1. ����������� �������� �������� XML-��������� � ������ PATH �� ���-���� TEACHER ��� �������������� ������� ����. 
*/

use UNIVER;
go

select *    from TEACHER inner join PULPIT
on TEACHER.PULPIT = PULPIT.PULPIT
where TEACHER.PULPIT = '����' for xml path, root('������_��������������_�������_����');
go


