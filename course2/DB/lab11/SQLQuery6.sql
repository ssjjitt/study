--����������� SELECT-������, � ��-����� �������� �� ������� PRO-GRESS ��������� ������, �������-��� ���������� � ���������, ����-������ ������ ���� 4 (������������ ����������� ������ PROGRESS, STUDENT, GROUPS). 
DECLARE @studentId INT;
DECLARE cursorStudents CURSOR FOR
SELECT p.IDSTUDENT
FROM PROGRESS p
INNER JOIN STUDENT s ON p.IDSTUDENT = s.IDSTUDENT
INNER JOIN GROUPS g ON s.IDGROUP = g.IDGROUP
WHERE p.NOTE < 4;
OPEN cursorStudents;
FETCH NEXT FROM cursorStudents INTO @studentId;
WHILE @@FETCH_STATUS = 0
BEGIN
DELETE FROM PROGRESS WHERE IDSTUDENT = @studentId;
FETCH NEXT FROM cursorStudents INTO @studentId;
END;
CLOSE cursorStudents;
DEALLOCATE cursorStudents;

--����������� SELECT-������, � ��-����� �������� � ������� PRO-GRESS ��� �������� � ���������� ������� IDSTUDENT ������������-�� ������ (������������� �� �����-��).
DECLARE @studId int
DECLARE cursorStudent CURSOR FOR
SELECT IDSTUDENT FROM PROGRESS WHERE IDSTUDENT = 1002;
OPEN cursorStudent;
FETCH NEXT FROM cursorStudent INTO @studId;
WHILE @@FETCH_STATUS = 0
BEGIN
UPDATE PROGRESS SET NOTE = NOTE + 1 WHERE IDSTUDENT = @studId;
FETCH NEXT FROM cursorStudent INTO @studId;
END;
CLOSE cursorStudent;
DEALLOCATE cursorStudent;