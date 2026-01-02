-- Создание курсора и выбор сотрудника
DECLARE @id char(40);
DECLARE curs CURSOR FOR
SELECT NAME FROM STUDENT;
OPEN curs;
FETCH NEXT FROM curs INTO @id;
-- Обновление данных с использованием конструкции CURRENT OF
UPDATE STUDENT SET NAME = 'НеРошен Нина Леонидовна' WHERE CURRENT OF curs;
-- Удаление записи с использованием конструкции CURRENT OF
CLOSE curs;
DEALLOCATE curs;