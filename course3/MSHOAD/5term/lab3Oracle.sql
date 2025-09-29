CREATE TABLE FACULTY (
    FACULTY CHAR(10) PRIMARY KEY,
    FACULTY_NAME NVARCHAR2(100)
);

CREATE TABLE PROFESSION (
    PROFESSION CHAR(20) PRIMARY KEY,
    FACULTY CHAR(10) REFERENCES FACULTY(FACULTY),
    PROFESSION_NAME NVARCHAR2(100),
    QUALIFICATION NVARCHAR2(50),
    PARENT_PROFESSION CHAR(20) REFERENCES PROFESSION(PROFESSION)
);

INSERT INTO FACULTY (FACULTY, FACULTY_NAME)
VALUES ('��', '�������������� ����������');

-- ������������ ���������
INSERT INTO PROFESSION (PROFESSION, FACULTY, PROFESSION_NAME, QUALIFICATION, PARENT_PROFESSION)
VALUES ('��', '��', '�������������� �������', '�������-�����������-�������������', NULL);

INSERT INTO PROFESSION (PROFESSION, FACULTY, PROFESSION_NAME, QUALIFICATION, PARENT_PROFESSION)
VALUES ('��', '��', '����������� ���������', '�������-�����������', NULL);

-- �������� ���������
INSERT INTO PROFESSION (PROFESSION, FACULTY, PROFESSION_NAME, QUALIFICATION, PARENT_PROFESSION)
VALUES ('��', '��', '�������� ������', '�������-�����������', '��');

INSERT INTO PROFESSION (PROFESSION, FACULTY, PROFESSION_NAME, QUALIFICATION, PARENT_PROFESSION)
VALUES ('����', '��', '����������� ����������� �������������� ����������', '�������-�����������', '��');

INSERT INTO PROFESSION (PROFESSION, FACULTY, PROFESSION_NAME, QUALIFICATION, PARENT_PROFESSION)
VALUES ('������', '��', '����������� ����������� � ������������ ��������� ������', '�������-�����������', '��');

CREATE OR REPLACE PROCEDURE GetParentAndChildProfessions (
    p_profession CHAR
) AS
BEGIN
    DBMS_OUTPUT.PUT_LINE('�������� ���� ��� ��������� ' || p_profession || ':');
    FOR rec IN (
        WITH ChildHierarchy (PROFESSION, PROFESSION_NAME) AS (
            SELECT PROFESSION, PROFESSION_NAME
            FROM PROFESSION
            WHERE PARENT_PROFESSION = p_profession
            UNION ALL
            SELECT p.PROFESSION, p.PROFESSION_NAME
            FROM PROFESSION p
            JOIN ChildHierarchy ch ON p.PARENT_PROFESSION = ch.PROFESSION
        )
        SELECT PROFESSION, PROFESSION_NAME
        FROM ChildHierarchy
    ) LOOP
        DBMS_OUTPUT.PUT_LINE('�������� ���������: ' || rec.PROFESSION_NAME || ' (���: ' || rec.PROFESSION || ')');
    END LOOP;
    DBMS_OUTPUT.PUT_LINE('������������ ���� ��� ��������� ' || p_profession || ':');
    FOR rec IN (
        WITH ParentHierarchy (PROFESSION, PROFESSION_NAME) AS (
            SELECT PARENT_PROFESSION AS PROFESSION, 
                   (SELECT PROFESSION_NAME FROM PROFESSION WHERE PROFESSION = PARENT_PROFESSION) AS PROFESSION_NAME
            FROM PROFESSION
            WHERE PROFESSION = p_profession
            UNION ALL
            SELECT p.PARENT_PROFESSION AS PROFESSION, 
                   (SELECT PROFESSION_NAME FROM PROFESSION WHERE PROFESSION = p.PARENT_PROFESSION) AS PROFESSION_NAME
            FROM PROFESSION p
            JOIN ParentHierarchy ph ON p.PROFESSION = ph.PROFESSION
        )
        SELECT PROFESSION, PROFESSION_NAME
        FROM ParentHierarchy
        WHERE PROFESSION IS NOT NULL  -- ��������� ������ ��� ���������
    ) LOOP
        DBMS_OUTPUT.PUT_LINE('������������ ���������: ' || rec.PROFESSION_NAME || ' (���: ' || rec.PROFESSION || ')');
    END LOOP;
    IF SQL%ROWCOUNT = 0 THEN
        DBMS_OUTPUT.PUT_LINE('��������� �� �������: ' || p_profession);
    END IF;
END;

SET SERVEROUTPUT ON;
BEGIN
    GetParentAndChildProfessions('��'); 
END;

CREATE OR REPLACE PROCEDURE AddSubProfession (
    p_profession CHAR,
    p_faculty CHAR,
    p_profession_name NVARCHAR2,
    p_qualification NVARCHAR2,
    p_parent_profession CHAR
) AS
BEGIN
    INSERT INTO PROFESSION (PROFESSION, FACULTY, PROFESSION_NAME, QUALIFICATION, PARENT_PROFESSION)
    VALUES (p_profession, p_faculty, p_profession_name, p_qualification, p_parent_profession);
END;

CREATE OR REPLACE PROCEDURE MoveSubProfession (
    p_source_profession CHAR,
    p_target_profession CHAR
) AS
BEGIN
    UPDATE PROFESSION
    SET PARENT_PROFESSION = p_target_profession
    WHERE PARENT_PROFESSION = p_source_profession OR PROFESSION = p_source_profession;
END;

SELECT * FROM PROFESSION WHERE PROFESSION = '��';



EXEC AddSubProfession('��', '��', '������ ������������ �����������', '�������-�����������', '��');

EXEC MoveSubProfession('��', '��');