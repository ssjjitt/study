use UNIVER

--����������� ��������� ������� � ������ COUNT_STUDENTS, ������� ��������� ���������� ��������� �� ����������, ��� �������� �������� �������-��� ���� varchar(20) � ������ @faculty. 
--������������ ���������� ���������� ������ FACULTY, GROUPS, STUDENT. ���������� ������ �������.

go

create function COUNT_STUDENTS(@faculty nvarchar(20)) returns int 
as begin declare @rc int = 0;
set @rc = (select count(*) from STUDENT as stud 
join GROUPS as gr on stud.IDGROUP = gr.IDGROUP 
join FACULTY as fac on gr.FACULTY = fac.FACULTY 
where fac.FACULTY = @faculty);
return @rc;
end;

go

drop function COUNT_STUDENTS;

go

declare @fun int = dbo.COUNT_STUDENTS('���');
print '���������� ���������: ' + cast(@fun as varchar(4));

go 

--������ ��������� � ����� ������� � ������� �������-�� ALTER � ���, ����� ������� ��������� ������ ����-���� @prof ���� varchar(20), 
--������������ ��������-����� ���������. ��� ���������� ���������� �������� �� ��������� NULL. ���������� ������ ������� � ����-��� SELECT-��������.

alter function COUNT_STUDENTS(
@faculty nvarchar(20),
@prof nvarchar(60)
) returns int
as 
begin
declare @rc int = 0
set @rc = (
select count(*) from STUDENT as stud 
join GROUPS as gr on stud.IDGROUP = gr.IDGROUP 
join FACULTY as fac on gr.FACULTY = fac.FACULTY 
join PROFESSION as prof on prof.PROFESSION = gr.PROFESSION
where fac.FACULTY = @faculty and (prof.PROFESSION_NAME =@prof));
return @rc;
end;

declare @fun2 int = dbo.COUNT_STUDENTS('���', '���������� ���������� ����������� ���������');
print '���������� ���������: ' + cast(@fun2 as varchar(4));
