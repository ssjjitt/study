use UNIVER
go

ALTER PROCEDURE PSUBJECT @p NVARCHAR(20) = NULL, @c INT OUTPUT
AS
BEGIN
    DECLARE @count INT = (SELECT COUNT(*) FROM SUBJECT)
    SELECT *
    FROM SUBJECT
    WHERE SUBJECT.PULPIT = @p
    SET @c = @@ROWCOUNT
    RETURN @count
END
GO

declare @c int;
exec PSUBJECT 'ศั่า', @c output
print 'result = ' + cast(@c as varchar(3));