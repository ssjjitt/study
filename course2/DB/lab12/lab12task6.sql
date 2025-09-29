use UNIVER
--task6 (фантомное чтение)

-- A ---
set transaction isolation level REPEATABLE READ
begin transaction
select * from SUBJECT where SUBJECT = 'БД';
-------------------------- t1 ------------------
-------------------------- t2 -----------------
select count(*) from SUBJECT where SUBJECT = 'БД';
rollback;

--- B ---
begin transaction
-------------------------- t1 ------------------
update SUBJECT set SUBJECT_NAME ='1253asdat' where SUBJECT = 'БД'
commit ;