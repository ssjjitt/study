--RISPDBOSNOVA - от администратора пдб
ALTER PLUGGABLE DATABASE rispdb OPEN;

CREATE USER GDV IDENTIFIED BY 1111;

GRANT CONNECT, CREATE SESSION, CREATE TABLE, CREATE DATABASE LINK TO GDV;
ALTER USER GDV QUOTA UNLIMITED ON SYSTEM;

SELECT * FROM DBA_TS_QUOTAS WHERE USERNAME = 'GDV';
ALTER USER GDV QUOTA UNLIMITED ON USERS;


-- подкл к GDV
CREATE DATABASE LINK SAU_TO_GDV
  CONNECT TO SAU IDENTIFIED BY "1111"  
  USING 'RIS';  
  
select * from dual;  
  
select * from risA;
SELECT * FROM RISD@SAU_TO_GDV;
INSERT INTO RISD@SAU_TO_GDV (id, name) VALUES (4, 'Mike');

CREATE TABLE RISA (
   id NUMBER PRIMARY KEY,
   name VARCHAR2(255) NOT NULL
);

INSERT INTO RISA (id, name) VALUES (1, 'Alice');
INSERT INTO RISA (id, name) VALUES (2, 'Bob');
INSERT INTO RISA (id, name) VALUES (3, 'Charlie');
-- DELETE FROM RISA;
COMMIT;

-- GDV
--скрипт для распределённых транзакций
--INSERT/INSERT
BEGIN
   INSERT INTO RISA (id, name) VALUES (1, 'Misha');
   INSERT INTO RISD@SAU_TO_GDV (id, name) VALUES (2, 'Pasha');
   COMMIT;
END;

--INSERT/UPDATE
BEGIN
   INSERT INTO RISA (id, name) VALUES (3, 'Sasha');
   UPDATE RISD@SAU_TO_GDV SET name = 'Sasha' WHERE id = 1;
   COMMIT;
END;

--UPDATE/INSERT
BEGIN
   UPDATE RISA SET name = 'Gleb' WHERE id = 3;
   INSERT INTO RISD@SAU_TO_GDV (id, name) VALUES (4, 'Vlad');
   COMMIT;
END;

--5)Смоделировать ошибку нарушения целостности
--Транзакция с нарушением ограничения целостности
BEGIN
   INSERT INTO RISA (id, name) VALUES (1, 'Invalid');
   INSERT INTO RISD@SAU_TO_GDV (id, name) VALUES (1, 'Invalid');
   COMMIT;
END;

--Смоделировать блокировку ресурса
-- ЭТОТ БЛОКИРУЕТ
BEGIN
   INSERT INTO RISA (id, name) VALUES (1, 'Invalid');
END;
-- ЭТО ЧТОБЫ РАЗБЛОКИРОВАТЬСЯ
COMMIT;
-- ЭТО ЧТОБЫ ЖДАТЬ
BEGIN
   UPDATE RISA SET name = 'Grace Updated' WHERE id = 1;
   COMMIT;
END;




