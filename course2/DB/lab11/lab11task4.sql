USE UNIVER;
-- Создание курсора с атрибутом SCROLL и использованием всех ключевых слов в операторе FETCH
DECLARE @name VARCHAR(50);
DECLARE scrollCursor CURSOR SCROLL FOR
SELECT NAME FROM STUDENT;
OPEN scrollCursor;
-- Перемещение курсора к первой записи
FETCH FIRST FROM scrollCursor INTO @name;
PRINT 'FIRST: ' + @name;
-- Перемещение курсора к последней записи
FETCH LAST FROM scrollCursor INTO @name;
PRINT 'LAST: ' + @name;
-- Перемещение курсора к следующей записи
FETCH NEXT FROM scrollCursor INTO @name;
PRINT 'NEXT: ' + @name;
-- Перемещение курсора к предыдущей записи
FETCH PRIOR FROM scrollCursor INTO @name;
PRINT 'PRIOR: ' + @name;
-- Перемещение курсора на указанное количество записей вперед
FETCH ABSOLUTE 2 FROM scrollCursor INTO @name;
PRINT 'ABSOLUTE 2: ' + @name;
-- Перемещение курсора на указанное количество записей назад
FETCH RELATIVE -1 FROM scrollCursor INTO @name;
PRINT 'RELATIVE -1: ' + @name;
CLOSE scrollCursor;
DEALLOCATE scrollCursor;