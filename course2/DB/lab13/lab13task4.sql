/*
Разработать процедуру с именем PAUDITORI-UM_INSERT. 
Процедура принимает четыре вход-ных параметра: @a, @n, @c и @t.
Параметр @a имеет тип CHAR(20), параметр @n имеет тип VAR-CHAR(50), параметр @c имеет тип INT и значение по умолчанию 0, параметр @t имеет тип CHAR(10).
Процедура добавляет строку в таблицу AUDI-TORIUM. 
Значения столбцов AUDITORIUM, AU-DITORIUM_NAME, AUDITORIUM_CAPACITY и AUDITORIUM_TYPE добавляемой строки задают-ся соответственно параметрами @a, @n, @c и @t.
Процедура PAUDITORIUM_INSERT должна применять механизм TRY/CATCH для обработки ошибок. 
В случае возникновения ошибки, процеду-ра должна формировать сообщение, содержащее код ошибки, уровень серьезности и текст сообщения в стандартный выходной поток. 
Процедура должна возвращать к точке вызова значение -1 в том случае, если произошла ошибка и 1, если выполнение успешно. 
Опробовать работу процедуры с различными значениями исходных данных.

*/

use UNIVER
go

drop Procedure if exists PAUDITORIUM_INSERT;
go

CREATE PROCEDURE PAUDITORIUM_INSERT @a NVARCHAR(20), @n NVARCHAR(50), @c INT = 0, @t NVARCHAR (10)
AS
BEGIN TRY
	INSERT INTO AUDITORIUM VALUES (@a, @n, @c, @t);
	RETURN 1;
END TRY
BEGIN CATCH
	PRINT error_message();
	PRINT error_procedure();
	PRINT error_state();
    RETURN -1;
END CATCH
GO

declare @result int;
exec @result = PAUDITORIUM_INSERT '7716-2', 'ЛК', 200, '776-2';
select @result;