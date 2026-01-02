/*3. Создать AFTER-триггер с именем TR_TEACHER_UPD для таблицы TEA-CHER, реагирующий на событие UPDATE. 
Триггер должен записывать строку данных в таблицу TR_AUDIT для каждой изменяемой строки. 
В столбец СС помещаются значения столбцов изменяемой строки до и после изме-нения.
*/


use UNIVER;

drop trigger if exists  dbo.TR_TEACHER_UPD 
go

create trigger TR_TEACHER_UPD on TEACHER after UPDATE
as declare @a1 char(10), @a2 varchar(100), @a3 char(1), @a4 char(20), @in varchar(300);
print 'update';
set @a1 = (select TEACHER from INSERTED);
set @a2= (select TEACHER_NAME from INSERTED);
set @a3= (select GENDER from INSERTED);
set @a4 = (select PULPIT from INSERTED);
set @in = @a1+' '+ @a2 +' '+ @a3+ ' ' +@a4;

set @a1 = (select TEACHER from deleted);
set @a2= (select TEACHER_NAME from DELETED);
set @a3= (select GENDER from DELETED);
set @a4 = (select PULPIT from DELETED);
set @in =@in + '' + @a1+' '+ @a2 +' '+ @a3+ ' ' +@a4;
insert into TR_AUDIT(STMT, TRNAME, CC) values('UPD', 'TR_TEACHER_UPD', @in);
return;
go

insert into TEACHER values('РР1РРРР', 'ЗЗЗ', 'м', 'ТЛ');
select * from TR_AUDIT
update TEACHER set TEACHER_NAME = 'ШШШШ' where TEACHER = 'РР1РРРР'





drop trigger if exists  dbo.TR_TEACHER_UPD;
go