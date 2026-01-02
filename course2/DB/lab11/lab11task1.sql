USE UNIVER

--Разработать сценарий, формирую-щий список дисциплин на кафедре ИСиТ.
--В отчет должны быть выведе-ны краткие названия дисциплин из таблицы SUBJECT 
--в одну строку че-рез запятую. 
--Использовать встроенную функ-цию RTRIM.
declare @subj char(100), @subjT char(300) = '';
declare subjCursor cursor for select SUBJECT_NAME from SUBJECT where PULPIT = 'ИСиТ';
open subjCursor 
fetch subjCursor into @subj
print 'список на ИСИТЕ: '
while @@fetch_status = 0
begin
set @subjT = rtrim(@subj) + ',' + @subjT
fetch subjCursor into @subj
end
close subjCursor
print @subjT

