/*
����������� ��������� � ������ PAUDITORI-UM_INSERT. 
��������� ��������� ������ ����-��� ���������: @a, @n, @c � @t.
�������� @a ����� ��� CHAR(20), �������� @n ����� ��� VAR-CHAR(50), �������� @c ����� ��� INT � �������� �� ��������� 0, �������� @t ����� ��� CHAR(10).
��������� ��������� ������ � ������� AUDI-TORIUM. 
�������� �������� AUDITORIUM, AU-DITORIUM_NAME, AUDITORIUM_CAPACITY � AUDITORIUM_TYPE ����������� ������ ������-�� �������������� ����������� @a, @n, @c � @t.
��������� PAUDITORIUM_INSERT ������ ��������� �������� TRY/CATCH ��� ��������� ������. 
� ������ ������������� ������, �������-�� ������ ����������� ���������, ���������� ��� ������, ������� ����������� � ����� ��������� � ����������� �������� �����. 
��������� ������ ���������� � ����� ������ �������� -1 � ��� ������, ���� ��������� ������ � 1, ���� ���������� �������. 
���������� ������ ��������� � ���������� ���������� �������� ������.

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
exec @result = PAUDITORIUM_INSERT '7716-2', '��', 200, '776-2';
select @result;