USE UNIVER

--����������� ��������, ��������-��� ������ ��������� �� ������� ����.
--� ����� ������ ���� ������-�� ������� �������� ��������� �� ������� SUBJECT 
--� ���� ������ ��-��� �������. 
--������������ ���������� ����-��� RTRIM.
declare @subj char(100), @subjT char(300) = '';
declare subjCursor cursor for select SUBJECT_NAME from SUBJECT where PULPIT = '����';
open subjCursor 
fetch subjCursor into @subj
print '������ �� �����: '
while @@fetch_status = 0
begin
set @subjT = rtrim(@subj) + ',' + @subjT
fetch subjCursor into @subj
end
close subjCursor
print @subjT

