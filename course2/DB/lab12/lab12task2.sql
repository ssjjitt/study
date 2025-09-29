--Разработать сценарий, демон-стрирующий свойство ато-марности явной транзакции 
--на примере базы данных UNI-VER. 
--В блоке CATCH преду-смотреть выдачу соответству-ющих сообщений об ошибках. 
--Опробовать работу сцена-рия при использовании раз-личных операторов модифи-кации таблиц.
USE UNIVER

begin try
begin tran
delete STUDENT WHERE IDSTUDENT = 1012
insert STUDENT values(2, 'Дублирование Ксения Павловна','22.11.1993')
insert STUDENT values(2, 'неизвестная НЕКсения Павловна','22.11.1993')
commit tran
end try
begin catch
print 'error' + case
when error_number() = 2627 and patindex('%PK_STUDENT%', error_message()) > 0
then 'дублирование человека'
else 'неизвестная ошибка' + cast(error_number() as varchar(5)) + error_message()
end
if @@trancount > 0 rollback tran
end catch
