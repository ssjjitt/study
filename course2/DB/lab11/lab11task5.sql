-- �������� ������� � ����� ����������
DECLARE @id char(40);
DECLARE curs CURSOR FOR
SELECT NAME FROM STUDENT;
OPEN curs;
FETCH NEXT FROM curs INTO @id;
-- ���������� ������ � �������������� ����������� CURRENT OF
UPDATE STUDENT SET NAME = '������� ���� ����������' WHERE CURRENT OF curs;
-- �������� ������ � �������������� ����������� CURRENT OF
CLOSE curs;
DEALLOCATE curs;