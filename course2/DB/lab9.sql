USE UNIVER
--1. �������� ���������� ���� char, varchar, datetime, time, int, smallint, ti-nint, numeric(12, 5); 
--������ ��� ���������� �����������-�������� � ��������� ����������;
declare @mychar char = 'c',
@myvarchar varchar(4) = '�',
@mydatetime datetime,
@mytime time,
@mysmallint smallint,
@mytinyint tinyint,
@mynumeric numeric(12, 5);

--��������� ������������ �������� ��-�������� � ������� ���������� SET � select; 
set @mysmallint = 4;
set @mytinyint = 53;
set @mynumeric = 4.54213;
select @mydatetime = GETDATE();  
select @mytime = GETDATE();  

--�������� ����� ���������� ������� � ������� ��������� select, �����-��� ������ ���������� ����������� � ������� ��������� PRINT
select @mychar as mychar, @myvarchar as myvarchar, @mydatetime as mydatetime, @mytime as mytime;
print 'mysmallint: ' +cast(@mysmallint as varchar(10));
print 'mytinyint: ' +cast(@mytinyint as varchar(10));
print 'mynumeric: ' +cast(@mynumeric as varchar(10));

--2. ����������� ������, � ������� ����-�������� ����� ����������� ���������
declare @auditoriumCapacity int;
select @auditoriumCapacity = sum(AUDITORIUM_CAPACITY) from AUDITORIUM;
if @auditoriumCapacity > 200
begin
    declare @kolvoAuditorium int;
    select @kolvoAuditorium = count(*) from AUDITORIUM;
    
	declare @avgAuditorium float;
    select @avgAuditorium = avg(AUDITORIUM_CAPACITY) from AUDITORIUM;

    declare @numSmallAuditoriums int;
    select @numSmallAuditoriums = count(*) from AUDITORIUM where AUDITORIUM_CAPACITY < @avgAuditorium;

    declare @percentSmallAuditoriums float;
    select @percentSmallAuditoriums = cast(@numSmallAuditoriums as float) / @kolvoAuditorium * 100;

	print ''
    print '����������: ' + cast(@kolvoAuditorium as varchar);
    print '������� �����������: ' + cast(@avgAuditorium as varchar);
    print '����������, ����������� ������� ������ �������: ' + cast(@numSmallAuditoriums as varchar);
    print '�������, ����������� ������� ������ �������: ' + cast(@percentSmallAuditoriums as varchar) + '%';
end
else
begin
    print '����� �����������: ' + cast(@auditoriumCapacity as varchar);
end

--3. ����������� T-SQL-������, ��-����� ������� �� ������ ���������� ����������
print ''
print '����� ������������ �����: ' + cast(@@ROWCOUNT as varchar(100));
print '������ SQL Server: ' + cast(@@VERSION as varchar(100));
print '��������� ������������� �������� ��� �������� �����������: ' + cast(@@SPID as varchar(100));
print '��� ��������� ������: ' + cast(@@ERROR as varchar(100));
print '��� �������: ' + cast(@@SERVERNAME as varchar(100));
print '������� ����������� ����������: ' + cast(@@TRANCOUNT as varchar(100));
print '��������� ���������� ����� ��������������� ������: ' + cast(@@FETCH_STATUS as varchar(100));
print '������� ����������� ������� ���������: ' + cast(@@NESTLEVEL as varchar(100));

--4. ���������� �������� ���������� z 
declare @x int = 2, @t int = 3, @z float;
if (@t > @x) set @z = power(sin(@t), 2);
else if (@t < @x) set @z = 4 * (@t + @x);
else set @z = 1 - exp(@x - 2);
print '';
print 'x = ' + cast(@x as varchar(10));
print 't = ' + cast(@t as varchar(10));
print 'z = ' + cast(@z as varchar(10));

--�������������� ������� ��� ������-�� � ����������� 
declare @FIO varchar(100)
declare @TempTable table
(
    LastName varchar(100)
)
insert into @TempTable (LastName)
select substring(NAME, 1, charindex(' ', NAME))
       + substring(NAME, charindex(' ', NAME) + 1, 1) + '.'
       + substring(NAME, charindex(' ', NAME, charindex(' ', NAME) + 1) + 1, 1) + '.'
from STUDENT
select * from @TempTable

--����� ���������, � ������� ���� ���-����� � ��������� ������, � ����������� �� ��������;
select NAME, BDAY, datediff(year, BDAY, getdate()) AS �������
from STUDENT where month(BDAY) = month(dateadd(month, 1, getdate()));

--����� ��� ������, � ������� �������� ��������� ������ ������� ������� �� ��.
select *
from (select *,
(CASE
when datepart(weekday, PDATE) = 1 then '�����������'
when datepart(weekday, PDATE) = 2 then '�������'
when datepart(weekday, PDATE) = 3 then '�����'
when datepart(weekday, PDATE) = 4 then '�������'
when datepart(weekday, PDATE) = 5 then '�������'
when datepart(weekday, PDATE) = 6 then '�������'
when datepart(weekday, PDATE) = 7 then '�����������'
end) ����_������
from PROGRESS
where SUBJECT like '%����%') as tr;

--5. ������������������ ����������� IF� ELSE
declare @numberOfGroups int = 20;
declare @kolvoGroups int = (select count(*) from GROUPS)

if (select count(*) from GROUPS) > @numberOfGroups
begin
print '���������� ����� ������ '+ cast(@numberOfGroups as varchar);
print '���������� '+ cast(@kolvoGroups as varchar);
end
else
begin
print '���������� ����� ������ ' + cast(@numberOfGroups as varchar);
print '���������� '+ cast(@kolvoGroups as varchar);
end

--6. ����������� ��������, � ������� � ������� CASE ������������� ����-��, ���������� ���������� ��������-�� ���������� ��� ����� ���������
select IDSTUDENT,
avg(NOTE) as ����,
case
when avg (PROGRESS.NOTE) = 4 then '������'
when avg (PROGRESS.NOTE) between 5 and 6 then '���� �����'
when avg (PROGRESS.NOTE) between 7 and 8 then '���������'
when avg (PROGRESS.NOTE) between 9 and 10 then '��������'
else '�� ����������'
end [������ �������� �����]
from PROGRESS
group by IDSTUDENT

--7. ������� ��������� ��������� �����-�� �� ���� �������� � 10 �����, ��������� �� � ������� ����������. ��-���������� �������� WHILE.
declare @Fam varchar(100)
declare @TempTable2 table
(
	ID int identity(1,1),
    LastName varchar(100),
	Birth varchar(100)
)
declare @iter int = 1;
while @iter <= 10
begin
insert into @TempTable2 (LastName, Birth)
select top 1 NAME, BDAY
from STUDENT
order by newid();
set @iter = @iter + 1;
end
select * from @TempTable2

--8. ����������� ������, ��������������� ������������� ��������� RETURN. 
DECLARE @note int = 8;
print @note+1
print @note+2
RETURN 
print @note+3

--9. ����������� �������� � ��������, � ������� ������������ ��� ��������� ������ ����� TRY � CATCH. 
begin try
select 1 / 0
end try 
begin catch
print 'Error Number: ' + cast(error_number() as varchar(10))
print 'Error Message: ' + error_message()
print 'Error Line: ' + cast(error_line() as varchar(10))
print 'Error Procedure: ' + isnull(error_procedure(), 'N/A')
print 'Error Severity: ' + cast(error_severity() as varchar(10))
print 'Error State: ' + cast(error_state() as varchar(10))
end catch