/*5. ����������� ��������, ������� �����-�������� �� ������� ���� ������ X_UNIVER, ��� �������� ����������� ����������� �����-������ �� ������������ AFTER-��������.*/

use UNIVER
go

select * from TR_AUDIT
go;

/*alter table TEACHER  add constraint GENDER check (GENDER = '�'or GENDER='�')*/

update TEACHER set GENDER = 'q' where TEACHER='���'
select * from TR_AUDIT