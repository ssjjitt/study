/*5. Разработать сценарий, который демон-стрирует на примере базы данных X_UNIVER, что проверка ограничения целостности выпол-няется до срабатывания AFTER-триггера.*/

use UNIVER
go

select * from TR_AUDIT
go;

/*alter table TEACHER  add constraint GENDER check (GENDER = 'м'or GENDER='ж')*/

update TEACHER set GENDER = 'q' where TEACHER='АРС'
select * from TR_AUDIT