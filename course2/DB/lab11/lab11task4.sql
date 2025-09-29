USE UNIVER;
-- �������� ������� � ��������� SCROLL � �������������� ���� �������� ���� � ��������� FETCH
DECLARE @name VARCHAR(50);
DECLARE scrollCursor CURSOR SCROLL FOR
SELECT NAME FROM STUDENT;
OPEN scrollCursor;
-- ����������� ������� � ������ ������
FETCH FIRST FROM scrollCursor INTO @name;
PRINT 'FIRST: ' + @name;
-- ����������� ������� � ��������� ������
FETCH LAST FROM scrollCursor INTO @name;
PRINT 'LAST: ' + @name;
-- ����������� ������� � ��������� ������
FETCH NEXT FROM scrollCursor INTO @name;
PRINT 'NEXT: ' + @name;
-- ����������� ������� � ���������� ������
FETCH PRIOR FROM scrollCursor INTO @name;
PRINT 'PRIOR: ' + @name;
-- ����������� ������� �� ��������� ���������� ������� ������
FETCH ABSOLUTE 2 FROM scrollCursor INTO @name;
PRINT 'ABSOLUTE 2: ' + @name;
-- ����������� ������� �� ��������� ���������� ������� �����
FETCH RELATIVE -1 FROM scrollCursor INTO @name;
PRINT 'RELATIVE -1: ' + @name;
CLOSE scrollCursor;
DEALLOCATE scrollCursor;