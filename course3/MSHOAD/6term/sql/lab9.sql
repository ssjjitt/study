SET SERVEROUTPUT ON;

-- Создание типа объекта для студента
CREATE OR REPLACE TYPE StudentType AS OBJECT (
    IDSTUDENT NUMBER,
    IDGROUP NUMBER,
    STUDENT_NAME NVARCHAR2(100),
    STUDENT_SURNAME VARCHAR2(100),
    STUDENT_PATRONYMIC VARCHAR2(100),
    BDAY DATE
);

-- Создание коллекции объектов типа StudentType
CREATE OR REPLACE TYPE StudentTableType IS TABLE OF StudentType;

-- Создание типа объекта для группы
CREATE OR REPLACE TYPE GroupType AS OBJECT (
    IDGROUP NUMBER,
    FACULTY CHAR(10),
    PROFESSION CHAR(20),
    YEAR_FIRST SMALLINT
);

-- Создание коллекции объектов типа GroupType
CREATE OR REPLACE TYPE GroupTableType IS TABLE OF GroupType;

DECLARE
    -- Объявление коллекций
    K1 StudentTableType := StudentTableType();
    K2 GroupTableType := GroupTableType();
    
    v_Exists INTEGER := 0;  
    v_inserted INTEGER := 0;
    v_updated INTEGER := 0;

BEGIN
    -- Заполнение коллекции K1 (Студенты)
    SELECT StudentType(IDSTUDENT, IDGROUP, STUDENT_NAME, STUDENT_SURNAME, STUDENT_PATRONYMIC, BDAY)
    BULK COLLECT INTO K1 FROM STUDENT;

    -- Заполнение коллекции K2 (Группы)
    SELECT GroupType(IDGROUP, FACULTY, PROFESSION, YEAR_FIRST)
    BULK COLLECT INTO K2 FROM GROUPS;

    DBMS_OUTPUT.PUT_LINE('Данные загружены в коллекции K1 и K2');
    
    -- b. Проверка пересечений между K1 и K2
    FOR i IN 1 .. K1.COUNT LOOP
        FOR j IN 1 .. K2.COUNT LOOP
            IF K1(i).IDGROUP = K2(j).IDGROUP THEN
                DBMS_OUTPUT.PUT_LINE('Пересечение: Студент ' || K1(i).STUDENT_NAME || ' принадлежит группе ' || K2(j).IDGROUP);
            END IF;
        END LOOP;
    END LOOP;
    
    -- c. Проверка, является ли элемент членом коллекции K1
    FOR i IN 1 .. K1.COUNT LOOP
        IF K1(i).IDSTUDENT = 1 THEN
            v_Exists := 1;
            EXIT;
        END IF;
    END LOOP;
    IF v_Exists = 1 THEN
        DBMS_OUTPUT.PUT_LINE('Студент с ID 1 найден в коллекции K1');
    ELSE
        DBMS_OUTPUT.PUT_LINE('Студент с ID 1 не найден в коллекции K1');
    END IF;
    
    -- d. Поиск пустых коллекций K1
    FOR i IN 1 .. K1.COUNT LOOP
        IF K1(i).IDGROUP IS NULL THEN
            DBMS_OUTPUT.PUT_LINE('Пустая коллекция K1: Студент с ID = ' || K1(i).IDSTUDENT);
        END IF;
    END LOOP;

    -- e. Обмен атрибутами K2 между двумя элементами K1
    IF K1.COUNT > 1 THEN
        DECLARE
            temp_Group GroupType;
        BEGIN
            temp_Group := K2(1);
            K2(1) := K2(2);
            K2(2) := temp_Group;
            DBMS_OUTPUT.PUT_LINE('Обмен группами завершен');
        END;
    END IF;

    -- 3. Преобразование коллекции в реляционные данные
    FOR i IN 1 .. K1.COUNT LOOP
        BEGIN
            INSERT INTO STUDENT (IDGROUP, STUDENT_NAME, STUDENT_SURNAME, STUDENT_PATRONYMIC, BDAY)
            VALUES (K1(i).IDGROUP, K1(i).STUDENT_NAME, K1(i).STUDENT_SURNAME, K1(i).STUDENT_PATRONYMIC, K1(i).BDAY);
            v_inserted := v_inserted + 1; 
        EXCEPTION
            WHEN DUP_VAL_ON_INDEX THEN
                DBMS_OUTPUT.PUT_LINE('Ошибка: Студент с ID ' || K1(i).IDSTUDENT || ' уже существует');
        END;
    END LOOP;

    DBMS_OUTPUT.PUT_LINE('Количество вставленных данных: ' || v_inserted);
    
    -- 4. Применение BULK операций
    FORALL i IN INDICES OF K1
        UPDATE STUDENT
        SET STUDENT_NAME = K1(i).STUDENT_NAME,
            STUDENT_SURNAME = K1(i).STUDENT_SURNAME
        WHERE IDSTUDENT = K1(i).IDSTUDENT;

    v_updated := SQL%ROWCOUNT;
    DBMS_OUTPUT.PUT_LINE('Успешно обновлено записей: ' || v_updated);

END;

