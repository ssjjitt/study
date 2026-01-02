SELECT NAME, OPEN_MODE FROM V$PDBS;

ALTER PLUGGABLE DATABASE rispdb CLOSE IMMEDIATE;
DROP PLUGGABLE DATABASE rispdb INCLUDING DATAFILES;

ALTER PLUGGABLE DATABASE rispdb OPEN;
--------------------------------------------------------------------------------
--1)Создание пользователей на каждом сервере
--От SYS_PDBORCL
--DROP USER RISD CASCADE;
CREATE USER RISA IDENTIFIED BY 282004;
GRANT CONNECT, CREATE SESSION, CREATE TABLE, CREATE DATABASE LINK TO RISA;
ALTER USER RISA QUOTA UNLIMITED ON SYSTEM;

select * from all_users;

SELECT tablespace_name FROM dba_tablespaces;

--2)Установка DBLINK между серверами

grant insert, select on sys to public;

CREATE DATABASE LINK dblink_name 
CONNECT TO remote_username 
IDENTIFIED BY remote_password 
USING 'tns_service_name';

CREATE DATABASE LINK RISA_RISD
  CONNECT TO RISA IDENTIFIED BY 23052005
  USING '(DESCRIPTION=
            (ADDRESS=(PROTOCOL=TCP)(HOST=172.20.10.8)(PORT=1521))
            (CONNECT_DATA=(SERVICE_NAME=orclpdb)))';

CREATE DATABASE LINK RISD_RISA
CONNECT TO RISA IDENTIFIED BY "23052005"
USING 'RIS';

--SHUTDOWN IMMEDIATE;
--STARTUP;

ALTER SESSION SET CONTAINER=RISPDB;

DROP DATABASE LINK RISD_RISA;
--3)Создание таблиц
CREATE TABLE RISD (
   id NUMBER PRIMARY KEY,
   name VARCHAR2(255) NOT NULL
);

DROP TABLE RISD;
SELECT table_name FROM all_tables WHERE owner = 'RISA';
SELECT * FROM RISD;
SELECT * FROM RISA@RISD_RISA;
INSERT INTO RISA@RISD_RISA (id, name) VALUES (2, 'Misha');
INSERT INTO RISD (id, name) VALUES (3, 'Misha');
--4)Разработка SQL-скрипта для распределённых транзакций
--INSERT/INSERT
BEGIN
   INSERT INTO RISD (id, name) VALUES (2, 'Misha');
   COMMIT;

   INSERT INTO RISA@RISD_RISA (id, name) VALUES (3, 'Pasha');
   COMMIT;
END;

--INSERT/UPDATE
BEGIN
   INSERT INTO RISD (id, name) VALUES (3, 'Sasha');
   COMMIT;

   UPDATE RISA@RISD_RISA SET name = 'Sasha' WHERE id = 1;
   COMMIT;
END;

--UPDATE/INSERT
BEGIN
   UPDATE RISD SET name = 'Gleb' WHERE id = 1337;
   COMMIT;

   INSERT INTO RISA@RISD_RISA (id, name) VALUES (4, 'Vlad');
   COMMIT;
END;

--5)Смоделировать ошибку нарушения целостности
--Транзакция с нарушением ограничения целостности
BEGIN
   INSERT INTO RISD (id, name) VALUES (1, 'Petr');
   COMMIT;

   INSERT INTO RISA@RISD_RISA (id, name) VALUES (1, 'Invalid Item');
   COMMIT;
END;

--6)Смоделировать блокировку ресурса
BEGIN
   DELETE FROM RISA@RISD_RISA WHERE id = 1;
END;

