/*
����������� ��������� � ������ PAUDITORIUM_INSERTX. 
��������� ��������� ���� ������� ����������: @a, @n, @c, @t � @tn.
��������� @a, @n, @c, @t ���������� �������-��� ��������� AUDITORIUM_INSERT. 
�������-������� �������� @tn �������� �������, ����� ��� VARCHAR(50), ������������ ��� ����� �������� � ������� AUDITORIUM_TYPE.AUDITORIUM_TYPENAME.
��������� ��������� ��� ������. 
������ ������ ����������� � ������� AUDITORIUM_TYPE. �����-��� �������� AUDITORIUM_TYPE � AUDITORIUM_TYPENAME ����������� ������ �������� ��-������������ ����������� @t � @tn. 
������ ������ ����������� ����� ������ ��������� PAUDITORIUM_INSERT.
���������� ������ � ������� AUDITORI-UM_TYPE � ����� ��������� PAUDITORI-UM_INSERT ������ ����������� � ������ ����� ����� ���������� � ������� ��������������� SERI-ALIZABLE.
� ��������� ������ ���� ������������� ��������� ������ � ������� ��������� TRY/CATCH. ��� ������ ������ ���� ���������� � ������� �������-��������� ��������� � ����������� �������� �����.
��������� PAUDITORIUM_INSERTX ������ ���������� � ����� ������ �������� -1 � ��� ������, ���� ��������� ������ � 1, ���� ���������� �����-���� ����������� �������.
*/

drop procedure if exists PAUDITORIUM_INSERTX;
go

CREATE procedure PAUDITORIUM_INSERTX
		@a char(20),
		@n varchar(50),
		@c int = 0,
		@t char(10),
		@tn varchar(50)
as begin
DECLARE @rc int = 1;
begin try
	set transaction isolation level serializable;
	begin tran
	INSERT into AUDITORIUM_TYPE(AUDITORIUM_TYPE, AUDITORIUM_TYPENAME)
				values(@n, @tn);
	EXEC @rc = PAUDITORIUM_INSERT @a, @n, @c, @t;
	commit tran;
	return @rc;
end try
begin catch
	print '����� ������: ' + cast(error_number() as varchar(6));
	print '���������: ' + error_message();
	print '�������: ' + cast(error_severity() as varchar(6));
	print '�����: ' + cast(error_state() as varchar(8));
	print '����� ������: ' + cast(error_line() as varchar(8));
	if error_procedure() is not  null
	print '��� ���������: ' + error_procedure();
	if @@trancount > 0 rollback tran ;
	return -1;
end catch;
end;
    go

declare @result int;
 exec @result  =  PAUDITORIUM_INSERTX '771-2', '��-�', 200, '776-2' , '������������� �����������';
select * from AUDITORIUM;
    select * from AUDITORIUM_TYPE;


