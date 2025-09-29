USE UNIVER
-- Обновление данных в таблице "Students"
UPDATE STUDENT SET Name = 'Рошен Мария Ивановна' WHERE IDSTUDENT = 1000;
-- Создание статического курсора
DECLARE @name VARCHAR(50);
DECLARE staticCursor CURSOR STATIC FOR
SELECT top 5 NAME FROM STUDENT;
OPEN staticCursor;
-- Обновление данных в таблице "Students"
UPDATE STUDENT SET Name = 'Ну Мария Ивановна' WHERE IDSTUDENT = 1000;
FETCH NEXT FROM staticCursor INTO @name;
WHILE @@FETCH_STATUS = 0
BEGIN
PRINT @name;
FETCH NEXT FROM staticCursor INTO @name;
END;
CLOSE staticCursor;
DEALLOCATE staticCursor;

PRINT '---------------------------------------------'

-- Создание динамического курсора
DECLARE @nameDin VARCHAR(50);
DECLARE dynamicCursor CURSOR DYNAMIC FOR
SELECT top 5 NAME FROM STUDENT;
OPEN dynamicCursor;
-- Обновление данных в таблице "Students"
UPDATE STUDENT SET Name = 'Нену Мария Ивановна' WHERE IDSTUDENT = 1000;
FETCH NEXT FROM dynamicCursor INTO @nameDin;
WHILE @@FETCH_STATUS = 0
BEGIN
PRINT @nameDin;
FETCH NEXT FROM dynamicCursor INTO @nameDin;
END;
CLOSE dynamicCursor;
DEALLOCATE dynamicCursor;

