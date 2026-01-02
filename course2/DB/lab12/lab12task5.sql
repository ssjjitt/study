

set transaction isolation level READ COMMITTED 
use UNIVER

--(Неповторяющееся чтение)
-- A ---
set transaction isolation level READ COMMITTED
begin transaction
select * from SUBJECT where SUBJECT = 'БД';
-------------------------- t1 ------------------
-------------------------- t2 -----------------
select * from SUBJECT where SUBJECT = 'БД';
commit ;

--- B ---
begin transaction
-------------------------- t1 --------------------

update SUBJECT set SUBJECT_NAME = 'Базы данных (изменено)'  where SUBJECT = 'БД';
commit tran;
-------------------------- t2 --------------------
rollback