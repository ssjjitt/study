/*
2. Создать AFTER-триггер с именем TR_TEACHER_DEL для таблицы TEA-CHER, реагирующий на событие DELETE. 
Триггер должен записывать строку данных в таблицу TR_AUDIT для каждой удаляемой строки. 
В столбец СС помещаются значения столбца TEACHER удаляемой строки. */

use UNIVER

drop TRIGGER if exists dbo.TR_TEACHER_DEL;
go

    create  trigger TR_TEACHER_DEL
      on TEACHER after DELETE
      as
      declare @a1 char(10), @a2 varchar(100), @a3 char(1), @a4 char(20), @in varchar(300);
      print 'Удаление';
      set @a1 = (select TEACHER from DELETED);
      set @a2= (select TEACHER_NAME from DELETED);
      set @a3= (select GENDER from DELETED);
	  set @a4 = (select PULPIT from DELETED);
      set @in = @a1+' '+ @a2 +' '+ @a3+ ' ' +@a4;
      insert into TR_AUDIT(STMT, TRNAME, CC)
                            values('DEL', 'TR_TEACHER_DEL', @in);
      return
      go

	  delete TEACHER where TEACHER='ив2123'
	  select * from TR_AUDIT

drop TRIGGER if exists dbo.TR_TEACHER_DEL;
go