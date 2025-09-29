/*9. Создать DDL-триггер, реагирующий на все DDL-события в БД UNIVER. 
Триггер должен запрещать создавать но-вые таблицы и удалять существующие. 
выполнение триггер должен сопровождать сообщением, которое содержит: 
тип события, имя и тип объекта, а также пояснительный текст, в случае запрещения выполнения опе-ратора. 
Разработать сценарий, демонстрирующий работу триггера. 
*/

use UNIVER;
go
drop trigger if exists  DDL_UNIVER on database;
go

	create  trigger DDL_UNIVER on database
                    for DDL_DATABASE_LEVEL_EVENTS
	    as
        raiserror('Операции с БД запрещены', 10, 1);
	    rollback;
	return;
	go

	

	drop table  TR_AUDIT;


	 drop trigger if exists  DDL_UNIVER on database;