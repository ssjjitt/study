/*
2. ����������� �������� �������� XML-��������� � ������ AUTO �� ������ SE-LECT-������� � �������� AUDITORIUM � AUDITORIUM_TYPE, 
������� �������� ��������� �������: ������������ ������-���, ������������ ���� ��������� � ������-�����. 
����� ������ ���������� ���������. 
*/

use UNIVER;
go

select AUDITORIUM.AUDITORIUM [���������], AUDITORIUM.AUDITORIUM_TYPE [�������������_����], AUDITORIUM.AUDITORIUM_CAPACITY [�����������]
from AUDITORIUM join AUDITORIUM_TYPE on AUDITORIUM.AUDITORIUM_TYPE = AUDITORIUM_TYPE.AUDITORIUM_TYPE
where AUDITORIUM.AUDITORIUM_TYPE = '��' for xml path , root('������_���������');