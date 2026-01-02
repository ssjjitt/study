/*6. Создать для таблицы TEACHER три AF-TER-триггера с именами: TR_TEACHER_ DEL1, TR_TEACHER_DEL2 и TR_TEA-CHER_ DEL3. 
Триггеры должны реагировать на событие DELETE и формировать соответ-ствующие строки в таблицу TR_AUDIT.  
По-лучить список триггеров таблицы TEACHER.
Упорядочить выполнение триггеров для таб-лицы TEACHER, реагирующих на событие DELETE следующим образом: 
первым должен выполняться триггер с именем TR_TEA-CHER_DEL3, 
последним – триггер TR_TEACHER_DEL2.
Примечание: 
использовать системные пред-ставления SYS.TRIGGERS и SYS.TRIG-GERS_ EVENTS, а также системную процеду-ру SP_SETTRIGGERORDERS. */


use UNIVER
go



drop trigger if exists  dbo.TR_TEACHER_DEL1 
go
drop trigger if exists  dbo.TR_TEACHER_DEL2 
go
drop trigger if exists  dbo.TR_TEACHER_DEL3
go

create trigger TR_TEACHER_DEL1 on TEACHER after DELETE
as print 'AUD_AFTER_UPDATE1';
 return;
go
create trigger TR_TEACHER_DEL2 on TEACHER after DELETE
as print 'AUD_AFTER_UPDATE2';
 return;
go
create trigger TR_TEACHER_DEL3 on TEACHER after DELETE
as print 'AUD_AFTER_UPDATE3';
 return;
go

select t.name, e.type_desc
  from sys.triggers  t join  sys.trigger_events e  on t.object_id = e.object_id
  where OBJECT_NAME(t.parent_id)='TEACHER' and e.type_desc = 'DELETE' ;

exec  SP_SETTRIGGERORDER @triggername = 'TR_TEACHER_DEL3',
	                        @order='First', @stmttype = 'DELETE';
exec  SP_SETTRIGGERORDER @triggername = 'TR_TEACHER_DEL2',
	                        @order='Last', @stmttype = 'DELETE';



  delete TEACHER where TEACHER='кп'
	  select * from TR_AUDIT

 drop trigger if exists  dbo.TR_TEACHER_DEL1
	go
drop trigger if exists  dbo.TR_TEACHER_DEL2
go
drop trigger if exists  dbo.TR_TEACHER_DEL3
go