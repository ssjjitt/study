/*8.  Для таблицы FACULTY создать IN-STEAD OF-триггер, запрещающий удаление строк в таблице.
Разработать сценарий, который демонстри-рует на примере базы данных X_UNIVER, что проверка ограничения целостности выполнена, если есть INSTEAD OF-триггер.
С помощью оператора DROP удалить все DML-триггеры, созданные в этой лабораторной работе.*/
use UNIVER
go
drop trigger if exists dbo.F_INSTEAD_OF
go

	create trigger F_INSTEAD_OF
	on FACULTY instead of DELETE
	as
        raiserror(N'Удаление запрещено', 10, 1);
	    rollback;
	return;
	    go

	 delete FACULTY where FACULTY = 'ИДиП'
	    go

drop trigger if exists dbo.F_INSTEAD_OF
go