--------------------------Student Object Type--------------------------
CREATE OR REPLACE TYPE Student_Type AS OBJECT (
    IDSTUDENT NUMBER,
    IDGROUP NUMBER,
    STUDENT_NAME VARCHAR2(100),
    STUDENT_SURNAME VARCHAR2(100),
    STUDENT_PATRONYMIC VARCHAR2(100),
    BDAY DATE,
    -- Additional Constructor
    CONSTRUCTOR FUNCTION Student_Type(
        IDSTUDENT NUMBER,
        IDGROUP NUMBER,
        STUDENT_NAME VARCHAR2,
        STUDENT_SURNAME VARCHAR2,
        STUDENT_PATRONYMIC VARCHAR2,
        BDAY DATE
    ) RETURN SELF AS RESULT,
    -- Method to get full name
    MEMBER FUNCTION Get_Full_Name RETURN VARCHAR2,
    -- Method to update birthdate
    MEMBER PROCEDURE Update_Birthdate(New_BDAY DATE)
);
----------------------------------------------------
CREATE OR REPLACE TYPE BODY Student_Type AS
    CONSTRUCTOR FUNCTION Student_Type(
        IDSTUDENT NUMBER,
        IDGROUP NUMBER,
        STUDENT_NAME VARCHAR2,
        STUDENT_SURNAME VARCHAR2,
        STUDENT_PATRONYMIC VARCHAR2,
        BDAY DATE
    ) RETURN SELF AS RESULT IS
    BEGIN
        SELF.IDSTUDENT := IDSTUDENT;
        SELF.IDGROUP := IDGROUP;
        SELF.STUDENT_NAME := STUDENT_NAME;
        SELF.STUDENT_SURNAME := STUDENT_SURNAME;
        SELF.STUDENT_PATRONYMIC := STUDENT_PATRONYMIC;
        SELF.BDAY := BDAY;
        RETURN;
    END;
    --------------------------
    MEMBER FUNCTION Get_Full_Name RETURN VARCHAR2 IS
    BEGIN
        RETURN SELF.STUDENT_SURNAME || ' ' || SELF.STUDENT_NAME || ' ' || SELF.STUDENT_PATRONYMIC;
    END;
    --------------------------
    MEMBER PROCEDURE Update_Birthdate(New_BDAY DATE) IS
    BEGIN
        SELF.BDAY := New_BDAY;
    END;
END;

--------------------------Group Object Type--------------------------
CREATE OR REPLACE TYPE Group_Type AS OBJECT (
    IDGROUP NUMBER,
    FACULTY VARCHAR2(10),
    PROFESSION VARCHAR2(20),
    YEAR_FIRST SMALLINT,
    -- Method to compare groups by faculty and year
    MAP MEMBER FUNCTION Compare_By_Faculty_Year RETURN VARCHAR2
);
----------------------------------------------------
CREATE OR REPLACE TYPE BODY Group_Type AS
    MAP MEMBER FUNCTION Compare_By_Faculty_Year RETURN VARCHAR2 IS
    BEGIN
        RETURN SELF.FACULTY || ' ' || SELF.YEAR_FIRST;
    END;
END;
--------------------------Copying Data to Object Tables--------------------------
CREATE TABLE Students_Object_Table OF Student_Type;
----------------------------------------------------
INSERT INTO Students_Object_Table
SELECT Student_Type(
    IDSTUDENT, IDGROUP, STUDENT_NAME, STUDENT_SURNAME, STUDENT_PATRONYMIC, BDAY
)
FROM STUDENT;
----------------------------------------------------
CREATE TABLE Groups_Object_Table OF Group_Type;
----------------------------------------------------
INSERT INTO Groups_Object_Table
SELECT Group_Type(IDGROUP, FACULTY, PROFESSION, YEAR_FIRST)
FROM GROUPS;
--------------------------Object View--------------------------
CREATE OR REPLACE VIEW Students_Object_View AS
SELECT s.IDSTUDENT, s.Get_Full_Name() AS Full_Name, g.FACULTY, g.YEAR_FIRST
FROM Students_Object_Table s
JOIN Groups_Object_Table g ON s.IDGROUP = g.IDGROUP;
--------------------------Indexes--------------------------
CREATE INDEX idx_students_object_surname ON Students_Object_Table (STUDENT_SURNAME);
CREATE INDEX idx_groups_object_faculty_year ON Groups_Object_Table (FACULTY, YEAR_FIRST);
CREATE INDEX idx_full_name_index ON Students_Object_Table s (STUDENT_SURNAME || STUDENT_NAME || STUDENT_PATRONYMIC);
--------------------------Testing--------------------------
select * from Groups_Object_Table;
select * from Students_Object_Table;
SELECT g.Compare_By_Faculty_Year() FROM Groups_Object_Table g;
SELECT s.Get_Full_Name() AS Full_Name FROM Students_Object_Table s;
--------------------------
SET SERVEROUTPUT ON;
--------------------------
DECLARE
    v_Group_ID NUMBER := 1; 
BEGIN
    FOR student IN (SELECT s.Get_Full_Name() AS Full_Name
                    FROM Students_Object_Table s
                    WHERE s.IDGROUP = v_Group_ID) LOOP
        DBMS_OUTPUT.PUT_LINE('Student in Group ' || v_Group_ID || ': ' || student.Full_Name);
    END LOOP;
END;
