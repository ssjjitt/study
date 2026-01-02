USE UNIVER

--–азработать сценарий, демон-стрирующий работу в режиме не€вной транзакции.
--ѕроанализировать пример, приведенный справа, в кото-ром создаетс€ таблица ’, 
--и создать сценарий дл€ другой таблицы.

set nocount on

if  exists (select * from  SYS.OBJECTS        
where OBJECT_ID= object_id(N'DBO.X') )	            
drop table X;           
declare @c int, @flag char = 'r';--если тут будет r, то таблица не сохранитс€, если с - сохранитс€
SET IMPLICIT_TRANSACTIONS  ON   
CREATE table X(K int );                         
INSERT X values (1),(2),(3);
set @c = (select count(*) from X);
print 'количество строк в таблице X: ' + cast( @c as varchar(2));
if @flag = 'c'  commit;                   
else   rollback;                          
SET IMPLICIT_TRANSACTIONS  OFF  
if  exists (select * from  SYS.OBJECTS     
where OBJECT_ID= object_id(N'DBO.X') )
print 'таблица X есть';  
else print 'таблицы X нет'
