use univer;
-- 1
-- ��� �������� �������
-- �������� �� ���� �������� � ����: 
-- �� = �� + ��
-- �� = ���� + ������ (���������� ��� ��� �������)
CREATE TABLE PROFESSION (
    PROFESSION CHAR(20) PRIMARY KEY,
    FACULTY CHAR(10) FOREIGN KEY REFERENCES FACULTY(FACULTY),
    PROFESSION_NAME NVARCHAR(100),
    QUALIFICATION NVARCHAR(50)
);

--�������� ��������������
ALTER TABLE PROFESSION
ADD PARENT_PROFESSION CHAR(20) NULL FOREIGN KEY REFERENCES PROFESSION(PROFESSION);

INSERT INTO FACULTY (FACULTY, FACULTY_NAME)
VALUES ('��','�������������� ����������');

--������������
INSERT INTO PROFESSION (PROFESSION, FACULTY, PROFESSION_NAME, QUALIFICATION, PARENT_PROFESSION)
VALUES ('��', '��', '�������������� �������', '�������-�����������-�������������', NULL);

INSERT INTO PROFESSION (PROFESSION, FACULTY, PROFESSION_NAME, QUALIFICATION, PARENT_PROFESSION)
VALUES ('��', '��', '����������� ���������', ' �������-�����������', NULL);

--��������
INSERT INTO PROFESSION (PROFESSION, FACULTY, PROFESSION_NAME, QUALIFICATION, PARENT_PROFESSION)
VALUES ('��', '��', '�������� ������', '�������-�����������', '��');

INSERT INTO PROFESSION (PROFESSION, FACULTY, PROFESSION_NAME, QUALIFICATION, PARENT_PROFESSION)
VALUES ('����', '��', '����������� ����������� �������������� ����������', '�������-�����������', '��');

INSERT INTO PROFESSION (PROFESSION, FACULTY, PROFESSION_NAME, QUALIFICATION, PARENT_PROFESSION)
VALUES ('������', '��', '����������� ����������� � ������������ ��������� ������', '�������-�����������', '��');

--2
--��� ����������� ���� � ��������� ������ ��������(�������� - �������� ����)

CREATE OR ALTER PROCEDURE GetSubProfessions
    @Profession CHAR(20)
AS
BEGIN
    WITH ProfessionHierarchy AS (
        SELECT PROFESSION, PROFESSION_NAME, PARENT_PROFESSION, 0 AS Level
        FROM PROFESSION
        WHERE PROFESSION = @Profession
        UNION ALL
        SELECT p.PROFESSION, p.PROFESSION_NAME, p.PARENT_PROFESSION, Level + 1
        FROM PROFESSION p
        INNER JOIN ProfessionHierarchy ph ON p.PARENT_PROFESSION = ph.PROFESSION
    )
    SELECT PROFESSION, PROFESSION_NAME, Level
    FROM ProfessionHierarchy;
END;

--��������
EXEC GetSubProfessions '��';

--3
--���������� ������������ ����
CREATE OR ALTER PROCEDURE AddSubProfession
    @Profession CHAR(20),
    @Faculty CHAR(10),
    @ProfessionName NVARCHAR(100),
    @Qualification NVARCHAR(50),
    @ParentProfession CHAR(20)
AS
BEGIN
    INSERT INTO PROFESSION (PROFESSION, FACULTY, PROFESSION_NAME, QUALIFICATION, PARENT_PROFESSION)
    VALUES (@Profession, @Faculty, @ProfessionName, @Qualification, @ParentProfession);
END;

--��������
EXEC AddSubProfession '��', '��', '������ ������������ �����������', '�������-�����������', '��';

--4
--����������� �����
CREATE PROCEDURE MoveSubProfession
    @SourceProfession CHAR(20),
    @TargetProfession CHAR(20)
AS
BEGIN
    UPDATE PROFESSION
    SET PARENT_PROFESSION = @TargetProfession
    WHERE PARENT_PROFESSION = @SourceProfession OR PROFESSION = @SourceProfession;
END;

--��������
EXEC MoveSubProfession '��', '��';



-----------------------------
-- 1.	��� ���� ������ � ���� SQL Server �������� ��� ����� �� ������ ������� ������ �������������� ����. 
ALTER TABLE PROFESSION
ADD HIERARCHY_COLUMN HIERARCHYID;

--2.	������� ���������, ������� ��������� ��� ����������� ���� � ��������� ������ �������� (�������� � �������� ����).
drop procedure Show_p; 
drop procedure Add_p; 
drop procedure Replace_p; 


CREATE PROCEDURE Show_p
@Node HIERARCHYID
AS
BEGIN
    SELECT
        HIERARCHY_COLUMN.ToString() AS HierarchyPath,
        LEVEL = HIERARCHY_COLUMN.GetLevel(),
        * -- �������� ��� ��������� ������� �� ������ ����������
    FROM PROFESSION
    WHERE HIERARCHY_COLUMN.IsDescendantOf(@Node) = 1;
END;

CREATE PROCEDURE Add_p
@ParentNode HIERARCHYID,
@NewNode HIERARCHYID
AS
BEGIN
    INSERT INTO PROFESSION(PROFESSION,FACULTY,PROFESSION_NAME,QUALIFICATION,HIERARCHY_COLUMN)
    VALUES ('��', '��', '�������������� �������', '�������-�����������', @ParentNode.GetDescendant(@NewNode, NULL));
END;
go

EXEC Show_p '/';
EXEC Add_p '/', '/1/';

