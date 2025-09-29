/*
2. ������� AFTER-������� � ������ TR_TEACHER_DEL ��� ������� TEA-CHER, ����������� �� ������� DELETE. 
������� ������ ���������� ������ ������ � ������� TR_AUDIT ��� ������ ��������� ������. 
� ������� �� ���������� �������� ������� TEACHER ��������� ������. */

use UNIVER

drop TRIGGER if exists dbo.TR_TEACHER_DEL;
go

    create  trigger TR_TEACHER_DEL
      on TEACHER after DELETE
      as
      declare @a1 char(10), @a2 varchar(100), @a3 char(1), @a4 char(20), @in varchar(300);
      print '��������';
      set @a1 = (select TEACHER from DELETED);
      set @a2= (select TEACHER_NAME from DELETED);
      set @a3= (select GENDER from DELETED);
	  set @a4 = (select PULPIT from DELETED);
      set @in = @a1+' '+ @a2 +' '+ @a3+ ' ' +@a4;
      insert into TR_AUDIT(STMT, TRNAME, CC)
                            values('DEL', 'TR_TEACHER_DEL', @in);
      return
      go

	  delete TEACHER where TEACHER='��2123'
	  select * from TR_AUDIT

drop TRIGGER if exists dbo.TR_TEACHER_DEL;
go