/*
Разработать процедуру с именем PAUDITORIUM_INSERTX. 
Процедура принимает пять входных параметров: @a, @n, @c, @t и @tn.
Параметры @a, @n, @c, @t аналогичны парамет-рам процедуры AUDITORIUM_INSERT. 
Дополни-тельный параметр @tn является входным, имеет тип VARCHAR(50), предназначен для ввода значения в столбец AUDITORIUM_TYPE.AUDITORIUM_TYPENAME.
Процедура добавляет две строки. 
Первая строка добавляется в таблицу AUDITORIUM_TYPE. Значе-ния столбцов AUDITORIUM_TYPE и AUDITORIUM_TYPENAME добавляемой строки задаются со-ответственно параметрами @t и @tn. 
Вторая строка добавляется путем вызова процедуры PAUDITORIUM_INSERT.
Добавление строки в таблицу AUDITORI-UM_TYPE и вызов процедуры PAUDITORI-UM_INSERT должны выполняться в рамках одной явной транзакции с уровнем изолированности SERI-ALIZABLE.
В процедуре должна быть предусмотрена обработка ошибок с помощью механизма TRY/CATCH. Все ошибки должны быть обработаны с выдачей соответ-ствующего сообщения в стандартный выходной поток.
Процедура PAUDITORIUM_INSERTX должна возвращать к точке вызова значение -1 в том случае, если произошла ошибка и 1, если выполнения проце-дуры завершилось успешно.
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
	print 'Номер ошибки: ' + cast(error_number() as varchar(6));
	print 'Сообщение: ' + error_message();
	print 'Уровень: ' + cast(error_severity() as varchar(6));
	print 'Метка: ' + cast(error_state() as varchar(8));
	print 'Номер строки: ' + cast(error_line() as varchar(8));
	if error_procedure() is not  null
	print 'Имя процедуры: ' + error_procedure();
	if @@trancount > 0 rollback tran ;
	return -1;
end catch;
end;
    go

declare @result int;
 exec @result  =  PAUDITORIUM_INSERTX '771-2', 'ЛК-с', 200, '776-2' , 'Биологическая лаборатория';
select * from AUDITORIUM;
    select * from AUDITORIUM_TYPE;


