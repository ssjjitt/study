--SET SERVEROUTPUT ON;
--DELETE FROM PROFESSION;

--1
-- ��������� ������ ��� ������ ���������
CREATE OR REPLACE TYPE child_profession AS OBJECT (
    profession CHAR(20),
    profession_name NVARCHAR2(100),
    qualification NVARCHAR2(50)
);
-- ��� ��������� �� ������� ��������
-- ����� profession_obj � ����� ������
CREATE OR REPLACE TYPE child_profession_table AS TABLE OF child_profession;
-- �������� �������
CREATE TABLE PROFESSION (
    profession CHAR(20) PRIMARY KEY,
    faculty CHAR(10) REFERENCES FACULTY(FACULTY),
    profession_name NVARCHAR2(100),
    qualification NVARCHAR2(50),
    children child_profession_table
) NESTED TABLE children STORE AS child_profession_nested_table;
--
SELECT p.profession, p.profession_name, p.qualification, 
       c.profession AS child_profession, 
       c.profession_name AS child_profession_name
FROM PROFESSION p, TABLE(p.children) c;

--2
CREATE OR REPLACE PROCEDURE DisplayProfessions (
    p_profession CHAR
) AS
BEGIN
    FOR rec IN (
        SELECT p.profession, p.profession_name, p.qualification, 
               c.profession AS child_profession, 
               c.profession_name AS child_profession_name
        FROM PROFESSION p, TABLE(p.children) c
        WHERE p.profession = p_profession
    ) LOOP
        DBMS_OUTPUT.PUT_LINE('���������: ' || rec.profession_name || 
                             ' (���: ' || rec.profession || 
                             '), ������������: ' || rec.qualification);
        DBMS_OUTPUT.PUT_LINE('  �������� ���������: ' || rec.child_profession_name || 
                             ' (���: ' || rec.child_profession || ')');
    END LOOP;
END;
--
EXEC DisplaySubProfessions('��');

--3
CREATE OR REPLACE PROCEDURE AddSubProfession (
    p_profession CHAR,
    p_faculty CHAR,
    p_profession_name NVARCHAR2,
    p_qualification NVARCHAR2,
    p_parent_profession CHAR
) AS
BEGIN
    -- ������� ����� ���������
    INSERT INTO PROFESSION (profession, faculty, profession_name, qualification, children)
    VALUES (
        p_profession, 
        p_faculty, 
        p_profession_name, 
        p_qualification,
        child_profession_table()  -- ������ ������� ��� �������� ���������
    );

    -- ���������� ������������ ���������, �������� ����� � ��������� �������
    UPDATE PROFESSION
    SET children = children
    WHERE profession = p_parent_profession;

    -- ��������, ���� �� ��������� ������������ ���������
    IF SQL%ROWCOUNT = 0 THEN
        RAISE_APPLICATION_ERROR(-20001, '������������ ��������� �� �������: ' || p_parent_profession);
    END IF;
END;
--
EXEC AddSubProfession('��', '��', '�������������� �������', '�������-�����������', '��');
--4
CREATE OR REPLACE PROCEDURE MoveSubTree (
    p_source_profession CHAR,
    p_target_profession CHAR
) AS
    v_children child_profession_table;
BEGIN
    -- �������� ����� ���������
    SELECT children INTO v_children
    FROM PROFESSION
    WHERE profession = p_source_profession;

    -- ��������� ����� � ������� ����
    UPDATE PROFESSION
    SET children = children || v_children
    WHERE profession = p_target_profession;

    -- ��������, ���� �� ��������� ������� ���������
    IF SQL%ROWCOUNT = 0 THEN
        RAISE_APPLICATION_ERROR(-20002, '������� ��������� �� �������: ' || p_target_profession);
    END IF;

    -- ������� ��������
    DELETE FROM PROFESSION
    WHERE profession = p_source_profession;
END;
--
EXEC DisplaySubProfessions('��');






INSERT INTO FACULTY (FACULTY, FACULTY_NAME)
VALUES ('��', '�������������� ����������');

-- ������������ ���������
INSERT INTO PROFESSION (profession, faculty, profession_name, qualification, children)
VALUES (
    '��', 
    '��', 
    '�������������� �������', 
    '�������-�����������-�������������', 
    child_profession_table(
        child_profession('��', '�������� ������', '�������-�����������'),
        child_profession('��', '�������������� �������', '�������-�����������')
    )
);

INSERT INTO PROFESSION (profession, faculty, profession_name, qualification, children)
VALUES (
    '��', 
    '��', 
    '�������������� �������', 
    '�������-�����������-�������������', 
    child_profession_table(
        child_profession('��', '�������������� �������', '�������-�����������')
    )
);

INSERT INTO PROFESSION (profession, faculty, profession_name, qualification, children)
VALUES (
    '��', 
    '��', 
    '����������� ���������', 
    '�������-�����������', 
    child_profession_table(
    child_profession('��', '����������� ����������� �������������� ����������', '�������-�����������'),
    child_profession('������', '����������� ����������� � ������������ ��������� ������', '�������-�����������')
    )  -- ������ ������� ��� �������� ���������
);

-- �������� ���������
INSERT INTO PROFESSION (profession, faculty, profession_name, qualification, children)
VALUES (
    '��', 
    '��', 
    '�������� ������', 
    '�������-�����������', 
    child_profession_table()
);

INSERT INTO PROFESSION (profession, faculty, profession_name, qualification, children)
VALUES (
    '������', 
    '��', 
    '����������� ����������� � ������������ ��������� ������', 
    '�������-�����������', 
    child_profession_table()
);
