use univer;
-- 1
-- это исходная таблица
-- иерархию по типу новшеств в бгту: 
-- ИС = ИС + ЦД
-- ПИ = ПОИТ + ПОИБМС (представим что они живчики)
CREATE TABLE PROFESSION (
    PROFESSION CHAR(20) PRIMARY KEY,
    FACULTY CHAR(10) FOREIGN KEY REFERENCES FACULTY(FACULTY),
    PROFESSION_NAME NVARCHAR(100),
    QUALIFICATION NVARCHAR(50)
);

--иерархия специальностей
ALTER TABLE PROFESSION
ADD PARENT_PROFESSION CHAR(20) NULL FOREIGN KEY REFERENCES PROFESSION(PROFESSION);

INSERT INTO FACULTY (FACULTY, FACULTY_NAME)
VALUES ('ИТ','Информационные технологии');

--родительские
INSERT INTO PROFESSION (PROFESSION, FACULTY, PROFESSION_NAME, QUALIFICATION, PARENT_PROFESSION)
VALUES ('ИС', 'ИТ', 'Информационные системы', 'Инженер-программист-системотехник', NULL);

INSERT INTO PROFESSION (PROFESSION, FACULTY, PROFESSION_NAME, QUALIFICATION, PARENT_PROFESSION)
VALUES ('ПИ', 'ИТ', 'Программная инженерия', ' Инженер-программист', NULL);

--дочерние
INSERT INTO PROFESSION (PROFESSION, FACULTY, PROFESSION_NAME, QUALIFICATION, PARENT_PROFESSION)
VALUES ('ЦД', 'ИТ', 'Цифровой дизайн', 'инженер-программист', 'ИС');

INSERT INTO PROFESSION (PROFESSION, FACULTY, PROFESSION_NAME, QUALIFICATION, PARENT_PROFESSION)
VALUES ('ПОИТ', 'ИТ', 'Программное обеспечение информационных технологий', 'инженер-программист', 'ПИ');

INSERT INTO PROFESSION (PROFESSION, FACULTY, PROFESSION_NAME, QUALIFICATION, PARENT_PROFESSION)
VALUES ('ПОИБМС', 'ИТ', 'Программное обеспечение и безопасность мобильных систем', 'инженер-программист', 'ПИ');

--2
--все подчиненные узлы с указанием уровня иерархии(параметр - значение узла)

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

--проверка
EXEC GetSubProfessions 'ПИ';

--3
--добавление подчиненного узла
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

--проверка
EXEC AddSubProfession 'ДП', 'ИТ', 'Дизайн программного обеспечения', 'Инженер-программист', 'ИС';

--4
--перемещение узлов
CREATE PROCEDURE MoveSubProfession
    @SourceProfession CHAR(20),
    @TargetProfession CHAR(20)
AS
BEGIN
    UPDATE PROFESSION
    SET PARENT_PROFESSION = @TargetProfession
    WHERE PARENT_PROFESSION = @SourceProfession OR PROFESSION = @SourceProfession;
END;

--проверка
EXEC MoveSubProfession 'ДП', 'ПИ';



-----------------------------
-- 1.	Для базы данных в СУБД SQL Server добавить для одной из таблиц столбец данных иерархического типа. 
ALTER TABLE PROFESSION
ADD HIERARCHY_COLUMN HIERARCHYID;

--2.	Создать процедуру, которая отобразит все подчиненные узлы с указанием уровня иерархии (параметр – значение узла).
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
        * -- Выбираем все остальные столбцы по вашему усмотрению
    FROM PROFESSION
    WHERE HIERARCHY_COLUMN.IsDescendantOf(@Node) = 1;
END;

CREATE PROCEDURE Add_p
@ParentNode HIERARCHYID,
@NewNode HIERARCHYID
AS
BEGIN
    INSERT INTO PROFESSION(PROFESSION,FACULTY,PROFESSION_NAME,QUALIFICATION,HIERARCHY_COLUMN)
    VALUES ('ИС', 'ИТ', 'Информационные системы', 'Инженер-программист', @ParentNode.GetDescendant(@NewNode, NULL));
END;
go

EXEC Show_p '/';
EXEC Add_p '/', '/1/';

