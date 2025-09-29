use univer;
-----------------------------------------------
--INDEXES--
-----------------------------------------------
CREATE INDEX IX_Teacher_Surname ON TEACHER(TEACHER_SURNAME);
CREATE INDEX IX_Student_Surname ON STUDENT(STUDENT_SURNAME);
CREATE INDEX IX_Profession_Name ON PROFESSION(PROFESSION_NAME);
-----------------------------------------------
--VIEWS--
-----------------------------------------------
CREATE OR ALTER VIEW vw_SubjectsWithTeachers AS
SELECT 
    SUB.SUBJECT,
    SUB.SUBJECT_NAME,
    T.TEACHER_NAME,
    T.TEACHER_SURNAME,
    P.PULPIT_NAME
FROM 
    SUBJECT SUB
LEFT JOIN 
    TEACHER T ON SUB.TEACHER = T.TEACHER
LEFT JOIN 
    PULPIT P ON T.PULPIT = P.PULPIT;
-----------------------------------------------
SELECT * FROM vw_SubjectsWithTeachers;
-----------------------------------------------
CREATE OR ALTER VIEW vw_StudentProgress AS
SELECT 
    S.IDSTUDENT,
    S.STUDENT_NAME,
    S.STUDENT_SURNAME,
    P.SUBJECT,
    P.ESTIMATION
FROM 
    PROGRESS P
JOIN 
    STUDENT S ON P.IDSTUDENT = S.IDSTUDENT;
-----------------------------------------------
SELECT * FROM vw_StudentProgress;
-----------------------------------------------
CREATE OR ALTER VIEW vw_SubjectEstimation AS
SELECT 
    SUB.SUBJECT,
    SUB.SUBJECT_NAME,
    AVG(P.ESTIMATION) AS AverageEstimation
FROM 
    PROGRESS P
JOIN 
    SUBJECT SUB ON P.SUBJECT = SUB.SUBJECT
GROUP BY 
    SUB.SUBJECT, SUB.SUBJECT_NAME;
-----------------------------------------------
SELECT * FROM vw_SubjectEstimation;
-----------------------------------------------
--FUNCTIONS--
-----------------------------------------------
CREATE FUNCTION dbo.GetStudentsByGroup
(
    @GroupId INT
)
RETURNS TABLE
AS
RETURN
(
    SELECT 
        S.IDSTUDENT,
        S.STUDENT_NAME,
        S.STUDENT_SURNAME,
        S.STUDENT_PATRONYMIC,
        S.BDAY
    FROM 
        STUDENT S
    WHERE 
        S.IDGROUP = @GroupId
);
-----------------------------------------------
SELECT * FROM dbo.GetStudentsByGroup(1);
-----------------------------------------------
--PROCEDURES--
-----------------------------------------------
CREATE PROCEDURE AddTeacher
    @Teacher CHAR(10),
    @TeacherName NVARCHAR(100),
    @TeacherSurname NVARCHAR(100),
    @TeacherPatronymic NVARCHAR(100),
    @Gender CHAR(1),
    @StartDate DATE,
    @WorkTime DECIMAL(10, 2),
    @Pulpit CHAR(20)
AS
BEGIN
    INSERT INTO TEACHER (TEACHER, TEACHER_NAME, TEACHER_SURNAME, TEACHER_PATRONYMIC, GENDER, START_DATE, WORK_TIME, PULPIT)
    VALUES (@Teacher, @TeacherName, @TeacherSurname, @TeacherPatronymic, @Gender, @StartDate, @WorkTime, @Pulpit);
END;
-----------------------------------------------
CREATE PROCEDURE UpdateTeacher
    @Teacher CHAR(10),
    @TeacherName NVARCHAR(100),
    @TeacherSurname NVARCHAR(100),
    @TeacherPatronymic NVARCHAR(100),
    @Gender CHAR(1),
    @StartDate DATE,
    @WorkTime DECIMAL(10, 2),
    @Pulpit CHAR(20)
AS
BEGIN
    UPDATE TEACHER
    SET TEACHER_NAME = @TeacherName,
        TEACHER_SURNAME = @TeacherSurname,
        TEACHER_PATRONYMIC = @TeacherPatronymic,
        GENDER = @Gender,
        START_DATE = @StartDate,
        WORK_TIME = @WorkTime,
        PULPIT = @Pulpit
    WHERE TEACHER = @Teacher;
END;
-----------------------------------------------
CREATE PROCEDURE DeleteTeacher
    @Teacher CHAR(10)
AS
BEGIN
    DELETE FROM TEACHER WHERE TEACHER = @Teacher;
