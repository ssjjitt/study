USE UNIVER
-- ���������� ������ � ������� "Students"
UPDATE STUDENT SET Name = '����� ����� ��������' WHERE IDSTUDENT = 1000;
-- �������� ������������ �������
DECLARE @name VARCHAR(50);
DECLARE staticCursor CURSOR STATIC FOR
SELECT top 5 NAME FROM STUDENT;
OPEN staticCursor;
-- ���������� ������ � ������� "Students"
UPDATE STUDENT SET Name = '�� ����� ��������' WHERE IDSTUDENT = 1000;
FETCH NEXT FROM staticCursor INTO @name;
WHILE @@FETCH_STATUS = 0
BEGIN
PRINT @name;
FETCH NEXT FROM staticCursor INTO @name;
END;
CLOSE staticCursor;
DEALLOCATE staticCursor;

PRINT '---------------------------------------------'

-- �������� ������������� �������
DECLARE @nameDin VARCHAR(50);
DECLARE dynamicCursor CURSOR DYNAMIC FOR
SELECT top 5 NAME FROM STUDENT;
OPEN dynamicCursor;
-- ���������� ������ � ������� "Students"
UPDATE STUDENT SET Name = '���� ����� ��������' WHERE IDSTUDENT = 1000;
FETCH NEXT FROM dynamicCursor INTO @nameDin;
WHILE @@FETCH_STATUS = 0
BEGIN
PRINT @nameDin;
FETCH NEXT FROM dynamicCursor INTO @nameDin;
END;
CLOSE dynamicCursor;
DEALLOCATE dynamicCursor;

