USE UNIVER

--����������� ��������, �����-���������� ������ � ������ ������� ����������.
--���������������� ������, ����������� ������, � ����-��� ��������� ������� �, 
--� ������� �������� ��� ������ �������.

set nocount on

if  exists (select * from  SYS.OBJECTS        
where OBJECT_ID= object_id(N'DBO.X') )	            
drop table X;           
declare @c int, @flag char = 'r';--���� ��� ����� r, �� ������� �� ����������, ���� � - ����������
SET IMPLICIT_TRANSACTIONS  ON   
CREATE table X(K int );                         
INSERT X values (1),(2),(3);
set @c = (select count(*) from X);
print '���������� ����� � ������� X: ' + cast( @c as varchar(2));
if @flag = 'c'  commit;                   
else   rollback;                          
SET IMPLICIT_TRANSACTIONS  OFF  
if  exists (select * from  SYS.OBJECTS     
where OBJECT_ID= object_id(N'DBO.X') )
print '������� X ����';  
else print '������� X ���'
