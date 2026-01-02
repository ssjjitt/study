/* 1. С помощью сценария, представленного на рисунке, создать таблицу TR_AUDIT.
Таблица предназначена для добавления в нее строк триггерами.
В столбец STMT триггер должен поместить событие, на которое он среагировал, а в стол-бец TRNAME  собственное имя.
Разработать AFTER-триггер с именем TR_TEACHER_INS для таблицы TEACHER, реагирующий на событие INSERT. 
Триггер должен записывать строки вводимых данных в таблицу TR_AUDIT. В столбец СС помеща-ются значения столбцов вводимой строки. */

use UNIVER;
go

drop table if exists  TR_AUDIT

create table TR_AUDIT
(
ID int identity,
STMT varchar(20)
check (STMT in ('INS', 'DEL', 'UPD')),
TRNAME varchar(50),
CC varchar(300)
)
	go

drop trigger if exists dbo.TR_TEACHER_INS
go

    create  trigger TR_TEACHER_INS
      on TEACHER after INSERT
      as
      declare @a1 char(10), @a2 varchar(100), @a3 char(1), @a4 char(20), @in varchar(300);
      print 'Вставка';
      set @a1 = (select TEACHER from INSERTED);
      set @a2= (select TEACHER_NAME from INSERTED);
      set @a3= (select GENDER from INSERTED);
	  set @a4 = (select PULPIT from INSERTED);
      set @in = @a1+' '+ @a2 +' '+ @a3+ ' ' +@a4;
      insert into TR_AUDIT(STMT, TRNAME, CC)
                            values('INS', 'TR_TEACHER_INS', @in);
      return
	  go
     

	  insert into  TEACHER values(1, 'Иванов', 'м', 'ИСиТ');
	  select distinct * from TR_AUDIT
	  
drop trigger if exists dbo.TR_TEACHER_INS;