

set transaction isolation level READ COMMITTED 
use UNIVER

--(��������������� ������)
-- A ---
set transaction isolation level READ COMMITTED
begin transaction
select * from SUBJECT where SUBJECT = '��';
-------------------------- t1 ------------------
-------------------------- t2 -----------------
select * from SUBJECT where SUBJECT = '��';
commit ;

--- B ---
begin transaction
-------------------------- t1 --------------------

update SUBJECT set SUBJECT_NAME = '���� ������ (��������)'  where SUBJECT = '��';
commit tran;
-------------------------- t2 --------------------
rollback