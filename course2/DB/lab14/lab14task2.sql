use UNIVER

--����������� ��������� ������� � ������ FSUBJECTS, ����������� �������� @p ���� varchar(20), 
--�������� �������� ������ ��� ������� (������� SUBJECT.PULPIT). 
--������� ������ ���������� ������ ���� varchar(300) � �������� ��������� � ������. 

go

alter function FSUBJECTS(@p nvarchar(20)) returns nvarchar(300)
as 
begin
declare @tv char(20);
declare @t varchar(300) = '�������� ���������: ';
declare curs cursor local 
for select SUBJECT from SUBJECT as subj
join PULPIT as pulp on subj.PULPIT = pulp.PULPIT
where pulp.PULPIT = @p
open curs
fetch curs into @tv
while @@FETCH_STATUS = 0
begin
set @t = @t + ' ' + rtrim(@tv)
fetch curs into @tv
end;
return @t;
end;

go

select PULPIT, dbo.FSUBJECTS(PULPIT) from PULPIT