--Разработать сценарий, демон-стрирующий применение опе-ратора SAVE TRAN на 
--при-мере базы данных UNIVER. 
--В блоке CATCH преду-смотреть выдачу соответству-ющих сообщений об ошибках. 
--Опробовать работу сцена-рия при использовании раз-личных контрольных точек и различных операторов моди-фикации таблиц.

USE UNIVER

declare @point varchar(32)
begin try
begin tran
delete SUBJECT where SUBJECT_NAME = 'Лесоводство'
set @point = 'p1' 
save tran @point
insert SUBJECT values('ТерВер', 'Теория вероятности', 'ИСиТ')
set @point = 'p2' 
save tran @point 
insert SUBJECT values('МатАнализ', 'Математический анализ', 'ИСиТ')
commit tran 
end try
begin catch
print 'error' + case
when error_number() = 2627 and patindex('%PK_STUDENT%', error_message()) > 0
then 'дублирование человека'
else 'неизвестная ошибка' + cast(error_number() as varchar(5)) + error_message()
end
if @@trancount > 0 
begin 
print 'контрольная точка: ' + @point
rollback tran @point 
end
end catch

