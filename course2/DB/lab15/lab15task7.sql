/*7. Разработать сценарий, демонстрирующий на примере базы данных X_UNIVER утвер-ждение: 
AFTER-триггер является частью тран-закции, в рамках которого выполняется опера-тор, активизировавший триггер.*/


use UNIVER
go

drop trigger if exists  dbo.PTran
go
create trigger PTran
on PULPIT after INSERT, DELETE, UPDATE
as
declare @c int = (select count (*) from PULPIT);
if (@c >22)
begin
raiserror('Общая количество кафедр не может быть >22', 10, 1);
rollback;
end;
return;
go
-- тут тріггера тіпа больше нет
insert into PULPIT(PULPIT) values ('Т1ТПЛ')

drop trigger if exists  dbo.PTran
go