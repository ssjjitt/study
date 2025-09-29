/*6. ������� ��� ������� TEACHER ��� AF-TER-�������� � �������: TR_TEACHER_ DEL1, TR_TEACHER_DEL2 � TR_TEA-CHER_ DEL3. 
�������� ������ ����������� �� ������� DELETE � ����������� �������-�������� ������ � ������� TR_AUDIT.  
��-������ ������ ��������� ������� TEACHER.
����������� ���������� ��������� ��� ���-���� TEACHER, ����������� �� ������� DELETE ��������� �������: 
������ ������ ����������� ������� � ������ TR_TEA-CHER_DEL3, 
��������� � ������� TR_TEACHER_DEL2.
����������: 
������������ ��������� ����-��������� SYS.TRIGGERS � SYS.TRIG-GERS_ EVENTS, � ����� ��������� �������-�� SP_SETTRIGGERORDERS. */


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



  delete TEACHER where TEACHER='��'
	  select * from TR_AUDIT

 drop trigger if exists  dbo.TR_TEACHER_DEL1
	go
drop trigger if exists  dbo.TR_TEACHER_DEL2
go
drop trigger if exists  dbo.TR_TEACHER_DEL3
go