END;
-----------------------------------------------
EXEC AddTeacher 'T01', 'Иван', 'Иванов', 'Иванович', 'м', '2015-09-01', 40.00, 'P01';
EXEC UpdateTeacher 'T01', 'Иван', 'Иванов', 'Иванович', 'м', '2015-09-01', 40.00, 'P01';
EXEC DeleteTeacher 'T01';
-----------------------------------------------
-----------------------------------------------
-----------------------------------------------
CREATE PROCEDURE AddGroup
    @Faculty CHAR(10),
    @Profession CHAR(20),
    @YearFirst SMALLINT
AS
BEGIN
    INSERT INTO GROUPS (FACULTY, PROFESSION, YEAR_FIRST)
    VALUES (@Faculty, @Profession, @YearFirst);
END;
-----------------------------------------------
CREATE PROCEDURE UpdateGroup
    @IdGroup INT,
    @Faculty CHAR(10),
    @Profession CHAR(20),
    @YearFirst SMALLINT
AS
BEGIN
    UPDATE GROUPS
    SET FACULTY = @Faculty, PROFESSION = @Profession, YEAR_FIRST = @YearFirst
    WHERE IDGROUP = @IdGroup;
END;
-----------------------------------------------
CREATE PROCEDURE DeleteGroup
    @IdGroup INT
AS
BEGIN
    DELETE FROM GROUPS WHERE IDGROUP = @IdGroup;
END;
-----------------------------------------------
EXEC AddGroup 'F01', 'P01', 2023;
EXEC UpdateGroup 1, 'F01', 'P01', 2024;
EXEC DeleteGroup 1;
-----------------------------------------------
CREATE PROCEDURE AddStudent
    @IdGroup INT,
    @StudentName NVARCHAR(100),
    @StudentSurname NVARCHAR(100),
    @StudentPatronymic NVARCHAR(100),
    @Bday DATE
AS
BEGIN
    INSERT INTO STUDENT (IDGROUP, STUDENT_NAME, STUDENT_SURNAME, STUDENT_PATRONYMIC, BDAY)
    VALUES (@IdGroup, @StudentName, @StudentSurname, @StudentPatronymic, @Bday);
END;
-----------------------------------------------
CREATE PROCEDURE UpdateStudent
    @IdStudent INT,
    @IdGroup INT,
    @StudentName NVARCHAR(100),
    @StudentSurname NVARCHAR(100),
    @StudentPatronymic NVARCHAR(100),
    @Bday DATE
AS
BEGIN
    UPDATE STUDENT
    SET IDGROUP = @IdGroup,
        STUDENT_NAME = @StudentName,
        STUDENT_SURNAME = @StudentSurname,
        STUDENT_PATRONYMIC = @StudentPatronymic,
        BDAY = @Bday
    WHERE IDSTUDENT = @IdStudent;
END;
-----------------------------------------------
CREATE PROCEDURE DeleteStudent
    @IdStudent INT
AS
BEGIN
    DELETE FROM STUDENT WHERE IDSTUDENT = @IdStudent;
END;
-----------------------------------------------
EXEC AddStudent 1, 'Сергей', 'Сергеев', 'Сергеевич', '2001-05-15';
EXEC UpdateStudent 1, 1, 'Сергей', 'Сергеев', 'Сергеевич', '2001-05-15';
EXEC DeleteStudent 1;
-----------------------------------------------
CREATE PROCEDURE AddProgress
    @Subject CHAR(10),
    @IdStudent INT,
    @PDate DATE,
    @Estimation INT
AS
BEGIN
    INSERT INTO PROGRESS (SUBJECT, IDSTUDENT, PDATE, ESTIMATION)
    VALUES (@Subject, @IdStudent, @PDate, @Estimation);
END;
-----------------------------------------------
CREATE PROCEDURE UpdateProgress
    @Subject CHAR(10),
    @IdStudent INT,
    @PDate DATE,
    @Estimation INT
AS
BEGIN
    UPDATE PROGRESS
    SET ESTIMATION = @Estimation
    WHERE SUBJECT = @Subject AND IDSTUDENT = @IdStudent AND PDATE = @PDate;
END;
-----------------------------------------------
CREATE PROCEDURE DeleteProgress
    @Subject CHAR(10),
    @IdStudent INT,
    @PDate DATE
AS
BEGIN
    DELETE FROM PROGRESS WHERE SUBJECT = @Subject AND IDSTUDENT = @IdStudent AND PDATE = @PDate;
END;
-----------------------------------------------
EXEC AddProgress 'SUB01', 1, '2023-09-15', 8;
EXEC UpdateProgress 'SUB01', 1, '2023-09-15', 9;
EXEC DeleteProgress 'SUB01', 1, '2023-09-15';