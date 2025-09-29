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
VALUES ('ИТ', 'Информационные технологии');

-- Родительские профессии
INSERT INTO PROFESSION (PROFESSION, FACULTY, PROFESSION_NAME, QUALIFICATION, PARENT_PROFESSION)
VALUES ('ИС', 'ИТ', 'Информационные системы', 'Инженер-программист-системотехник', NULL);

INSERT INTO PROFESSION (PROFESSION, FACULTY, PROFESSION_NAME, QUALIFICATION, PARENT_PROFESSION)
VALUES ('ПИ', 'ИТ', 'Программная инженерия', 'Инженер-программист', NULL);

-- Дочерние профессии
INSERT INTO PROFESSION (PROFESSION, FACULTY, PROFESSION_NAME, QUALIFICATION, PARENT_PROFESSION)
VALUES ('ЦД', 'ИТ', 'Цифровой дизайн', 'инженер-программист', 'ИС');

INSERT INTO PROFESSION (PROFESSION, FACULTY, PROFESSION_NAME, QUALIFICATION, PARENT_PROFESSION)
VALUES ('ПОИТ', 'ИТ', 'Программное обеспечение информационных технологий', 'инженер-программист', 'ПИ');

INSERT INTO PROFESSION (PROFESSION, FACULTY, PROFESSION_NAME, QUALIFICATION, PARENT_PROFESSION)
VALUES ('ПОИБМС', 'ИТ', 'Программное обеспечение и безопасность мобильных систем', 'инженер-программист', 'ПИ');

CREATE OR REPLACE PROCEDURE GetParentAndChildProfessions (
    p_profession CHAR
) AS
BEGIN
    DBMS_OUTPUT.PUT_LINE('Дочерние узлы для профессии ' || p_profession || ':');
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
        DBMS_OUTPUT.PUT_LINE('Дочерняя профессия: ' || rec.PROFESSION_NAME || ' (Код: ' || rec.PROFESSION || ')');
    END LOOP;
    DBMS_OUTPUT.PUT_LINE('Родительские узлы для профессии ' || p_profession || ':');
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
        WHERE PROFESSION IS NOT NULL  -- Исключаем записи без профессии
    ) LOOP
        DBMS_OUTPUT.PUT_LINE('Родительская профессия: ' || rec.PROFESSION_NAME || ' (Код: ' || rec.PROFESSION || ')');
    END LOOP;
    IF SQL%ROWCOUNT = 0 THEN
        DBMS_OUTPUT.PUT_LINE('Профессия не найдена: ' || p_profession);
    END IF;
END;

SET SERVEROUTPUT ON;
BEGIN
    GetParentAndChildProfessions('ПИ'); 
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

SELECT * FROM PROFESSION WHERE PROFESSION = 'ЦД';



EXEC AddSubProfession('ДП', 'ИТ', 'Дизайн программного обеспечения', 'Инженер-программист', 'ИС');

EXEC MoveSubProfession('ДП', 'ПИ');