--SET SERVEROUTPUT ON;
--DELETE FROM PROFESSION;

--1
-- структура данных для каждой профессии
CREATE OR REPLACE TYPE child_profession AS OBJECT (
    profession CHAR(20),
    profession_name NVARCHAR2(100),
    qualification NVARCHAR2(50)
);
-- тип коллекции из таблицы объектов
-- много profession_obj в одной записи
CREATE OR REPLACE TYPE child_profession_table AS TABLE OF child_profession;
-- основная таблица
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
        DBMS_OUTPUT.PUT_LINE('Профессия: ' || rec.profession_name || 
                             ' (Код: ' || rec.profession || 
                             '), Квалификация: ' || rec.qualification);
        DBMS_OUTPUT.PUT_LINE('  Дочерняя профессия: ' || rec.child_profession_name || 
                             ' (Код: ' || rec.child_profession || ')');
    END LOOP;
END;
--
EXEC DisplaySubProfessions('ИС');

--3
CREATE OR REPLACE PROCEDURE AddSubProfession (
    p_profession CHAR,
    p_faculty CHAR,
    p_profession_name NVARCHAR2,
    p_qualification NVARCHAR2,
    p_parent_profession CHAR
) AS
BEGIN
    -- Вставка новой профессии
    INSERT INTO PROFESSION (profession, faculty, profession_name, qualification, children)
    VALUES (
        p_profession, 
        p_faculty, 
        p_profession_name, 
        p_qualification,
        child_profession_table()  -- Пустая таблица для дочерних профессий
    );

    -- Обновление родительской профессии, добавляя новую в вложенную таблицу
    UPDATE PROFESSION
    SET children = children
    WHERE profession = p_parent_profession;

    -- Проверка, была ли обновлена родительская профессия
    IF SQL%ROWCOUNT = 0 THEN
        RAISE_APPLICATION_ERROR(-20001, 'Родительская профессия не найдена: ' || p_parent_profession);
    END IF;
END;
--
EXEC AddSubProfession('ДП', 'ИТ', 'Информационные системы', 'Инженер-программист', 'ИС');
--4
CREATE OR REPLACE PROCEDURE MoveSubTree (
    p_source_profession CHAR,
    p_target_profession CHAR
) AS
    v_children child_profession_table;
BEGIN
    -- Получаем детей источника
    SELECT children INTO v_children
    FROM PROFESSION
    WHERE profession = p_source_profession;

    -- Добавляем детей в целевой узел
    UPDATE PROFESSION
    SET children = children || v_children
    WHERE profession = p_target_profession;

    -- Проверка, была ли обновлена целевая профессия
    IF SQL%ROWCOUNT = 0 THEN
        RAISE_APPLICATION_ERROR(-20002, 'Целевая профессия не найдена: ' || p_target_profession);
    END IF;

    -- Удаляем источник
    DELETE FROM PROFESSION
    WHERE profession = p_source_profession;
END;
--
EXEC DisplaySubProfessions('ПИ');






INSERT INTO FACULTY (FACULTY, FACULTY_NAME)
VALUES ('ИТ', 'Информационные технологии');

-- Родительские профессии
INSERT INTO PROFESSION (profession, faculty, profession_name, qualification, children)
VALUES (
    'ИС', 
    'ИТ', 
    'Информационные системы', 
    'Инженер-программист-системотехник', 
    child_profession_table(
        child_profession('ЦД', 'Цифровой дизайн', 'инженер-программист'),
        child_profession('ИС', 'Информационные системы', 'инженер-программист')
    )
);

INSERT INTO PROFESSION (profession, faculty, profession_name, qualification, children)
VALUES (
    'ИС', 
    'ИТ', 
    'Информационные системы', 
    'Инженер-программист-системотехник', 
    child_profession_table(
        child_profession('ИС', 'Информационные системы', 'инженер-программист')
    )
);

INSERT INTO PROFESSION (profession, faculty, profession_name, qualification, children)
VALUES (
    'ПИ', 
    'ИТ', 
    'Программная инженерия', 
    'Инженер-программист', 
    child_profession_table(
    child_profession('ПИ', 'Программное обеспечение информационных технологий', 'инженер-программист'),
    child_profession('ПОИБМС', 'Программная обеспечение и безопасность мобильных систем', 'инженер-программист')
    )  -- Пустая таблица для дочерних профессий
);

-- Дочерние профессии
INSERT INTO PROFESSION (profession, faculty, profession_name, qualification, children)
VALUES (
    'ЦД', 
    'ИТ', 
    'Цифровой дизайн', 
    'Инженер-программист', 
    child_profession_table()
);

INSERT INTO PROFESSION (profession, faculty, profession_name, qualification, children)
VALUES (
    'ПОИБМС', 
    'ИТ', 
    'Программное обеспечение и безопасность мобильных систем', 
    'инженер-программист', 
    child_profession_table()
);
