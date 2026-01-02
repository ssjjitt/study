/*4. Создать AFTER-триггер с именем TR_TEACHER для таблицы TEACHER, реагирующий на события INSERT, DE-LETE, UPDATE. 
Триггер должен записывать строку данных в таблицу TR_AUDIT для каждой изменяе-мой строки. 
В коде триггера определить со-бытие, активизировавшее триггер и поме-стить в столбец СС соответствующую собы-тию информацию. 
Разработать сценарий, демонстрирующий работоспособность триггера. 
*/

use UNIVER;

drop trigger if exists  dbo.TR_TEACHER
go


create trigger TR_TEACHER   on TEACHER after INSERT, DELETE, UPDATE
 as declare @a1 char(10), @a2 varchar(100), @a3 char(1), @a4 char(20), @in varchar(300);
	  declare @ins int = (select count(*) from inserted),
              @del int = (select count(*) from deleted);
   if  @ins > 0 and  @del = 0
   begin
   print 'Событие: INSERT';
      set @a1 = (select TEACHER from INSERTED);
      set @a2= (select TEACHER_NAME from INSERTED);
      set @a3= (select GENDER from INSERTED);
	  set @a4 = (select PULPIT from INSERTED);
      set @in = @a1+' '+ @a2 +' '+ @a3+ ' ' +@a4;
      insert into TR_AUDIT(STMT, TRNAME, CC)
                            values('INS', 'TR_TEACHER_INS', @in);
	 end;
	else
    if @ins = 0 and  @del > 0
	begin
	print 'Событие: DELETE';
      set @a1 = (select TEACHER from DELETED);
      set @a2= (select TEACHER_NAME from DELETED);
      set @a3= (select GENDER from DELETED);
	  set @a4 = (select PULPIT from DELETED);
      set @in = @a1+' '+ @a2 +' '+ @a3+ ' ' +@a4;
      insert into TR_AUDIT(STMT, TRNAME, CC)
                            values('DEL', 'TR_TEACHER_DEL', @in);
	  end;
	else
    if @ins > 0 and  @del > 0
	begin
	print 'Событие: UPDATE';
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
      insert into TR_AUDIT(STMT, TRNAME, CC)
                            values('UPD', 'TR_TEACHER_UPD', @in);
	  end;
	  return
    go

	
	  select * from TR_AUDIT
      insert into  TEACHER values('ив12в', 'Иванов', 'м', 'ИСиТ');
      update TEACHER set GENDER = 'ж' where TEACHER='кп'
	  delete TEACHER where TEACHER='ивв'


	  select * from TR_AUDIT

drop trigger if exists  dbo.TR_TEACHER;
go